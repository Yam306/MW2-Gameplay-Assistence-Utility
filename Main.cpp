#include "Process.h"
#include "Memory.h"
#include "Hack.h"

int main()
{
	Offsets offsets;

	//Process Setup
	Proc ProcObj;

	const wchar_t* exeName = L"iw4sp.exe";
	ProcObj.GetProcessIDByName(exeName);

	ProcObj.GetProcessHandle();

	const wchar_t* moduleName = L"iw4sp.exe";
	ProcObj.GetModuleBaseAddress(moduleName);

	HANDLE openProcHandle = ProcObj.retrHProcess();

	std::vector<uintptr_t> moduleBaseAddressVector = ProcObj.retrModBaseAddr();
	uintptr_t moduleBaseAddress = moduleBaseAddressVector[0]; //here

	//Memory Setup
	Mem MemObj(openProcHandle, moduleBaseAddress);

	hackFunc(openProcHandle, MemObj, offsets);

	return 0;
}