#include "stdafx.h"
#include "Pet.h"
#include "Import.h"
#include "User.h"
#include "PetProtocol.h"
#include "TMemory.h"
#include "Protect.h"
#include "Interface.h"
#include "Util.h"
#include "CustomPet.h"
#include "CustomCloak.h"

CustomPet gCustomPet;

CustomPet::CustomPet() //OK
{
	this->PetTickCount = 0;
}

CustomPet::~CustomPet()
{

}

char CustomPet::PetHPBar(int a1, int a2)
{
	lpViewObj Object = &*(ObjectPreview*)oUserPreviewStruct;

	char result;
	char PetName[255];
	int PetHP;

	if ((Object->PetSlot < 7827 || Object->PetSlot > 7831)
		&& Object->PetSlot != 7891
		&& Object->PetSlot != 7892
		&& Object->PetSlot != 7894
		&& Object->PetSlot != 7907
		&& Object->PetSlot != 7933
		&& Object->PetSlot != 7950
		&& Object->PetSlot != 7864
		&& (Object->PetSlot < ITEM2(13, 200) || Object->PetSlot > ITEM2(13, 512)))
	{
		result = 0;
	}
	else
	{
		memset(&PetHP, 0, 255);
		PetName[0] = 0;
		switch (Object->PetSlot)
		{
		case 7827:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 353));
			break;
		case 7828:
			wsprintf(PetName, (char *)oUserTextObject + 84 * (*(WORD *)(oUserPreviewStruct + 556) - 1171));
			break;
		case 7829:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 355));
			break;
		case 7830:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 354));
			break;
		case 7831:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 1187));
			break;
		case 7864:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 1916));
			break;
		case 7891:
			wsprintf(PetName, (char *)(oUserTextObject + 564480));
			break;
		case 7892:
			wsprintf(PetName, (char *)(oUserTextObject + 564564));
			break;
		case 7894:
			wsprintf(PetName, (char *)(oUserTextObject + 564732));
			break;
		case 7907:
			wsprintf(PetName, (char *)(oUserTextObject + 565824));
			break;
		case 7933:
			wsprintf(PetName, (char *)(oUserTextObject + 568008));
			break;
		case 7950:
			wsprintf(PetName, (char *)(oUserTextObject + 569436));
			break;
		default:
			wsprintf(PetName, (char *)oUserTextObject + 84 * (*(WORD *)(oUserPreviewStruct + 556) - 1171));
			break;
		}

		PetHP = *(BYTE*)(oUserObjectStruct_ + 5550);
		lpCharObj test		= &*(ObjectCharacter*)oUserObjectStruct_;
		
		sub_7DFA60(2, 26, (int)&PetName, PetHP, 255, 0);
		
		result = 1;
	}

	return result;
}

bool IsCharacterMove(int a1)
{

	if ((*(WORD *)(*(DWORD *)(a1 + 472) + 18) >= 15
		&& *(WORD *)(*(DWORD *)(a1 + 472) + 18) <= 37)
		|| *(WORD *)(*(DWORD *)(a1 + 472) + 18) == 74
		|| *(WORD *)(*(DWORD *)(a1 + 472) + 18) == 75
		|| *(WORD *)(*(DWORD *)(a1 + 472) + 18) == 259
		|| *(WORD *)(*(DWORD *)(a1 + 472) + 18) == 260)
	{
		return true;
	}
	return false;
}

void CustomPet::PetFollowCharacter(int a1, float MaxPos)
{
	float v22;
	vec3_t MUFLOAT;
	vec3_t PetPos;
	vec3_t OwnerPos;
	vec3_t CurrentPos;
	int LootPosition = 1000;

	OwnerPos[0] = *(float *)(*(DWORD *)(a1 + 472) + 252);
	OwnerPos[1] = *(float *)(*(DWORD *)(a1 + 472) + 256);
	OwnerPos[2] = *(float *)(*(DWORD *)(a1 + 472) + 260);

	PetPos[0] = OwnerPos[0] - *(float *)(a1 + 252);
	PetPos[1] = OwnerPos[1] - *(float *)(a1 + 256);
	PetPos[2] = OwnerPos[2] - *(float *)(a1 + 260);

	CurrentPos[0] = *(float *)(a1 + 252);
	CurrentPos[1] = *(float *)(a1 + 256);
	CurrentPos[2] = *(float *)(a1 + 260);

	float PetMapPos = PetPos[0] * PetPos[0] + PetPos[1] * PetPos[1];

	float diff1 = ((OwnerPos[0] > CurrentPos[0]) ? OwnerPos[0] - CurrentPos[0] : CurrentPos[0] - OwnerPos[0]);
	float diff2 = ((OwnerPos[1] > CurrentPos[1]) ? OwnerPos[1] - CurrentPos[1] : CurrentPos[1] - OwnerPos[1]);

	float angle = atan(diff2 / diff1) * 180 / PI;
	float angle2 = atan2(diff1, diff2) * 180 / PI; //

	if (PetMapPos >= MaxPos * MaxPos)
	{
		float speed;
		if (PetMapPos >= (MaxPos * 2) * (MaxPos * 2))
		{
			speed = 14.0f;
			speed += 1.0f;
			*(float *)(a1 + 120) = 0.89000002f;
		}
		else if (PetMapPos >= (MaxPos + (MaxPos / 2)) * (MaxPos + (MaxPos / 2)))
		{
			speed = 13.0f;
			*(float *)(a1 + 120) = 0.69000002f;
		}
		else
		{
			speed = 10.0f;
			*(float *)(a1 + 120) = 0.40000001f;
		}

		double MoveX = speed *(cos(angle * PI / 180));
		double MoveY = speed *(sin(angle * PI / 180));

		if (CurrentPos[0] < OwnerPos[0] && CurrentPos[1] < OwnerPos[1])
		{
			*(float *)(a1 + 252) += (float)MoveX;
			*(float *)(a1 + 256) += (float)MoveY;
			*(float *)(a1 + 272) = 180;
			*(float *)(a1 + 272) -= angle2;
		}
		else if (CurrentPos[0] < OwnerPos[0] && CurrentPos[1] > OwnerPos[1])
		{
			*(float *)(a1 + 252) += (float)MoveX;
			*(float *)(a1 + 256) -= (float)MoveY;
			*(float *)(a1 + 272) = angle2;
		}
		else if (CurrentPos[0] > OwnerPos[0] && CurrentPos[1] > OwnerPos[1])
		{
			*(float *)(a1 + 252) -= (float)MoveX;
			*(float *)(a1 + 256) -= (float)MoveY;
			*(float *)(a1 + 272) = 360;
			*(float *)(a1 + 272) -= angle2;
		}
		else if (CurrentPos[0] > OwnerPos[0] && CurrentPos[1] < OwnerPos[1])
		{
			*(float *)(a1 + 252) -= (float)MoveX;
			*(float *)(a1 + 256) += (float)MoveY;
			*(float *)(a1 + 272) = 180;
			*(float *)(a1 + 272) += angle2;
		}
		*(WORD*)(a1 + 18) = 2;
	}
	else if (PetMapPos < 70 * 70)
	{
		if ((*(WORD *)(*(DWORD *)(a1 + 472) + 18) < 15 || *(WORD *)(*(DWORD *)(a1 + 472) + 18) > 37))
		{
			*(WORD*)(a1 + 18) = 2;
			sub_959CE0(a1 + 264, a1 + 372);
			sub_95A1E0(a1 + 168, a1 + 372, MUFLOAT);
			*(float *)(a1 + 252) = *(float *)(a1 + 252) + MUFLOAT[0];
			*(float *)(a1 + 256) = *(float *)(a1 + 256) + MUFLOAT[1];
		}
	}
	else
	{
		if( pViewAttackTargetID != -1 )
		{
			if (GetTickCount() <= gCustomPet.PetTickCount + 10000)
			{
				*(WORD*)(a1 + 18) = 1;
			}
			else
			{
				*(WORD*)(a1 + 18) = 0;
				gCustomPet.PetTickCount = GetTickCount();
			}
		}
		else if (GetTickCount() <= gCustomPet.PetTickCount + 800)
		{
			*(WORD*)(a1 + 18) = 1;
		}
		else if (GetTickCount() <= gCustomPet.PetTickCount + 12000)
		{
			*(WORD*)(a1 + 18) = 0;
		}
		else
		{
			gCustomPet.PetTickCount = GetTickCount();
		}
	}

	if (PetMapPos >= LootPosition * LootPosition)
	{
		if (*(float *)(a1 + 252) < *(float *)(*(DWORD *)(a1 + 472) + 252))
		{
			*(float *)(a1 + 252) = *(float *)(a1 + 252) + PetPos[0] + rand() % 360;
		}
		if (*(float *)(a1 + 252) > *(float *)(*(DWORD *)(a1 + 472) + 252))
		{
			*(float *)(a1 + 252) = *(float *)(a1 + 252) + PetPos[0] - rand() % 360;
		}
		if (*(float *)(a1 + 256) < *(float *)(*(DWORD *)(a1 + 472) + 256))
		{
			*(float *)(a1 + 256) = *(float *)(a1 + 256) + PetPos[1] + rand() % 360;
		}
		if (*(float *)(a1 + 256) > *(float *)(*(DWORD *)(a1 + 472) + 256))
		{
			*(float *)(a1 + 256) = *(float *)(a1 + 256) + PetPos[1] - rand() % 360;
		}
	}

	*(float *)(a1 + 260) = *(float *)(*(DWORD *)(a1 + 472) + 260);

	if (!(rand() % 100))
	{
		if (PetMapPos < MaxPos * MaxPos)
		{
			v22 = -(float)(rand() % 64 + 16) * 0.1000000014901161f;
			*(float *)(a1 + 272) = (float)(rand() % 360);
		}
		else
		{
			v22 = -(float)(rand() % 64 + 128) * 0.1000000014901161f;
		}
		*(float *)(a1 + 168) = 0.0f;
		*(float *)(a1 + 172) = v22;
		*(float *)(a1 + 176) = (float)(rand() % 64 - 32) * 0.1000000014901161f;
	}

	if (*(float *)(a1 + 260) < *(float *)(*(DWORD *)(a1 + 472) + 260) + 100.0f)
		*(float *)(a1 + 176) = *(float *)(a1 + 176) + 1.5f;
	if (*(float *)(a1 + 260) > *(float *)(*(DWORD *)(a1 + 472) + 260) + 200.0f)
		*(float *)(a1 + 176) = *(float *)(a1 + 176) - 1.5f;
}

#if(HAISLOTRING)

bool CustomPet::PetsMovement(int a1, char a2)
{
	int v86; // [sp+19Ch] [bp-Ch]@76
	float v87; // [sp+1A0h] [bp-8h]@76
	float v88; // [sp+1A4h] [bp-4h]@76

	if (*(BYTE*)(a1 + 4))
	{
		lpViewObj lpObj = &*(ObjectPreview*)*(DWORD*)0x07BC4F04;

		if (*(DWORD*)0xE609E8 == 5
			&& (*(DWORD*)0xE61E18 < 65 || *(DWORD*)0xE61E18 > 68)
			&& (!*(BYTE*)(*(DWORD*)(a1 + 472) + 4) || *(BYTE*)(*(DWORD*)(a1 + 472) + 24) != 1))
		{
			*(BYTE*)(a1 + 4) = 0;
			sub_501790(a1, a2);
			return false;
		}

		DWORD SkinID = *(DWORD*)(a1 + 48);
		DWORD Model = sub_969C50(sub_4CDA10(), SLODWORD(SkinID));

		if (Model)
		{
			{
				if ((SkinID >= ITEM2(13, 246) && SkinID <= ITEM2(13, 350)) && g_CustomPet.GetInfoPetType(SkinID - 1171) == 8)
				{
					gCustomPet.PetFollowCharacter(a1, 150);//150

					switch (SkinID)
					{
					case ITEM2(13, 226): //King
					case ITEM2(13, 281): //Prince
					case ITEM2(13, 388): //Prince =)) lazy
						*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 40.0f;
						break;
					case ITEM2(13, 214): //Hawk
					case ITEM2(13, 215): //Hawk Evo
					case ITEM2(13, 174): //CherryBlossom
					case ITEM2(13, 175): //CherryBlossom Evo
					case ITEM2(13, 178): //Chrysanthemum
					case ITEM2(13, 179): //Chrysanthemum Evo
					case ITEM2(13, 200): //Ghost
						*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 30.0f;
						break;
					case ITEM2(13, 201): //Ghost Evo
						*(DWORD*)(a1 + 68) = 1;
						*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 30.0f;
						break;
					}
				}
				else if ((SkinID >= ITEM2(13, 200) && SkinID <= ITEM2(13, 245)) && g_CustomPet.GetInfoPetType(SkinID - 1171) == 8)//muun
				{
					lpViewObj MuunMount = &*(ObjectPreview*)(oUserPreviewStruct);
					int dis = 200;
					if (MuunMount)
					{
						if (MuunMount->InSafeZone)
						{
							dis = 400;
						}
					}
					gCustomPet.PetFollowCharacter(a1, dis);

					switch (SkinID)
					{
					case ITEM2(13, 226): //King
					case ITEM2(13, 281): //Prince
					case ITEM2(13, 388): //Prince =)) lazy
						*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 40.0f;
						break;
					case ITEM2(13, 214): //Hawk
					case ITEM2(13, 215): //Hawk Evo
					case ITEM2(13, 174): //CherryBlossom
					case ITEM2(13, 175): //CherryBlossom Evo
					case ITEM2(13, 178): //Chrysanthemum
					case ITEM2(13, 179): //Chrysanthemum Evo
					case ITEM2(13, 200): //Ghost
						*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 30.0f;
						break;
					case ITEM2(13, 201): //Ghost Evo
						*(DWORD*)(a1 + 68) = 1;
						*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 30.0f;
						break;
					}
				}
			}
			//---
		}
	}

	return ((bool(*)(int, char)) 0x00501790)(a1, a2);
}

#else
void CustomPet::PetsMovement(int a1, char a2)
{
	int v86; // [sp+19Ch] [bp-Ch]@76
	float v87; // [sp+1A0h] [bp-8h]@76
	float v88; // [sp+1A4h] [bp-4h]@76

	if (*(BYTE*)(a1 + 4))
	{
		lpViewObj lpObj = &*(ObjectPreview*)*(DWORD*)0x07BC4F04;

		if (*(DWORD*)0xE609E8 == 5
			&& (*(DWORD*)0xE61E18 < 65 || *(DWORD*)0xE61E18 > 68)
			&& (!*(BYTE*)(*(DWORD*)(a1 + 472) + 4) || *(BYTE*)(*(DWORD*)(a1 + 472) + 24) != 1))
		{
			*(BYTE*)(a1 + 4) = 0;
			sub_501790(a1, a2);
			return;
		}

		DWORD SkinID = *(DWORD*)(a1 + 48);
		DWORD Model = sub_969C50(sub_4CDA10(), SLODWORD(SkinID));

		if (Model)
		{
			if ((SkinID >= ITEM2(13, 200) && SkinID <= ITEM2(13, 512)) && g_CustomPet.GetInfoPetType(SkinID - 1171) == 8)
			{
				gCustomPet.PetFollowCharacter(a1, 150);

				switch (SkinID)
				{
				case ITEM2(13, 226): //King
				case ITEM2(13, 281): //Prince
				case ITEM2(13, 388): //Prince =)) lazy
					*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 40.0f;
					break;
				case ITEM2(13, 214): //Hawk
				case ITEM2(13, 215): //Hawk Evo
				case ITEM2(13, 174): //CherryBlossom
				case ITEM2(13, 175): //CherryBlossom Evo
				case ITEM2(13, 178): //Chrysanthemum
				case ITEM2(13, 179): //Chrysanthemum Evo
				case ITEM2(13, 200): //Ghost
					*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 30.0f;
					break;
				case ITEM2(13, 201): //Ghost Evo
					*(DWORD*)(a1 + 68) = 1;
					*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 30.0f;
					break;
				}
			}
		}
	}

	((void(*)(int, char)) 0x501790)(a1, a2);
}
#endif

void CustomPet::PreviewCharSet(int ObjectIndex, BYTE * CharSet, lpViewObj Object, int Mode)
{
	pPreviewCharSet(ObjectIndex, CharSet, Object, Mode);

	lpViewObj lpObj;

	if (Object == 0)
	{
		lpObj = &*(lpViewObj)pGetPreviewStruct(pPreviewThis(), ObjectIndex);
	}
	else
	{
		lpObj = Object;
	}

	PMSG_NEW_CHARACTER_CHARSET_RECV* SelectCharSet = GetNewCharSetSelectCharacter(lpObj->Name);

	if (pPlayerState == 4)
	{
		if (SelectCharSet > 0)
		{
			BYTE sNewCharSet0 = SelectCharSet->PetCharSet[0] >> 1;
			BYTE sNewCharSet1 = SelectCharSet->PetCharSet[1] >> 1;
			BYTE sNewCharSet2 = SelectCharSet->PetCharSet[2] >> 1;
			BYTE sNewCharSet3 = SelectCharSet->PetCharSet[3] >> 1;

			if (sNewCharSet0 > 0 && sNewCharSet0 < 112)
			{
				if (Mode)
				{
					*(BYTE *)(Mode + 4) = 0;
				}
				else
				{
					sub_5012D0((int)&lpObj->m_Model);
					sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
				}

				lpObj->PetSlot = ITEM2(13, 147) + (sNewCharSet0 - 1);

				if (Mode)
					sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
				else
					sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			}

			if (sNewCharSet1 > 0 && sNewCharSet1 < 94)
			{
				if (Mode)
				{
					*(BYTE *)(Mode + 4) = 0;
				}
				else
				{
					sub_5012D0((int)&lpObj->m_Model);
					sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
				}

				lpObj->PetSlot = ITEM2(13, 258) + (sNewCharSet1 - 1);

				if (Mode)
					sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
				else
					sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			}

			if (sNewCharSet2 > 0 && sNewCharSet2 < 100)
			{
				if (Mode)
				{
					*(BYTE *)(Mode + 4) = 0;
				}
				else
				{
					sub_5012D0((int)&lpObj->m_Model);
					sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
				}

				lpObj->PetSlot = ITEM2(13, 351) + (sNewCharSet2 - 1);

				if (Mode)
					sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
				else
					sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			}

			if (sNewCharSet3 > 0 && sNewCharSet3 < 100)
			{
				if (Mode)
				{
					*(BYTE *)(Mode + 4) = 0;
				}
				else
				{
					sub_5012D0((int)&lpObj->m_Model);
					sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
				}

				lpObj->PetSlot = ITEM2(13, 451) + (sNewCharSet3 - 1);

				if (Mode)
					sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
				else
					sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			}
		}
	}

	NEW_PET_STRUCT* lpCharSet = GetNewPetCharSet(lpObj->aIndex);

	if (lpCharSet > 0)
	{
		BYTE NewCharSet0 = lpCharSet->PetCharSet[0] >> 1;
		BYTE NewCharSet1 = lpCharSet->PetCharSet[1] >> 1;
		BYTE NewCharSet2 = lpCharSet->PetCharSet[2] >> 1;
		BYTE NewCharSet3 = lpCharSet->PetCharSet[3] >> 1;

		if (NewCharSet0 > 0 && NewCharSet0 < 112)
		{
			if (Mode)
			{
				*(BYTE *)(Mode + 4) = 0;
			}
			else
			{
				sub_5012D0((int)&lpObj->m_Model);
				sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
			}

			lpObj->PetSlot = ITEM2(13, 147) + (NewCharSet0 - 1);

			if (Mode)
				sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
		}

		if (NewCharSet1 > 0 && NewCharSet1 < 94)
		{
			if (Mode)
			{
				*(BYTE *)(Mode + 4) = 0;
			}
			else
			{
				sub_5012D0((int)&lpObj->m_Model);
				sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
			}

			lpObj->PetSlot = ITEM2(13, 258) + (NewCharSet1 - 1);

			if (Mode)
				sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
		}

		if (NewCharSet2 > 0 && NewCharSet2 < 100)
		{
			if (Mode)
			{
				*(BYTE *)(Mode + 4) = 0;
			}
			else
			{
				sub_5012D0((int)&lpObj->m_Model);
				sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
			}

			lpObj->PetSlot = ITEM2(13, 351) + (NewCharSet2 - 1);

			if (Mode)
				sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
		}

		if (NewCharSet3 > 0 && NewCharSet3 < 100)
		{
			if (Mode)
			{
				*(BYTE *)(Mode + 4) = 0;
			}
			else
			{
				sub_5012D0((int)&lpObj->m_Model);
				sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
			}

			lpObj->PetSlot = ITEM2(13, 451) + (NewCharSet3 - 1);

			if (Mode)
				sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
		}

	}

	BYTE CustomPets = CharSet[15] >> 1;

	if (CharSet[11] & 1) // == 1 
	{
		lpObj->PetSlot = 7831;
		if (Mode)
			sub_5013B0(226, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
		else
			sub_501700(226, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
	}
}

void CustomPet::RefreshViewPortItem(int a1)
{
	signed int v1; // ST14_4@1
	int result; // eax@1
	int v6; // [sp+Ch] [bp-14h]@2
	int v7; // [sp+10h] [bp-10h]@1
	int v8; // [sp+14h] [bp-Ch]@2
	BYTE v9; // [sp+1Dh] [bp-3h]@2
	BYTE v10; // [sp+1Eh] [bp-2h]@2
	BYTE v11; // [sp+1Fh] [bp-1h]@2

	v1 = sub_57D9A0(*(BYTE *)(a1 + 4) + (*(BYTE *)(a1 + 3) << 8));
	result = sub_96A4C0(sub_402BC0(), v1);
	v7 = result;

	if ( result )
	{
		v6 = result + 776;
		v8 = sub_58AA80(a1 + 5);
		v11 = *(BYTE *)(a1 + 6) & 0xF;
		v10 = *(BYTE *)(a1 + 8) & 0x3F;
		v9 = *(BYTE *)(a1 + 9);
		switch ((signed int)*(BYTE *)(a1 + 6) >> 4)
		{
		case 7:
			if (v8 == 0x1FFF)
			{
				if (*(WORD*)(v7 + 520) == ITEM2(12,40)
					|| *(WORD*)(v7 + 520) == ITEM2(12,49)
					|| *(WORD*)(v7 + 520) == ITEM2(12,50)
					|| gCloak.isCloak((*(WORD*)(v7 + 520) - 1171)))
				{
					sub_558630(v7, v6, 0);
				}
				*(WORD *)(v7 + 520) = -1;
			}
			else
			{
				*(WORD *)(v7 + 520) = v8 + 1171;
				*(BYTE *)(v7 + 522) = 0;
				if (*(WORD*)(v7 + 520) == ITEM2(12, 40)
					|| *(WORD*)(v7 + 520) == ITEM2(12, 49)
					|| *(WORD*)(v7 + 520) == ITEM2(12, 50)
					|| gCloak.isCloak((*(WORD*)(v7 + 520) - 1171)))
				{
					sub_558630(v7, v6, 0);
				}
			}
			break;
		case 8:
			if (v8 == 0x1FFF)
			{
				*(WORD *)(v7 + 556) = -1;
				sub_5012D0(v6);
				sub_9253D0(sub_4DB230(), v7, -1);
			}
			else
			{
				*(WORD *)(v7 + 556) = v8 + 1171;
				*(BYTE *)(v7 + 558) = 0;
				if (v8 >= ITEM(13, 147) && v8 <= ITEM(13, 512))
				{
					sub_501700(v8 + 1171, v6 + 252, v6, 0, 0);
				}
			}
			break;
		default:
			break;
		}
	}
	((void(*)(int))0x6411A0)(a1);
}

char PetPreviewScale(int a4, char a5)
{
	if(*(BYTE*)(a4 + 4))
	{
		char v8 = 0;

		if(a5)
		{
			v8 = 1;
		}
		else
		{
			float v5 = *(float*)(a4 + 256) * 0.009999999776482582;
			float v6 = *(float*)(a4 + 252) * 0.009999999776482582;
			v8 = sub_5DBA10(v6, v5, -20.0);
		}

		*(BYTE*)(a4 + 12) = v8;

		if(*(BYTE*)(a4 + 12))
		{
			DWORD dwItemNumber = *(DWORD*)(a4 + 48);

			if(*(DWORD *)(*(DWORD*)(a4 + 472) + 48) != 1163 && *(DWORD*)(a4 + 48) != 7827)
			{
				return 1;
			}

			if(a5)
			{
				*(float*)(a4 + 96) = *(float*)(a4 + 96);
			}
			else if(pPlayerState == 4)
			{
				if(g_CustomPet.CheckCustomPetByItem(dwItemNumber - 1171))
				{		
						*(float*)(a4 + 96) = g_CustomPet.GetScaleView(dwItemNumber - 1171) + 0.3;
				}
				else
				{
						*(float*)(a4 + 96) = 1.3;
				}
			}
			else if(dwItemNumber != 384 && dwItemNumber != 386 && dwItemNumber != 385 && dwItemNumber != 387)
			{
				*(float*)(a4 + 96) = 1.0;
			}

			if (pPlayerState > 4)
			{
				if(g_CustomPet.CheckCustomPetByItem(dwItemNumber - 1171))
				{
					*(float*)(a4 + 96) = g_CustomPet.GetScaleView(dwItemNumber - 1171);
				}
				else
				{
					*(float*)(a4 + 96) = 1.0;
				}
			}
			
			int v9 = 0;

			if(sub_4C8640((LPVOID)(*(DWORD*)(a4 + 472) + 484), 18))
			{
				v9 = 10;
			}
			
			pObjectMaxBug(a4, 0, 0, v9);
	
			float v10 = (double)((signed int)sub_9CFB8D() % 30 + 70) * 0.009999999776482582;

			if(dwItemNumber == 7827)
			{
				float v11[3];

				v11[0] = v10 * 0.5;
				v11[1] = v10 * 0.800000011920929;
				v11[2] = v10 * 0.6000000238418579;

				pPlayStaticEffect(32002, (DWORD*)(a4 + 252), 1.0, v11, a4, 0.0, 0);
			}
		}
	}

	return 1;
}

void CustomPet::Load()
{
	//-- Follow Pet Character
	//
	//-- PetMuun
	SetOp((LPVOID)0x0048E17D, CustomPet::PetsMovement, ASM::CALL);
	SetOp((LPVOID)0x00503756, CustomPet::PetsMovement, ASM::CALL);

	SetOp((LPVOID)0x007DF8BB, CustomPet::PetHPBar, ASM::CALL);
	
	SetOp((LPVOID)0x48FB8C, CustomPet::PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x63D2D8, CustomPet::PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x641189, CustomPet::PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x641F42, CustomPet::PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x642598, CustomPet::PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x65EA2D, CustomPet::PreviewCharSet, ASM::CALL);

	SetOp((LPVOID)0x664267, CustomPet::RefreshViewPortItem, ASM::CALL);

	SetCompleteHook(0xE8, 0x0048E504, &PetPreviewScale);
	SetCompleteHook(0xE8, 0x00503986, &PetPreviewScale);
}