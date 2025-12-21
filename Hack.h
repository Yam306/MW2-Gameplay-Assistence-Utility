#pragma once
#include "Process.h"
#include "Memory.h"
#include "Offsets.h"

template <typename T>
void printData(std::string currentDataString, T currentData)
{
	std::cout << currentDataString << ": " << currentData << std::endl;
}

void hackFunc(HANDLE openProcHandle, Mem MemObj, Offsets offsets);
