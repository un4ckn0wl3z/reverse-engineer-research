#include "stdafx.h"

void DllInitializer(HMODULE hDllModule)
{
	if (((UINT64)hDllModule) < 0x7E000000 && ((UINT64)(&hGame)) < 0x7F000000)
	{
		if (*((UINT64*)0x401000) == 0xAE76E8CE8B575553)
		{
			if ((hGame = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, GetCurrentProcessId())))
			{
				//WriteMemoryWORD(0x006B5B17, 0x026A);

				CloseHandle(hGame);
				hGame = NULL;
			}
			else
			{
				Msg(_T("ERROR"), _T("[%s]\n Cannot injected"), __WFILE__);
				ExitProcess(1);
			}
		}
		else
		{
			Msg(_T("ERROR"), _T("[%s]\n ERROR"), __WFILE__);
			ExitProcess(1);
		}
	}
	else
	{
		Msg(_T("ERROR"), _T("[%s]\n ERROR"), __WFILE__);
		ExitProcess(1);
	}
}

__declspec(dllexport) BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DllInitializer(hModule);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

