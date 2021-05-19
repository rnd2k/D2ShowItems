#pragma once

#ifndef _D2PATCH_H
#define _D2PATCH_H

#include "D2PatchConst.h"

/****************************************************************************
*                                                                           *
*   D2Patch.h                                                               *
*   Copyright (C) Olivier Verville                                          *
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
*   This file is where you declare all your patches, in order to inject     *
*   your own code into the game. Each patch should be declared in the       *
*   array, in order to be handled by D2Template's patcher                   *
*                                                                           *
*****************************************************************************/

//struct DLLPatchStrc
//{
//	int nDLL;
//	DWORD dwAddress;
//	DWORD dwData;
//	BOOL bRelative;
//	size_t nPatchSize;
//};


// Inject code for version 1.09b, 1.09d, 1.10f


// MOV EAX,OFFSET pBuf
__declspec(naked) void D2Func_1_109b_110f () {
	__asm
	{
		mov eax, pBuf
		retn
	}
}

// MOV EAX,DWORD PTR DS:[EAX+pBuf]
__declspec(naked) void D2Func_2_109b_110f () {
	__asm
	{
		pushfd
		push esi
		mov esi, pBuf
		mov eax, [eax+esi]
		pop esi
		popfd
		retn
	}
}

//MOV EAX,DWORD PTR DS:[EDX+pBuf+0x8]
__declspec(naked) void D2Func_3_109b_110f () {
	__asm
	{
		pushfd
		push esi
		mov esi, pBuf
		add esi, 0x8
		mov eax, [edx+esi]
		pop esi
		popfd
		retn
	}
}

//MOV EAX,DWORD PTR DS:[EAX+pBuf+0x4]
__declspec(naked) void D2Func_4_109b_110f () {
	__asm
	{
		pushfd
		push esi
		mov esi, pBuf
		add esi, 0x4
		mov eax, [eax+esi]
		pop esi
		popfd
		retn
	}
}

//MOV EAX,DWORD PTR DS:[ECX+pBuf+0xC]
__declspec(naked) void D2Func_5_109b_110f () {
	__asm
	{
		pushfd
		push esi
		mov esi, pBuf
		add esi, 0xC
		mov eax, [ecx+esi]
		pop esi
		popfd
		retn
	}
}

//ADD ESI,OFFSET pBuf
__declspec(naked) void D2Func_6_109b_110f () {
	__asm
	{
		pushfd
		add esi, pBuf
		popfd
		retn
	}
}

//MOV ESI,OFFSET pBuf+0x118
__declspec(naked) void D2Func_7_109b_110f () {
	__asm
	{
		pushfd
		mov esi, pBuf
		add esi, 0x118
		popfd
		retn
	}
}


// Inject code for version 1.11b, 1.12a, 1.13c, 1.13d


// MOV EAX,OFFSET pBuf
__declspec(naked) void D2Func_1_111b_113d () {
	__asm
	{
		mov eax, pBuf
		retn
	}
}

//MOV EAX,DWORD PTR DS:[EAX+pBuf]
__declspec(naked) void D2Func_2_111b_113d () {
	__asm
	{
		pushfd
		push esi
		mov esi, pBuf
		mov eax, [eax+esi]
		pop esi
		popfd
		retn
	}
}

//MOV EAX,DWORD PTR DS:[ECX+pBuf+0x8]
__declspec(naked) void D2Func_3_111b_113d () {
	__asm
	{
		pushfd
		push esi
		mov esi, pBuf
		add esi, 0x8
		mov eax, [ecx+esi]
		pop esi
		popfd
		retn
	}
}

//MOV EAX,DWORD PTR DS:[EAX+pBuf+0x4]
__declspec(naked) void D2Func_4_111b_113d () {
	__asm
	{
		pushfd
		push esi
		mov esi, pBuf
		add esi, 0x4
		mov eax, [eax+esi]
		pop esi
		popfd
		retn
	}
}

//MOV EAX,DWORD PTR DS:[ECX+pBuf+0xC]
__declspec(naked) void D2Func_5_111b_113d () {
	__asm
	{
		pushfd
		push esi
		mov esi, pBuf
		add esi, 0xC
		mov eax, [ecx+esi]
		pop esi
		popfd
		retn
	}
}

//ADD EBP,OFFSET pBuf
__declspec(naked) void D2Func_6_111b_113d () {
	__asm
	{
		pushfd
		add ebp, pBuf
		popfd
		retn
	}
}

//MOV ESI,OFFSET pBuf+0x118
__declspec(naked) void D2Func_7_111b_113d () {
	__asm
	{
		pushfd
		mov esi, pBuf
		add esi, 0x118
		popfd
		retn
	}
}


static const DLLPatchStrc gptD2Client109b[] =
{
	/*
		All your patches should be added here
		Keep it organized to save yourself some headache
	*/

	//6FB03A34  $+63A34   |.  B8 9024BC6F   MOV EAX,OFFSET 6FBC2490
	{D2DLL_D2CLIENT, 0x63A34, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63A35, (DWORD)D2Func_1_109b_110f, TRUE, 0x0},

	//6FB03ABA  $+63ABA   |.  8B80 F012BC6F MOV EAX,DWORD PTR DS:[EAX+6FBC12F0]
	{D2DLL_D2CLIENT, 0x63ABA, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63ABB, (DWORD)D2Func_2_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x63ABF, 0x90, FALSE, 0x1},

	//6FB03AE3  $+63AE3   |.  8B82 F812BC6F MOV EAX,DWORD PTR DS:[EDX+6FBC12F8]
	{D2DLL_D2CLIENT, 0x63AE3, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63AE4, (DWORD)D2Func_3_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x63AE8, 0x90, FALSE, 0x1},

	//6FB03B1F  $+63B1F   |.  8B80 F412BC6F MOV EAX,DWORD PTR DS:[EAX+6FBC12F4]
	{D2DLL_D2CLIENT, 0x63B1F, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63B20, (DWORD)D2Func_4_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x63B24, 0x90, FALSE, 0x1},

	//6FB03B32  $+63B32   |.  8B81 FC12BC6F MOV EAX,DWORD PTR DS:[ECX+6FBC12FC]
	{D2DLL_D2CLIENT, 0x63B32, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63B33, (DWORD)D2Func_5_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x63B37, 0x90, FALSE, 0x1},

	//6FB03C23  $+63C23   |.  81C6 F012BC6F ||ADD ESI,OFFSET 6FBC12F0
	{D2DLL_D2CLIENT, 0x63C23, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63C24, (DWORD)D2Func_6_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x63C28, 0x90, FALSE, 0x1},

	//6FB03FC2  $+63FC2   |.  BE 0814BC6F   MOV ESI,OFFSET 6FBC1408
	{D2DLL_D2CLIENT, 0x63FC2, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63FC3, (DWORD)D2Func_7_109b_110f, TRUE, 0x0},

	//6FB03A09  $+63A09   |.  83F8 20       CMP EAX,20
	//6FB03A0C  $+63A0C   |.  7C 1B         JL SHORT 6FB03A29

	// change to

	// NOP
	// NOP
	// NOP
	// JMP SHORT 6FB03A29

	{D2DLL_D2CLIENT, 0x63A09, (DWORD)PATCH_NOPBLOCK, FALSE, 0x3},
	{D2DLL_D2CLIENT, 0x63A0C, 0xEB, FALSE, 0x1},
	{D2DLL_D2CLIENT, 0x63A0D, 0x1B, FALSE, 0x1},

	//6FB03C10  $+63C10   |.  83F8 20       ||CMP EAX,20
	//6FB03C13  $+63C13   |.  0F8D 7E030000 ||JGE 6FB03F97

	// change to nops

	{D2DLL_D2CLIENT, 0x63C10, (DWORD)PATCH_NOPBLOCK, FALSE, 0x9},
    {D2DLL_INVALID} // this must be the last entry in the array!
};


static const DLLPatchStrc gptD2Client109d[] =
{
	//6FB03A34  $+63A34   |.  B8 F012BC6F   MOV EAX,OFFSET 6FBC12F0
	{D2DLL_D2CLIENT, 0x63A34, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63A35, (DWORD)D2Func_1_109b_110f, TRUE, 0x0},

	//6FB03ABA  $+63ABA   |.  8B80 F012BC6F MOV EAX,DWORD PTR DS:[EAX+6FBC12F0]
	{D2DLL_D2CLIENT, 0x63ABA, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63ABB, (DWORD)D2Func_2_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x63ABF, 0x90, FALSE, 0x1},

	//6FB03AE3  $+63AE3   |.  8B82 F812BC6F MOV EAX,DWORD PTR DS:[EDX+6FBC12F8]
	{D2DLL_D2CLIENT, 0x63AE3, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63AE4, (DWORD)D2Func_3_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x63AE8, 0x90, FALSE, 0x1},

	//6FB03B1F  $+63B1F   |.  8B80 F412BC6F MOV EAX,DWORD PTR DS:[EAX+6FBC12F4]
	{D2DLL_D2CLIENT, 0x63B1F, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63B20, (DWORD)D2Func_4_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x63B24, 0x90, FALSE, 0x1},

	//6FB03B32  $+63B32   |.  8B81 FC12BC6F MOV EAX,DWORD PTR DS:[ECX+6FBC12FC]
	{D2DLL_D2CLIENT, 0x63B32, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63B33, (DWORD)D2Func_5_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x63B37, 0x90, FALSE, 0x1},

	//6FB03C23  $+63C23   |.  81C6 F012BC6F ||ADD ESI,OFFSET 6FBC12F0
	{D2DLL_D2CLIENT, 0x63C23, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63C24, (DWORD)D2Func_6_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x63C28, 0x90, FALSE, 0x1},

	//6FB03FC2  $+63FC2   |.  BE 0814BC6F   MOV ESI,OFFSET 6FBC1408
	{D2DLL_D2CLIENT, 0x63FC2, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x63FC3, (DWORD)D2Func_7_109b_110f, TRUE, 0x0},


	//6FB03A09  $+63A09   |.  83F8 20       CMP EAX,20
	//6FB03A0C  $+63A0C   |.  7C 1B         JL SHORT 6FB03A29

	// change to

	// NOP
	// NOP
	// NOP
	// JMP SHORT 6FB03A29

	{D2DLL_D2CLIENT, 0x63A09, (DWORD)PATCH_NOPBLOCK, FALSE, 0x3},
	{D2DLL_D2CLIENT, 0x63A0C, 0xEB, FALSE, 0x1},
	{D2DLL_D2CLIENT, 0x63A0D, 0x1B, FALSE, 0x1},

	//6FB03C10  $+63C10   |.  83F8 20       ||CMP EAX,20
	//6FB03C13  $+63C13   |.  0F8D 7E030000 ||JGE 6FB03F97

	// change to nops

	{D2DLL_D2CLIENT, 0x63C10, (DWORD)PATCH_NOPBLOCK, FALSE, 0x9},
	{D2DLL_INVALID} // this must be the last entry in the array!
};


static const DLLPatchStrc gptD2Client110f[] =
{
	//6FB09E38  $+69E38   |.  B8 2870BB6F   MOV EAX,OFFSET 6FBB7028 +0x0
	{D2DLL_D2CLIENT, 0x69E38, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x69E39, (DWORD)D2Func_1_109b_110f, TRUE, 0x0},

	//6FB09EBE  $+69EBE   |.  8B80 2870BB6F MOV EAX,DWORD PTR DS:[EAX+6FBB7028] +0x0
	{D2DLL_D2CLIENT, 0x69EBE, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x69EBF, (DWORD)D2Func_2_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x69EC3, 0x90, FALSE, 0x1},

	//6FB09EE7  $+69EE7   |.  8B82 3070BB6F MOV EAX,DWORD PTR DS:[EDX+6FBB7030] +0x8
	{D2DLL_D2CLIENT, 0x69EE7, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x69EE8, (DWORD)D2Func_3_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x69EEC, 0x90, FALSE, 0x1},

	//6FB09F23  $+69F23   |.  8B80 2C70BB6F MOV EAX,DWORD PTR DS:[EAX+6FBB702C] +0x4
	{D2DLL_D2CLIENT, 0x69F23, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x69F24, (DWORD)D2Func_4_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x69F28, 0x90, FALSE, 0x1},

	//6FB09F36  $+69F36   |.  8B81 3470BB6F MOV EAX,DWORD PTR DS:[ECX+6FBB7034] +0xC
	{D2DLL_D2CLIENT, 0x69F36, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x69F37, (DWORD)D2Func_5_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x69F3B, 0x90, FALSE, 0x1},

	//6FB0A03F  $+6A03F   |.  81C6 2870BB6F ||ADD ESI,OFFSET 6FBB7028 +0x0
	{D2DLL_D2CLIENT, 0x6A03F, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x6A040, (DWORD)D2Func_6_109b_110f, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x6A044, 0x90, FALSE, 0x1},

	//6FB0A3C8  $+6A3C8   |.  BE 4071BB6F   MOV ESI,OFFSET 6FBB7140 +0x118
	{D2DLL_D2CLIENT, 0x6A3C8, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x6A3C9, (DWORD)D2Func_7_109b_110f, TRUE, 0x0},

	//6FB09E0D  $+69E0D   |.  83F8 20       CMP EAX,20
	//6FB09E10  $+69E10   |.  7C 1B         JL SHORT 6FB09E2D

	// change to

	// NOP
	// NOP
	// NOP
	// JMP SHORT 6FB09E2D

	{D2DLL_D2CLIENT, 0x69E0D, (DWORD)PATCH_NOPBLOCK, FALSE, 0x3},
	{D2DLL_D2CLIENT, 0x69E10, 0xEB, FALSE, 0x1},
	{D2DLL_D2CLIENT, 0x69E11, 0x1B, FALSE, 0x1},

	//6FB0A02C  $+6A02C   |.  83FE 20       ||CMP ESI,20
	//6FB0A02F  $+6A02F   |.  0F8D 64030000 ||JGE 6FB0A399

	// change to nops

	{D2DLL_D2CLIENT, 0x6A02C, (DWORD)PATCH_NOPBLOCK, FALSE, 0x9},
	{D2DLL_INVALID} // this must be the last entry in the array!
};


static const DLLPatchStrc gptD2Client111b[] =
{
	//$+5D7F2   |.  B8 B80EBD6F   MOV EAX,OFFSET 6FBD0EB8 +0x0
	{D2DLL_D2CLIENT, 0x5D7F2, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x5D7F3, (DWORD)D2Func_1_111b_113d, TRUE, 0x0},

	//$+5D875   |.  8B80 B80EBD6F MOV EAX,DWORD PTR DS:[EAX+6FBD0EB8] +0x0
	{D2DLL_D2CLIENT, 0x5D875, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x5D876, (DWORD)D2Func_2_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x5D87A, 0x90, FALSE, 0x1},

	//$+5D89D   |.  8B81 C00EBD6F MOV EAX,DWORD PTR DS:[ECX+6FBD0EC0] +0x8
	{D2DLL_D2CLIENT, 0x5D89D, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x5D89E, (DWORD)D2Func_3_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x5D8A2, 0x90, FALSE, 0x1},

	//$+5D8DE   |.  8B80 BC0EBD6F MOV EAX,DWORD PTR DS:[EAX+6FBD0EBC] +0x4
	{D2DLL_D2CLIENT, 0x5D8DE, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x5D8DF, (DWORD)D2Func_4_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x5D8E3, 0x90, FALSE, 0x1},

	//$+5D902   |.  8B81 C40EBD6F MOV EAX,DWORD PTR DS:[ECX+6FBD0EC4] +0xC
	{D2DLL_D2CLIENT, 0x5D902, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x5D903, (DWORD)D2Func_5_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x5D907, 0x90, FALSE, 0x1},

	//$+5DA0B   |.  81C5 B80EBD6F ||ADD EBP,OFFSET 6FBD0EB8 +0x0
	{D2DLL_D2CLIENT, 0x5DA0B, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x5DA0C, (DWORD)D2Func_6_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x5DA10, 0x90, FALSE, 0x1},

	//$+5DDB7   |.  BE D00FBD6F   MOV ESI,OFFSET 6FBD0FD0 +0x118
	{D2DLL_D2CLIENT, 0x5DDB7, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x5DDB8, (DWORD)D2Func_7_111b_113d, TRUE, 0x0},


	//$+5D7C7   |.  83F8 20       CMP EAX,20
	//$+5D7CA   |.  7C 1C         JL SHORT 6FB0D7E8

	// change to

	// NOP
	// NOP
	// NOP
	// JMP SHORT 6FB0D7E8

	{D2DLL_D2CLIENT, 0x5D7C7, (DWORD)PATCH_NOPBLOCK, FALSE, 0x3},
	{D2DLL_D2CLIENT, 0x5D7CA, 0xEB, FALSE, 0x1},
	{D2DLL_D2CLIENT, 0x5D7CB, 0x1C, FALSE, 0x1},

	//$+5D9F7   |.  83FD 20       ||CMP EBP,20
	//$+5D9FA   |.  0F8D 89030000 ||JGE 6FB0DD89

	// change to nops

	{D2DLL_D2CLIENT, 0x5D9F7, (DWORD)PATCH_NOPBLOCK, FALSE, 0x9},
	{D2DLL_INVALID} // this must be the last entry in the array!
};


static const DLLPatchStrc gptD2Client112a[] =
{
	//$+77222   |.  B8 000FBD6F   MOV EAX,OFFSET 6FBD0F00 +0x0
	{D2DLL_D2CLIENT, 0x77222, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x77223, (DWORD)D2Func_1_111b_113d, TRUE, 0x0},

	//$+772A5   |.  8B80 000FBD6F MOV EAX,DWORD PTR DS:[EAX+6FBD0F00] +0x0
	{D2DLL_D2CLIENT, 0x772A5, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x772A6, (DWORD)D2Func_2_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x772AA, 0x90, FALSE, 0x1},

	//$+772CD   |.  8B81 080FBD6F MOV EAX,DWORD PTR DS:[ECX+6FBD0F08] +0x8
	{D2DLL_D2CLIENT, 0x772CD, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x772CE, (DWORD)D2Func_3_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x772D2, 0x90, FALSE, 0x1},

	//$+7730E   |.  8B80 040FBD6F MOV EAX,DWORD PTR DS:[EAX+6FBD0F04] +0x4
	{D2DLL_D2CLIENT, 0x7730E, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x7730F, (DWORD)D2Func_4_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x77313, 0x90, FALSE, 0x1},

	//$+77332   |.  8B81 0C0FBD6F MOV EAX,DWORD PTR DS:[ECX+6FBD0F0C] +0xC
	{D2DLL_D2CLIENT, 0x77332, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x77333, (DWORD)D2Func_5_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x77337, 0x90, FALSE, 0x1},

	//$+7743B   |.  81C5 000FBD6F ||ADD EBP,OFFSET 6FBD0F00 +0x0
	{D2DLL_D2CLIENT, 0x7743B, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x7743C, (DWORD)D2Func_6_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x77440, 0x90, FALSE, 0x1},

	//$+777E7   |.  BE 1810BD6F   MOV ESI,OFFSET 6FBD1018 +0x118
	{D2DLL_D2CLIENT, 0x777E7, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x777E8, (DWORD)D2Func_7_111b_113d, TRUE, 0x0},


	//$+771F7   |.  83F8 20       CMP EAX,20
	//$+771FA   |.  7C 1C         JL SHORT 6FB27218

	// change to

	// NOP
	// NOP
	// NOP
	// JMP SHORT 6FB27218

	{D2DLL_D2CLIENT, 0x771F7, (DWORD)PATCH_NOPBLOCK, FALSE, 0x3},
	{D2DLL_D2CLIENT, 0x771FA, 0xEB, FALSE, 0x1},
	{D2DLL_D2CLIENT, 0x771FB, 0x1C, FALSE, 0x1},

	//$+77427   |.  83FD 20       ||CMP EBP,20
	//$+7742A   |.  0F8D 89030000 ||JGE 6FB277B9

	// change to nops

	{D2DLL_D2CLIENT, 0x77427, (DWORD)PATCH_NOPBLOCK, FALSE, 0x9},
	{D2DLL_INVALID} // this must be the last entry in the array!
};


static const DLLPatchStrc gptD2Client113c[] =
{
	//6FB08E82  $+58E82   |.  B8 F8FEBC6F   MOV EAX,OFFSET 6FBCFEF8 +0x0
	{D2DLL_D2CLIENT, 0x58E82, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x58E83, (DWORD)D2Func_1_111b_113d, TRUE, 0x0},

	//6FB08F05  $+58F05   |.  8B80 F8FEBC6F MOV EAX,DWORD PTR DS:[EAX+6FBCFEF8] +0x0
	{D2DLL_D2CLIENT, 0x58F05, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x58F06, (DWORD)D2Func_2_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x58F0A, 0x90, FALSE, 0x1},

	//6FB08F2D  $+58F2D   |.  8B81 00FFBC6F MOV EAX,DWORD PTR DS:[ECX+6FBCFF00] +0x8
	{D2DLL_D2CLIENT, 0x58F2D, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x58F2E, (DWORD)D2Func_3_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x58F32, 0x90, FALSE, 0x1},

	//6FB08F6E  $+58F6E   |.  8B80 FCFEBC6F MOV EAX,DWORD PTR DS:[EAX+6FBCFEFC] +0x4
	{D2DLL_D2CLIENT, 0x58F6E, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x58F6F, (DWORD)D2Func_4_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x58F73, 0x90, FALSE, 0x1},

	//6FB08F92  $+58F92   |.  8B81 04FFBC6F MOV EAX,DWORD PTR DS:[ECX+6FBCFF04] +0xC
	{D2DLL_D2CLIENT, 0x58F92, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x58F93, (DWORD)D2Func_5_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x58F97, 0x90, FALSE, 0x1},

	//6FB0909B  $+5909B   |.  81C5 F8FEBC6F ||ADD EBP,OFFSET 6FBCFEF8 +0x0
	{D2DLL_D2CLIENT, 0x5909B, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x5909C, (DWORD)D2Func_6_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x590A0, 0x90, FALSE, 0x1},

	//6FB09447  $+59447   |.  BE 1000BD6F   MOV ESI,OFFSET 6FBD0010 +0x118
	{D2DLL_D2CLIENT, 0x59447, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x59448, (DWORD)D2Func_7_111b_113d, TRUE, 0x0},


	//6FB08E57  $+58E57   |.  83F8 20       CMP EAX,20
	//6FB08E5A  $+58E5A   |.  7C 1C         JL SHORT 6FB08E78

	// change to

	// NOP
	// NOP
	// NOP
	// JMP SHORT 6FB08E78

	{D2DLL_D2CLIENT, 0x58E57, (DWORD)PATCH_NOPBLOCK, FALSE, 0x3},
	{D2DLL_D2CLIENT, 0x58E5A, 0xEB, FALSE, 0x1},
	{D2DLL_D2CLIENT, 0x58E5B, 0x1C, FALSE, 0x1},

	//6FB09087  $+59087   |.  83FD 20       ||CMP EBP,20
	//6FB0908A  $+5908A   |.  0F8D 89030000 ||JGE 6FB09419

	// change to nops

	{D2DLL_D2CLIENT, 0x59087, (DWORD)PATCH_NOPBLOCK, FALSE, 0x9},
	{D2DLL_INVALID} // this must be the last entry in the array!
};


static const DLLPatchStrc gptD2Client113d[] =
{
	//$+4E412   |.  B8 F018BD6F   MOV EAX,OFFSET 6FBD18F0 +0x0
	{D2DLL_D2CLIENT, 0x4E412, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x4E413, (DWORD)D2Func_1_111b_113d, TRUE, 0x0},

	//$+4E495   |.  8B80 F018BD6F MOV EAX,DWORD PTR DS:[EAX+6FBD18F0] +0x0
	{D2DLL_D2CLIENT, 0x4E495, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x4E496, (DWORD)D2Func_2_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x4E49A, 0x90, FALSE, 0x1},

	//$+4E4BD   |.  8B81 F818BD6F MOV EAX,DWORD PTR DS:[ECX+6FBD18F8] +0x8
	{D2DLL_D2CLIENT, 0x4E4BD, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x4E4BE, (DWORD)D2Func_3_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x4E4C2, 0x90, FALSE, 0x1},

	//$+4E4FE   |.  8B80 F418BD6F MOV EAX,DWORD PTR DS:[EAX+6FBD18F4] +0x4
	{D2DLL_D2CLIENT, 0x4E4FE, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x4E4FF, (DWORD)D2Func_4_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x4E503, 0x90, FALSE, 0x1},

	//$+4E522   |.  8B81 FC18BD6F MOV EAX,DWORD PTR DS:[ECX+6FBD18FC] +0xC
	{D2DLL_D2CLIENT, 0x4E522, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x4E523, (DWORD)D2Func_5_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x4E527, 0x90, FALSE, 0x1},

	//$+4E62B   |.  81C5 F018BD6F ||ADD EBP,OFFSET 6FBD18F0 +0x0
	{D2DLL_D2CLIENT, 0x4E62B, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x4E62C, (DWORD)D2Func_6_111b_113d, TRUE, 0x0},
	{D2DLL_D2CLIENT, 0x4E630, 0x90, FALSE, 0x1},

	//$+4E9D7   |.  BE 081ABD6F   MOV ESI,OFFSET 6FBD1A08 +0x118
	{D2DLL_D2CLIENT, 0x4E9D7, (DWORD)PATCH_CALL, FALSE, 0x0},
	{D2DLL_D2CLIENT, 0x4E9D8, (DWORD)D2Func_7_111b_113d, TRUE, 0x0},


	//$+4E3E7   |.  83F8 20       CMP EAX,20
	//$+4E3EA   |.  7C 1C         JL SHORT 6FAFE408

	// change to

	// NOP
	// NOP
	// NOP
	// JMP SHORT 6FAFE408

	{D2DLL_D2CLIENT, 0x4E3E7, (DWORD)PATCH_NOPBLOCK, FALSE, 0x3},
	{D2DLL_D2CLIENT, 0x4E3EA, 0xEB, FALSE, 0x1},
	{D2DLL_D2CLIENT, 0x4E3EB, 0x1C, FALSE, 0x1},

	//$+4E617   |.  83FD 20       ||CMP EBP,20
	//$+4E61A   |.  0F8D 89030000 ||JGE 6FAFE9A9

	// change to nops

	{D2DLL_D2CLIENT, 0x4E617, (DWORD)PATCH_NOPBLOCK, FALSE, 0x9},
	{D2DLL_INVALID} // this must be the last entry in the array!
};

// end of file --------------------------------------------------------------
#endif