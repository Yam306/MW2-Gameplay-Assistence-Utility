#pragma once
#include <cstdint>
#include <cstddef>

struct Offsets
{
	uintptr_t mainWeaponAmmoOffset[1] = { 0xC8DFBC };
	std::size_t mainWeaponAmmoOffsetSize = sizeof(mainWeaponAmmoOffset) / sizeof(uintptr_t);

	uintptr_t sideWeaponAmmoOffset[1] = { 0xC8DFD4 };
	std::size_t sideWeaponAmmoOffsetSize = sizeof(sideWeaponAmmoOffset) / sizeof(uintptr_t);

	uintptr_t sideWeaponAmmoOffset2[1] = { 0xC8DFC8 };
	std::size_t sideWeaponAmmoOffsetSize2 = sizeof(sideWeaponAmmoOffset2) / sizeof(uintptr_t);
};