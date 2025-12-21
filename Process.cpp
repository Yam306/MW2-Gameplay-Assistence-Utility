#include "Process.h"

Proc::Proc() : pID(0), hProcess(0), moduleBaseAddress(0) {}

Proc::Proc(DWORD inputPID, HANDLE hProcessInput) : pID(inputPID), hProcess(hProcessInput), moduleBaseAddress(0) {}

int Proc::GetProcessIDByName(const wchar_t* inputExeName)
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		std::cerr << "!Error in CreateToolhelp32Snapshot (GPIDBN): " << GetLastError() << std::endl;
		return 0;
	}

	if (Process32FirstW(hProcessSnap, &pe32) == FALSE)
	{
		std::cerr << "!Error in Process32FirstW (GPIDBN): " << GetLastError() << std::endl;
		CloseHandle(hProcessSnap);
		return 0;
	}

	else if (Process32FirstW(hProcessSnap, &pe32) == TRUE)
	{
		do
		{
			if (wcscmp(pe32.szExeFile, inputExeName) == 0)
			{
				Proc::pID = pe32.th32ProcessID;
				CloseHandle(hProcessSnap);
				break;
			}
		} while (Process32Next(hProcessSnap, &pe32));
	}

	if (Proc::pID == 0)
	{
		std::cerr << "!Error PID == 0 (GPIDBN): " << GetLastError() << std::endl;
		return 0;
	}

	return 1;
}

int Proc::GetProcessHandle(DWORD inputPID, DWORD procAccess, BOOL inheritHandle)
{
	if (inputPID == 0)
	{
		inputPID = Proc::pID;
	}

	HANDLE handleToProc = OpenProcess(procAccess, inheritHandle, inputPID);

	if (handleToProc == NULL)
	{
		std::cerr << "!Error in OpenProcess (GPH): " << GetLastError() << std::endl;
		return 0;
	}

	else if (handleToProc != NULL)
	{
		Proc::hProcess = handleToProc;
	}

	return 1;
}

int Proc::GetModuleBaseAddress(const wchar_t* inputModuleName, DWORD inputPID)
{
	if (inputPID == 0)
	{
		inputPID = Proc::pID;
	}

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, inputPID); //flags must be passed with |

	if (hSnap == INVALID_HANDLE_VALUE)
	{
		std::cerr << "!Error in CreateToolhelp32Snapshot (GMBA): " << GetLastError() << std::endl;
		return 0;
	}

	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);

		if (Module32First(hSnap, &moduleEntry) == FALSE)
		{
			std::cerr << "!Error in Module32First (GMBA): " << GetLastError() << std::endl;
			return 0;
		}

		else if (Module32First(hSnap, &moduleEntry) == TRUE) {
			do {
				if (_wcsicmp(moduleEntry.szModule, inputModuleName) == 0) {
					uintptr_t currModBaseAddr = ((uintptr_t)moduleEntry.modBaseAddr);
					Proc::moduleBaseAddress.push_back(currModBaseAddr);
				}
			} while (Module32Next(hSnap, &moduleEntry));
		}

		CloseHandle(hSnap);
	}

	if (Proc::moduleBaseAddress.empty()) {
		std::cerr << "!Error moduleBaseAddress vector empty (GMBA): " << GetLastError() << std::endl;
		return 0;
	}

	return 1;
}

HANDLE Proc::retrHProcess()
{
	return Proc::hProcess;
}

std::vector<uintptr_t> Proc::retrModBaseAddr()
{
	return Proc::moduleBaseAddress;
}
