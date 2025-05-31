#include "stdafx.h"
#include "CustomDisableSystem.h"
#include "Util.h"
#include "TMemory.h"
#include "Defines.h"

DWORD	SetInvisibleEffect_PointerYY;
DWORD	SetInvisibleEffect_BuffYY;
DWORD	SetInvisibleEffect_PointerY;
DWORD	SetInvisibleEffect_BuffY;
DWORD	ObjectPointer;
DWORD	SetInvisibleEffect_PointerX;
DWORD	SetInvisibleEffect_BuffX;

KG_DisableSystem gCDisableSystem;

KG_DisableSystem::KG_DisableSystem()
{
}

KG_DisableSystem::~KG_DisableSystem()
{
}

/*Effect15*/
void KG_DisableSystem::KG_ActivateEffect15_1(){
	MemorySet(0x0057655B,0x90,0x5);
}

void KG_DisableSystem::KG_ActivateEffect15_2(){
	SetOp((LPVOID)0x0057655B,(LPVOID)0x006097B0,ASM::CALL);
}

/*InvisibleObjects*/
void KG_DisableSystem::KG_ActivateInvisibleObjects_1(){
	SetByte((PVOID)(0x005DE2B2), 1);
}

void KG_DisableSystem::KG_ActivateInvisibleObjects_2(){
	SetByte((PVOID)(0x005DE2B2), 0);
}

/*InvisibleArmors*/
__declspec(naked) void ItemInvisible1(){
	static DWORD m_aaaaab = 0x0060B37A;
		_asm{
		    mov SetInvisibleEffect_BuffYY, esi
		    mov ecx, dword ptr ss : [ebp + 8]
		    mov esi, dword ptr ds : [ecx + 0x30]
		    mov SetInvisibleEffect_PointerYY, esi
		    mov esi, SetInvisibleEffect_BuffYY
		}
		if(SetInvisibleEffect_PointerYY != 0x1EA5
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 15) 
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 30)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 31)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 136)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 137)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 138)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 139)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 140)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 141)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 142)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 143)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 13)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 14)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 16)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 31)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 42)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 13)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 41)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 43)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 44)){
		_asm{
			jmp [m_aaaaab]
		}
	}
}

__declspec(naked) void ItemInvisible2(){
	static DWORD m_aaaaaa = 0x0060B41D;
	_asm{
		mov SetInvisibleEffect_BuffY, esi
		mov ecx, dword ptr ss : [ebp + 8]
		mov esi, dword ptr ds : [ecx + 0x30]
		jmp [m_aaaaaa]
	}
}

Naked(InvisibleEffectX){
	_asm{
		mov SetInvisibleEffect_BuffX, esi
		mov ecx, dword ptr ss : [ebp + 8]
		mov esi, dword ptr ds : [ecx + 0x30]
		mov SetInvisibleEffect_PointerX, esi
		mov esi, SetInvisibleEffect_BuffX
	}
	if (SetInvisibleEffect_PointerX == 0x1EA5 || SetInvisibleEffect_PointerX == ITEM2(13, 18)){
	    _asm{
			mov SetInvisibleEffect_BuffX, 0x0060B37A
			jmp SetInvisibleEffect_BuffX
		}
	}else{
		_asm{
			mov SetInvisibleEffect_BuffX, 0x0060B41D
			jmp SetInvisibleEffect_BuffX
		}
	}
}

void KG_DisableSystem::KG_ActivateInvisibleArmors_1(){
	SetCompleteHook(0xE9, 0x0060B36A, &ItemInvisible1);
}

void KG_DisableSystem::KG_ActivateInvisibleArmors_2(){
	SetCompleteHook(0xE9, 0x0060B36A, &ItemInvisible2);
}

void KG_DisableSystem::KG_ActivateInvisibleArmors_X(){
	SetRange((LPVOID)0x0060B36A, 10, ASM::NOP); //12
	SetCompleteHook(0xE9, 0x0060B36A, &InvisibleEffectX);
}

/*InvisibleWeapons*/
void KG_DisableSystem::KG_ActivateInvisibleWeapons_1(){
	MemorySet(0x576DDB,0x90,0x5);
	MemorySet(0x5883F4,0x90,0x5);
}

void KG_DisableSystem::KG_ActivateInvisibleWeapons_2(){
	SetOp((LPVOID)0x00576DDB,(LPVOID)0x005655C0,ASM::CALL);
	SetOp((LPVOID)0x005883F4,(LPVOID)0x005655C0,ASM::CALL);
}

/*InvisibleWings*/
void KG_DisableSystem::KG_ActivateInvisibleWings_1(){
	MemorySet(0x588661,0x90,0x5);
}

void KG_DisableSystem::KG_ActivateInvisibleWings_2(){
	SetOp((LPVOID)0x00588661,(LPVOID)0x005655C0,ASM::CALL);
}

/*InvisiblePlayer*/
__declspec(naked) void DelectlpViewPlayerOn(){
	static DWORD Buff_lpViewPlayer = 0x0057D27F;
	_asm{
		CMP DWORD PTR SS:[EBP-0x4],0
		JMP [Buff_lpViewPlayer]
	}
}

__declspec(naked) void DelectlpViewPlayerOff(){
	static DWORD Buff_lpViewPlayer = 0x0057D27F;
	_asm{
		CMP DWORD PTR SS:[EBP-0x4],400
		JMP [Buff_lpViewPlayer]
	}
}

void KG_DisableSystem::KG_ActivateInvisiblePlayer_1(){
	SetCompleteHook(0xE9, 0x0057D278, &DelectlpViewPlayerOn);
}

void KG_DisableSystem::KG_ActivateInvisiblePlayer_2(){
	SetCompleteHook(0xE9, 0x0057D278, &DelectlpViewPlayerOff);
}

/*EffectStatic*/
__declspec(naked) void DelectEffectStaticOn(){
	static DWORD Buff_EffectStatic = 0x0077132F;
	_asm{
		CMP DWORD PTR SS:[EBP-0x4],0
		JMP [Buff_EffectStatic]
	}
}

__declspec(naked) void DelectEffectStaticOff(){
	static DWORD Buff_EffectStatic = 0x0077132F;
	_asm{
		CMP DWORD PTR SS:[EBP-0x4],0x3E8
		JMP [Buff_EffectStatic]
	}
}

void KG_DisableSystem::KG_ActivateStaticEffect_1(){
	SetCompleteHook(0xE9, 0x00771328, &DelectEffectStaticOn);
}

void KG_DisableSystem::KG_ActivateStaticEffect_2(){
	SetCompleteHook(0xE9, 0x00771328, &DelectEffectStaticOff);
}

/*EffectDynamic*/
__declspec(naked) void DelectEffectDynamicOn(){
	static DWORD Buff_EffectDynamic = 0x0074CD57;
	_asm{
		CMP DWORD PTR SS:[EBP-0x4],0
		JMP [Buff_EffectDynamic]
	}
}

__declspec(naked) void DelectEffectDynamicOff(){
	static DWORD Buff_EffectDynamic = 0x0074CD57;
	_asm{
		CMP DWORD PTR SS:[EBP-0x4],0x0BB8
		JMP [Buff_EffectDynamic]
	}
}

void KG_DisableSystem::KG_ActivateDynamicEffect_1(){
	SetCompleteHook(0xE9, 0x0074CD50, &DelectEffectDynamicOn);
}

void KG_DisableSystem::KG_ActivateDynamicEffect_2(){
	SetCompleteHook(0xE9, 0x0074CD50, &DelectEffectDynamicOff);
}

/*Shades*/
void KG_DisableSystem::KG_ActiveShades_1(){
	SetByte(0x0054A270, 0xC3);
}

void KG_DisableSystem::KG_ActiveShades_2(){
	SetByte(0x0054A270, 0x55);
}

/*AutoCtrl*/
void KG_DisableSystem::KG_AutoCtrl_1(){
	SetByte(0x0059AF53+2,0);
	SetByte(0x0059B248+2,0);
}

void KG_DisableSystem::KG_AutoCtrl_2(){
	SetByte(0x0059AF53+2,1);
	SetByte(0x0059B248+2,1);
}