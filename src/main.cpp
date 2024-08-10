#include <Geode/Geode.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
	Patch* patch;
	void* l_patchAddress1 = reinterpret_cast<void*>(geode::base::get() + 0x2a6d5a);
	void* l_patchAddress2 = reinterpret_cast<void*>(geode::base::get() + 0x2a6e6c);
	void* l_patchAddress3 = reinterpret_cast<void*>(geode::base::get() + 0x2a6ee8);
	void* l_patchAddress4 = reinterpret_cast<void*>(geode::base::get() + 0x2a6eba);
	DWORD l_oldProtect;
	DWORD l_newProtect = 0x40;
	VirtualProtect(l_patchAddress1, 6, l_newProtect, &l_oldProtect);
	VirtualProtect(l_patchAddress2, 2, l_newProtect, &l_oldProtect);
	VirtualProtect(l_patchAddress3, 2, l_newProtect, &l_oldProtect);
	VirtualProtect(l_patchAddress4, 2, l_newProtect, &l_oldProtect);

	patch = Mod::get()->patch(l_patchAddress1, { 0xe9, 0xc9, 0x00, 0x00, 0x00, 0x90 }).unwrap();
	patch->enable();
	patch = Mod::get()->patch(l_patchAddress2, { 0x90, 0x90 }).unwrap();
	patch->enable();
	patch = Mod::get()->patch(l_patchAddress3, { 0x90, 0x90 }).unwrap();
	patch->enable();
	patch = Mod::get()->patch(l_patchAddress4, { 0x90, 0x90 }).unwrap();
	patch->enable();
	
	VirtualProtect(l_patchAddress1, 6, l_oldProtect, &l_newProtect);
	VirtualProtect(l_patchAddress2, 2, l_oldProtect, &l_newProtect);
	VirtualProtect(l_patchAddress3, 2, l_oldProtect, &l_newProtect);
	VirtualProtect(l_patchAddress4, 2, l_oldProtect, &l_newProtect);
}