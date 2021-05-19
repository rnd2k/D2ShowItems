#define _D2VARS_H

#include "DLLmain.h"
#include "D2Patch.h"

/****************************************************************************
*                                                                           *
*   DLLmain.h                                                               *
*                                                                           *
*   Licensed under the Apache License, Version 2.0 (the "License");         *
*   you may not use this file except in compliance with the License.        *
*   You may obtain a copy of the License at                                 *
*                                                                           *
*   http://www.apache.org/licenses/LICENSE-2.0                              *
*                                                                           *
*   Unless required by applicable law or agreed to in writing, software     *
*   distributed under the License is distributed on an "AS IS" BASIS,       *
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*
*   See the License for the specific language governing permissions and     *
*   limitations under the License.                                          *
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*   https://github.com/olivier-verville/D2Template                          *
*                                                                           *
*   D2Template core file, do not modify unless you know what you're doing   *
*                                                                           *
*****************************************************************************/

//LPVOID pBuf;

void __fastcall D2TEMPLATE_FatalError(char* szMessage)
{
    MessageBoxA(NULL, szMessage, "D2ShowItems", MB_OK | MB_ICONERROR);
    TerminateProcess(GetCurrentProcess(), -1);
}

BOOL __fastcall D2TEMPLATE_ApplyPatch(void* hGame, const DLLPatchStrc* hPatch)
{
    while (hPatch->nDLL != D2DLL_INVALID)
    {
        int nReturn = 0;
        int nDLL = hPatch->nDLL;
        if (nDLL < 0 || nDLL >= D2DLL_INVALID) return FALSE;
        
        DWORD dwAddress = hPatch->dwAddress;
        if (!dwAddress) return FALSE;

        DWORD dwBaseAddress = gptDllFiles[nDLL].dwAddress;
        if (!dwBaseAddress) return FALSE;

        dwAddress += dwBaseAddress;
        
        DWORD dwData = hPatch->dwData;
        if (hPatch->bRelative)
		{ dwData = dwData - (dwAddress + sizeof(dwData)); }
        
        void* hAddress = (void*)dwAddress;
        DWORD dwOldPage;

        if (hPatch->nPatchSize > 0)
        {
			BYTE Buffer[1024] = { 0 };

            for (size_t i = 0; i < hPatch->nPatchSize; i++)
                Buffer[i] = (BYTE)dwData;

            VirtualProtect(hAddress, hPatch->nPatchSize, PAGE_EXECUTE_READWRITE, &dwOldPage);
            nReturn = WriteProcessMemory(hGame, hAddress, &Buffer, hPatch->nPatchSize, 0);
            VirtualProtect(hAddress, hPatch->nPatchSize, dwOldPage, 0);
        }

        else
        {
            VirtualProtect(hAddress, sizeof(dwData), PAGE_EXECUTE_READWRITE, &dwOldPage);
            nReturn = WriteProcessMemory(hGame, hAddress, &dwData, sizeof(dwData), 0);
            VirtualProtect(hAddress, sizeof(dwData), dwOldPage, 0);
        }
        
        if (nReturn == 0) return FALSE;
        
        hPatch++;
    }
    
    return TRUE;
}

BOOL __fastcall D2TEMPLATE_LoadModules()
{
    for (int i = 0; i < D2DLL_INVALID; i++)
    {
        DLLBaseStrc* hDllFile = &gptDllFiles[i];
        
        void* hModule = GetModuleHandle(hDllFile->szName);
        if (!hModule)
        {
            hModule = LoadLibrary(hDllFile->szName);
        }

        hDllFile->dwAddress = (DWORD)hModule;
    }

    return TRUE;
}

int __fastcall D2TEMPLATE_GetDebugPrivilege()
{
    void* hToken;
    LUID luid;
    TOKEN_PRIVILEGES tokenPrivileges;

    if (OpenProcessToken(GetCurrentProcess(),TOKEN_ALL_ACCESS,&hToken) == 0)
    {
        D2TEMPLATE_FatalError("OpenProcessToken Failed");
        return 0;
    }

    if (LookupPrivilegeValue(0,SE_DEBUG_NAME,&luid) == 0)
    {
        D2TEMPLATE_FatalError("LookupPrivilegeValue Failed");
        CloseHandle(hToken);
        return 0;
    }

    tokenPrivileges.PrivilegeCount = 1;
    tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tokenPrivileges.Privileges[0].Luid = luid;
    if (AdjustTokenPrivileges(hToken,0,&tokenPrivileges,sizeof(tokenPrivileges),0,0) == 0)
    {
        D2TEMPLATE_FatalError("AdjustTokenPrivileges Failed");
        CloseHandle(hToken);
        return 0;
    }

    CloseHandle(hToken);
    return 1;
}

IMAGE_NT_HEADERS* GetHeader(LPBYTE pBase) {
	if (pBase == NULL)
		return NULL;

	IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)pBase;

	if (IsBadReadPtr(pDosHeader, sizeof(IMAGE_DOS_HEADER)))
		return NULL;

	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return NULL;

	IMAGE_NT_HEADERS* pHeader = (IMAGE_NT_HEADERS*)(pBase + pDosHeader->e_lfanew);
	if (IsBadReadPtr(pHeader, sizeof(IMAGE_NT_HEADERS)))
		return NULL;

	if (pHeader->Signature != IMAGE_NT_SIGNATURE)
		return NULL;

	return pHeader;
}


int __stdcall DllAttach()
{
    D2TEMPLATE_GetDebugPrivilege();

    void* hGame = GetCurrentProcess();
    if (!hGame) 
    {
        D2TEMPLATE_FatalError("Failed to retrieve process");
        return 0;
    }

    if (!D2TEMPLATE_LoadModules())
    {
        D2TEMPLATE_FatalError("Failed to load modules");
        return 0;
    }

	// Allocate additional memory for items
	// 0x120 bytes per item = ~ maximum 3500 items per screen
	pBuf = VirtualAlloc(0, 0xF7000, MEM_COMMIT + MEM_RESERVE, PAGE_READWRITE);

	LPBYTE pBase = (LPBYTE) DLLBASE_D2CLIENT;
	IMAGE_NT_HEADERS* pHeader;

	// Check version and patch D2Client.dll
	// D2Client.dll entry points
	// 0x000C234D	1.09b
	// 0x000C16CD	1.09d
	// 0x000C1C1D	1.10f
	// 0x000045EE	1.11b
	// 0x000045FA	1.12a
	// 0x000045F6	1.13c
	// 0x000045DE	1.13d
	if (pBase != NULL) {
		pHeader = GetHeader(pBase);
		if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000C234D) {
			D2TEMPLATE_ApplyPatch(hGame, gptD2Client109b);
		}
		if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000C16CD) {
			D2TEMPLATE_ApplyPatch(hGame, gptD2Client109d);
		}
		if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000C1C1D) {
			D2TEMPLATE_ApplyPatch(hGame, gptD2Client110f);
		}
		if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000045EE) {
			D2TEMPLATE_ApplyPatch(hGame, gptD2Client111b);
		}
		if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000045FA) {
			D2TEMPLATE_ApplyPatch(hGame, gptD2Client112a);
		}
		if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000045F6) {
			D2TEMPLATE_ApplyPatch(hGame, gptD2Client113c);
		}
		if (pHeader->OptionalHeader.AddressOfEntryPoint == 0x000045DE) {
			D2TEMPLATE_ApplyPatch(hGame, gptD2Client113d);
		}
	}

    return 1;
}

int __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, void* lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
			{
				if (!DllAttach()) D2TEMPLATE_FatalError("Couldn't attach to Diablo II");
				break;
			}
		case DLL_PROCESS_DETACH:
			{
				VirtualFree(pBuf, 0, MEM_RELEASE);
			}
    }

    return TRUE;
}

DWORD __fastcall GetDllOffset(char* ModuleName, DWORD BaseAddress, int Offset)
{
	if(!BaseAddress)
		BaseAddress = (DWORD)LoadLibraryA(GetModuleExt(ModuleName));

	if(Offset < 0)
		return (DWORD)GetProcAddress((HMODULE)BaseAddress,(LPCSTR)(-Offset));

	return BaseAddress + Offset;
}

char* __fastcall GetModuleExt(char* ModuleName)
{
	char DLLExt[] = ".dll";
	char DLLName[32] = {0};
	strcpy(DLLName,ModuleName);
	return strcat(DLLName,DLLExt);
}