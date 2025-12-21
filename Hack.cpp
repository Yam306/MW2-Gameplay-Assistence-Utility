#include "Hack.h"

void hackFunc(HANDLE openProcHandle, Mem MemObj, Offsets offsets)
{
	bool isHackLoopRunning = FALSE;

	std::cout << "Hack ready: Press H/h inside this window to toggle" << std::endl;

	while (TRUE) //create a seperate thread for hack loop
	{
		if (GetAsyncKeyState('H') & 0x8000) {
			isHackLoopRunning = !isHackLoopRunning;
			std::cout << "Hack loop: " << (isHackLoopRunning ? "on" : "off") << std::endl;
			Sleep(100);  // Sleep to avoid multiple toggles from a single key press
		}

		if (isHackLoopRunning) {
			uintptr_t mainWeaponAmmoAddress = MemObj.multiLvlPtrCalc(offsets.mainWeaponAmmoOffset, offsets.mainWeaponAmmoOffsetSize);
			uintptr_t sideWeaponAmmoAddress = MemObj.multiLvlPtrCalc(offsets.sideWeaponAmmoOffset, offsets.sideWeaponAmmoOffsetSize);
			uintptr_t sideWeaponAmmoAddress2 = MemObj.multiLvlPtrCalc(offsets.sideWeaponAmmoOffset2, offsets.sideWeaponAmmoOffsetSize2);

			int mainWeaponAmmo = MemObj.memRead<int>(mainWeaponAmmoAddress, openProcHandle);
			int sideWeaponAmmo = MemObj.memRead<int>(sideWeaponAmmoAddress, openProcHandle);
			int sideWeaponAmmo2 = MemObj.memRead<int>(sideWeaponAmmoAddress2, openProcHandle);
			int fireRate = MemObj.memRead<int>(0x0108DE54, openProcHandle);
			int hP = MemObj.memRead<int>(0x00EA7804, openProcHandle);

			printData<int>("Main Weapon Ammo", mainWeaponAmmo);
			printData<int>("Side Weapon Ammo1", sideWeaponAmmo);
			printData<int>("Side Weapon Ammo2", sideWeaponAmmo2);
			printData<int>("Fire Rate", fireRate);
			printData<int>("HP", hP);

			MemObj.memWrite<int>(mainWeaponAmmoAddress, 100, openProcHandle);
			MemObj.memWrite<int>(sideWeaponAmmoAddress, 100, openProcHandle);
			MemObj.memWrite<int>(sideWeaponAmmoAddress2, 100, openProcHandle);
			MemObj.memWrite<int>(0x0108DE54, 0, openProcHandle); //firerate
			//MemObj.memWrite<int>(0x00EA7804, 90, openProcHandle); //hp
		}

		Sleep(10);
	}
}