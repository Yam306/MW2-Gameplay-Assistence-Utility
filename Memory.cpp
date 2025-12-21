#include "Memory.h"

Mem::Mem() : hProcess(0), moduleBaseAddress(0) {}

Mem::Mem(HANDLE hProcessInput, uintptr_t moduleBaseAddressInput)
   : hProcess(hProcessInput), moduleBaseAddress(moduleBaseAddressInput) {}

uintptr_t Mem::multiLvlPtrCalc(uintptr_t offsetArray[], std::size_t offsetArraySize, uintptr_t moduleBaseAddressInput, HANDLE hProcessInput)
{
	if (hProcessInput == 0)
	{
		hProcessInput = Mem::hProcess;
	}

	if (moduleBaseAddressInput == 0)
	{
		moduleBaseAddressInput = Mem::moduleBaseAddress;
	}

	uintptr_t currentAddress = moduleBaseAddressInput;

	for (std::size_t i = 0; i < offsetArraySize - 1; ++i)
	{
		currentAddress = currentAddress + offsetArray[i];
		currentAddress = Mem::memRead<uintptr_t>(currentAddress, hProcessInput);
	}

	uintptr_t finalAddress = currentAddress + offsetArray[offsetArraySize - 1];

	return finalAddress;
}

Mem::~Mem() 
{
	CloseHandle(Mem::hProcess);
}