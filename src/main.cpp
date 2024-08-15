#include <Geode/Geode.hpp>
#include <math.h>

using namespace geode::prelude;

#include <Geode/modify/HardStreak.hpp>
class $modify(TFHardStreak, HardStreak) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("HardStreak::updateStroke", 99999999);
	}

	$override
	void updateStroke(float i_deltaTime) {
		if (!m_drawStreak) {
			return;
		}
		clear();
		unsigned int l_pointCount = m_pointArray->count();
		if (l_pointCount == 0) {
			return;
		}
		if (getOpacity() == 0) {
			return;
		}
		PointNode* l_curPointNode;
		CCPoint l_startPoint;
		CCPoint l_endPoint;
		unsigned int l_loopCount = m_isSolid ? 1 : 2;
		CCPoint l_position = getPosition();
		
		for (int i = 0; i < l_pointCount; i++) {
			l_curPointNode = static_cast<PointNode*>(m_pointArray->objectAtIndex(i));
			if (!l_curPointNode) break;
			l_curPointNode->m_point = l_curPointNode->m_point-l_position;
		}
		m_currentPoint = m_currentPoint-l_position;
		for (int l_loop = 0; l_loop < l_loopCount; l_loop++) {
			for (int i = 0; i < l_pointCount; i++) {
				l_startPoint = static_cast<PointNode*>(m_pointArray->objectAtIndex(i))->m_point;
				if (i < l_pointCount-1) {
					l_endPoint = static_cast<PointNode*>(m_pointArray->objectAtIndex(i+1))->m_point;
				} else {
					l_endPoint = m_currentPoint;
				}
				//l_startPoint-=l_position;
				//l_endPoint-=l_position;
				if (l_startPoint != l_endPoint) {
					if (m_isFlipped) {
						CCPoint l_temp = l_startPoint;
						l_startPoint = l_endPoint;
						l_endPoint = l_temp;
					}
					float l_size = m_waveSize * (l_loop == 0 ? 6 : 2) * m_pulseSize;
					CCPoint l_offset = CCPointZero;
					if (1.0f <= l_size) {
						float l_angle = (atan2f(l_endPoint.y-l_startPoint.y, l_endPoint.x-l_startPoint.x) * 180.0f) / 3.141593 + 90.0;
						if (l_angle <= 360.0f) {
							if (l_angle > 0.0f) {
								l_angle += 360.0f;
							}
						} else {
							l_angle -= 360.0f;
						}
						l_angle = (l_angle * 3.141593) / 180.0f;
						l_offset = CCPoint(cosf(l_angle)*l_size*0.5f,sinf(l_angle)*l_size*0.5f);
					}
					float l_mul = tanf(asinf(fabs(l_offset.x) / (l_size*0.5f)));
					float l_yOffset = fabs(l_mul*fabs(l_offset.x));
					bool l_cutoff;
					if (i < l_pointCount-1 || l_loop != 0) {
						l_cutoff = false;
					} else {
						l_cutoff = !m_isFlipped;
						if (!m_isFlipped && 10.0f < fabs(ccpDistance(l_startPoint, l_endPoint))) {
							float l_cutoffY = fabs(l_mul*4.0f);
							if (!m_isFlipped) {
								l_endPoint.x -= 4.0f;
								if (l_endPoint.y <= l_startPoint.y) {
									l_endPoint.y += l_cutoffY;
								} else {
									l_endPoint.y -= l_cutoffY;
								}
							} else {
								l_startPoint.x += 4.0;
								if (l_endPoint.y <= l_startPoint.y) {
									l_startPoint.y -= l_cutoffY;
								} else {
									l_startPoint.y += l_cutoffY;
								}
							}
						}
					}
					
					CCPoint l_verts[4] = { l_startPoint, l_startPoint, l_endPoint, l_endPoint };
					CCPoint l_bounds = CCPoint(fabs(l_offset.x),l_yOffset);
					if (l_verts[3].y <= l_verts[1].y) {
						l_bounds.y = -l_bounds.y;
					}
					bool l_startYLessThanEndY = l_verts[1].y < l_verts[3].y;
					l_verts[1] -= l_bounds;
					l_verts[3] += l_bounds;
					
					if (l_loop != 0) {
						l_startPoint += l_bounds;
						l_endPoint -= l_bounds;
					}
					if (l_startYLessThanEndY) {
						l_verts[0] = l_verts[1];
						l_verts[1] = l_startPoint;
						l_verts[2] = l_verts[3];
						l_verts[3] = l_endPoint;
					} else {
						l_verts[0] = l_startPoint;
						l_verts[2] = l_endPoint;
					}

					if (l_cutoff) {
						l_verts[2] = l_endPoint;
						l_verts[3] = l_endPoint;
					}

					l_verts[0] = l_verts[0] - l_offset;
					l_verts[1] = l_verts[1] + l_offset;
					l_verts[2] = l_verts[2] + l_offset;
					l_verts[3] = l_verts[3] - l_offset;
					_ccColor3B l_color = {255, 255, 255};
					float l_opacity = getOpacity()/255.0f;
					if (l_loop == 0) {
						l_color = getColor();
					} else {
						l_opacity *= 0.65f;
					}
					drawPolygon(l_verts, 4, { l_color.r / 255.0f, l_color.g / 255.0f, l_color.b / 255.0f, l_opacity }, 0.0, { 0, 0, 0, 0 });
				}
			}
		}
		for (int i = 0; i < l_pointCount; i++) {
			l_curPointNode = static_cast<PointNode*>(m_pointArray->objectAtIndex(i));
			if (!l_curPointNode) break;
			l_curPointNode->m_point = l_curPointNode->m_point+l_position;
		}
		m_currentPoint = m_currentPoint+l_position;
	}
};