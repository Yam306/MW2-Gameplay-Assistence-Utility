#pragma once
#include <windows.h>
#include <tlhelp32.h> //used in the get PID func
#include <iostream>
#include <string>
#include <vector>

class Proc
{
public:
	Proc();

	Proc(DWORD inputPID, HANDLE hProcessInput);

	int GetProcessIDByName(const wchar_t* inputExeName);

	int GetProcessHandle(DWORD inputPID = 0, DWORD procAccess = PROCESS_ALL_ACCESS, BOOL inheritHandle = FALSE);

	int GetModuleBaseAddress(const wchar_t* inputModuleName, DWORD inputPID = 0);

	HANDLE retrHProcess();

	std::vector<uintptr_t> retrModBaseAddr();

private:
	DWORD pID;
	HANDLE hProcess;
	std::vector<uintptr_t> moduleBaseAddress;
};
