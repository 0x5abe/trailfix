#include <Geode/Geode.hpp>
#include <math.h>

using namespace geode::prelude;

$on_mod(Loaded) {
	Patch* patch;
	
	void* l_patchAddress1 = reinterpret_cast<void*>(geode::base::get() + 0x4e2320);
	void* l_patchAddress2 = reinterpret_cast<void*>(geode::base::get() + 0x2a6d9c);
	void* l_patchAddress3 = reinterpret_cast<void*>(geode::base::get() + 0x2a6d32);

	DWORD l_oldProtect;
	DWORD l_newProtect = 0x40;

	VirtualProtect(l_patchAddress1, 8, l_newProtect, &l_oldProtect);
	VirtualProtect(l_patchAddress2, 1, l_newProtect, &l_oldProtect);
	VirtualProtect(l_patchAddress3, 1, l_newProtect, &l_oldProtect);

	void* asinfptr =(void*)&asinf;
	std::vector<uint8_t> data;
	data.push_back(*reinterpret_cast<uint8_t*>(&asinfptr));
	data.push_back(*(reinterpret_cast<uint8_t*>(&asinfptr)+1));
	data.push_back(*(reinterpret_cast<uint8_t*>(&asinfptr)+2));
	data.push_back(*(reinterpret_cast<uint8_t*>(&asinfptr)+3));
	data.push_back(*(reinterpret_cast<uint8_t*>(&asinfptr)+4));
	data.push_back(*(reinterpret_cast<uint8_t*>(&asinfptr)+5));
	data.push_back(*(reinterpret_cast<uint8_t*>(&asinfptr)+6));
	data.push_back(*(reinterpret_cast<uint8_t*>(&asinfptr)+7));
	patch = Mod::get()->patch(l_patchAddress1, data).unwrap();
	patch->enable();
	patch = Mod::get()->patch(l_patchAddress2, { 0xAA }).unwrap();
	patch->enable();
	patch = Mod::get()->patch(l_patchAddress3, { 0x14 }).unwrap();
	patch->enable();

	VirtualProtect(l_patchAddress1, 8, l_oldProtect, &l_newProtect);
	VirtualProtect(l_patchAddress2, 1, l_oldProtect, &l_newProtect);
	VirtualProtect(l_patchAddress3, 1, l_oldProtect, &l_newProtect);
}