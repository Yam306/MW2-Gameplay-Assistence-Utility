#pragma once
#include <windows.h>
#include <cstddef>
#include <iostream>

class Mem {
public:
	Mem();

	Mem(HANDLE hProcessInput, uintptr_t moduleBaseAddressInput);

	template <typename T> //usage: memRead<expected_return_type>(inputAddress, hProcess)
	T memRead(uintptr_t inputAddress, HANDLE hProcessInput = 0)
	{
		if (hProcess == 0)
		{
			hProcessInput = Mem::hProcess;
		}

		LPCVOID lpBaseAddress = reinterpret_cast<LPCVOID>(inputAddress);
		LPVOID lpBuffer;
		SIZE_T nSize = sizeof(lpBuffer);
		SIZE_T lpNumberOfBytesRead;
		BOOL eval = ReadProcessMemory(hProcessInput, lpBaseAddress, &lpBuffer, nSize, &lpNumberOfBytesRead);

		if (eval == 0)
		{
			std::cerr << "!Error in ReadProcessMemory (memRead): " << GetLastError() << std::endl;
			return 0;
		}

		T lpBufferCasted = reinterpret_cast<T>(lpBuffer);

		return lpBufferCasted;
	}

	template <typename T> //usage: memWrite<write_value_type>(inputAddress, write_value, hProcess)
	int memWrite(uintptr_t inputAddress, T inputBuffer, HANDLE hProcessInput = 0)
	{
		if (hProcess == 0)
		{
			hProcessInput = Mem::hProcess;
		}

		LPVOID lpBaseAddress = reinterpret_cast<LPVOID>(inputAddress);
		LPCVOID lpBuffer = reinterpret_cast<LPCVOID>(inputBuffer);
		SIZE_T nSize = sizeof(lpBuffer);
		SIZE_T lpNumberOfBytesWritten;
		BOOL eval = WriteProcessMemory(hProcessInput, lpBaseAddress, &lpBuffer, nSize, &lpNumberOfBytesWritten);

		if (eval == 0)
		{
			std::cerr << "!Error in WriteProcessMemory (memWrite): " << GetLastError() << std::endl;
			return 0;
		}

		return 1;
	}

	uintptr_t multiLvlPtrCalc(uintptr_t offsetArray[], std::size_t offsetArraySize, uintptr_t moduleBaseAddressInput = 0, HANDLE hProcessInput = 0);

	~Mem();

private:
	HANDLE hProcess;
	uintptr_t moduleBaseAddress;
};
