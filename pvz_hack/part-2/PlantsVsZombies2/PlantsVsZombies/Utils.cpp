#include "stdafx.h"
#include "Utils.h"

HANDLE hGame = NULL;

void WriteMemoryBYTES(unsigned int uAddress, void* bytes, unsigned int len)
{
	DWORD flOldProtect;
	SIZE_T uNumberOfBytesWritten;
	HANDLE hProcess;

	if ((hProcess = hGame) && len)
	{
		VirtualProtectEx(hProcess, (LPVOID)uAddress, len, PAGE_WRITECOPY, &flOldProtect);
		WriteProcessMemory(hProcess, (LPVOID)uAddress, bytes, len, &uNumberOfBytesWritten);
		FlushInstructionCache(hProcess, (LPVOID)uAddress, len);
		VirtualProtectEx(hProcess, (LPVOID)uAddress, len, flOldProtect, &flOldProtect);
	}
}

void WriteMemoryQWORD(unsigned int uAddress, unsigned __int64 value) { WriteMemoryBYTES(uAddress, &value, sizeof(unsigned __int64)); }
void WriteMemoryDWORD(unsigned int uAddress, unsigned int value) { WriteMemoryBYTES(uAddress, &value, sizeof(unsigned int)); }
void WriteMemoryWORD(unsigned int uAddress, unsigned short value) { WriteMemoryBYTES(uAddress, &value, sizeof(unsigned short)); }
void WriteMemoryBYTE(unsigned int uAddress, unsigned char value) { WriteMemoryBYTES(uAddress, &value, sizeof(unsigned char)); }

void NOPMemory(unsigned int uAddress, unsigned int len)
{
	unsigned int dword_count = (len / 4), byte_count = (len % 4);
	unsigned char Byte = 0x90;
	unsigned int Dword = 0x90666666;

	DWORD flOldProtect;
	SIZE_T uNumberOfBytesWritten;
	HANDLE hProcess;

	if ((hProcess = hGame) && len)
	{
		VirtualProtectEx(hProcess, (LPVOID)uAddress, len, PAGE_WRITECOPY, &flOldProtect);
		while (dword_count != NULL)
		{
			WriteProcessMemory(hProcess, (LPVOID)uAddress, &Dword, sizeof(unsigned int), &uNumberOfBytesWritten);
			uAddress += sizeof(unsigned int);
			dword_count--;
		}
		while (byte_count != NULL)
		{
			WriteProcessMemory(hProcess, (LPVOID)uAddress, &Byte, sizeof(unsigned char), &uNumberOfBytesWritten);
			uAddress += sizeof(unsigned char);
			byte_count--;
		}
		FlushInstructionCache(hProcess, (LPVOID)uAddress, len);
		VirtualProtectEx(hProcess, (LPVOID)uAddress, len, flOldProtect, &flOldProtect);
	}
}

void NULLMemory(unsigned int uAddress, unsigned int len)
{
	unsigned int dword_count = (len / 4), byte_count = (len % 4);
	unsigned char Byte = 0x00;
	unsigned int Dword = 0x00000000;

	DWORD flOldProtect;
	SIZE_T uNumberOfBytesWritten;
	HANDLE hProcess;

	if ((hProcess = hGame) && len)
	{
		VirtualProtectEx(hProcess, (LPVOID)uAddress, len, PAGE_WRITECOPY, &flOldProtect);
		while (dword_count != NULL)
		{
			WriteProcessMemory(hProcess, (LPVOID)uAddress, &Dword, sizeof(unsigned int), &uNumberOfBytesWritten);
			uAddress += sizeof(unsigned int);
			dword_count--;
		}
		while (byte_count != NULL)
		{
			WriteProcessMemory(hProcess, (LPVOID)uAddress, &Byte, sizeof(unsigned char), &uNumberOfBytesWritten);
			uAddress += sizeof(unsigned char);
			byte_count--;
		}
		FlushInstructionCache(hProcess, (LPVOID)uAddress, len);
		VirtualProtectEx(hProcess, (LPVOID)uAddress, len, flOldProtect, &flOldProtect);
	}
}

void WriteInstruction(unsigned int uAddress, unsigned int uDestination, unsigned char uFirstByte)
{
	unsigned char ExecLine[5];
	ExecLine[0] = uFirstByte;
	*((int*)(ExecLine + 1)) = (((int)uDestination) - (((int)uAddress) + 5));
	WriteMemoryBYTES(uAddress, ExecLine, 5);
}

void WriteInstructionCallJmpEax(unsigned int uAddress, unsigned int uDestination, unsigned int uNopEnd)
{
	unsigned char ExecLine[7];
	ExecLine[0] = 0xE8;
	*((int*)(ExecLine + 1)) = (((int)uDestination) - (((int)uAddress) + 5));
	*((unsigned short*)(ExecLine + 5)) = 0xE0FF;
	WriteMemoryBYTES(uAddress, ExecLine, 7);
	if (uNopEnd && uNopEnd > (uAddress + 7))
		NOPMemory((uAddress + 7), (uNopEnd - (uAddress + 7)));
}

void WriteInstructionCall(unsigned int uAddress, unsigned int uDestination, unsigned int uNopEnd)
{
	unsigned char ExecLine[5];
	ExecLine[0] = 0xE8;
	*((int*)(ExecLine + 1)) = (((int)uDestination) - (((int)uAddress) + 5));
	WriteMemoryBYTES(uAddress, ExecLine, 5);
	if (uNopEnd && uNopEnd > (uAddress + 5))
		NOPMemory((uAddress + 5), (uNopEnd - (uAddress + 5)));
}

void WriteInstructionJmp(unsigned int uAddress, unsigned int uDestination, unsigned int uNopEnd)
{
	unsigned char ExecLine[5];
	ExecLine[0] = 0xE9;
	*((int*)(ExecLine + 1)) = (((int)uDestination) - (((int)uAddress) + 5));
	WriteMemoryBYTES(uAddress, ExecLine, 5);
	if (uNopEnd && uNopEnd > (uAddress + 5))
		NOPMemory((uAddress + 5), (uNopEnd - (uAddress + 5)));
}

void Msg(const char* title, const char* format, ...)
{
	char pBuff[MSG_BUFFER_SIZE];
	va_list va;
	va_start(va, format);
	UINT32 ret_size = (UINT32)vsprintf_s(pBuff, MSG_BUFFER_SIZE, format, va);
	if (ret_size < MSG_BUFFER_SIZE)
		MessageBoxA(NULL, pBuff, title, MB_OK);
	va_end(va);
}

void Msg(const wchar_t* title, const wchar_t* format, ...)
{
	wchar_t pBuff[MSG_BUFFER_SIZE];
	va_list va;
	va_start(va, format);
	UINT32 ret_size = (UINT32)vswprintf_s(pBuff, MSG_BUFFER_SIZE, format, va);
	if (ret_size < MSG_BUFFER_SIZE)
		MessageBoxW(NULL, pBuff, title, MB_OK);
	va_end(va);
}