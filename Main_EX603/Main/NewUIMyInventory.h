#pragma once
#include "CharacterMachine.h"

#if(HAISLOTRING)

#define EQUIPMENT_WEAPON_RIGHT		0
#define EQUIPMENT_WEAPON_LEFT		1
#define EQUIPMENT_HELM				2
#define EQUIPMENT_ARMOR				3
#define EQUIPMENT_PANTS				4
#define EQUIPMENT_GLOVES			5
#define EQUIPMENT_BOOTS				6
#define EQUIPMENT_WING				7
#define EQUIPMENT_HELPER			8
#define EQUIPMENT_AMULET			9
#define EQUIPMENT_RING_RIGHT		10
#define EQUIPMENT_RING_LEFT			11
//--
#define EQUIPMENT_PENTAGRAM			12
#define EQUIPMENT_ERRING_RIGHT		13
#define EQUIPMENT_ERRING_LEFT		14
#define MAX_EQUIPMENT_INDEX			12

typedef struct tagEQUIPMENT_ITEM
{
	int x, y;
	int width, height;
	DWORD dwBgImage;
} EQUIPMENT_ITEM;

#define RenderRepairInfo					((void(__cdecl*)(int sz, int sy, int ip, bool Sell)) 0x005C3D70)
#define RenderItemInfo_						((void(__thiscall*)(int thisa, int sx,int sy,int ip,bool Sell, int Inventype, bool bItemTextListBoxUse)) 0x007E3E30)
#define sub_83CBE0							((int   (__thiscall*)(void *thisa)) 0x0083CBE0)
#define MyInventory_Update					((bool(__thiscall*)(void *thisa)) 0x007DB160)
#define calcMaxDurability					((WORD(__cdecl*)(int ip, ITEM_ATTRIBUTE *p, int Level)) 0x005C2170)
#define GetSlotIndexAtPt					((int(__stdcall*)(unsigned __int8 col, unsigned __int8 fil, int temporal)) 0x0083C770)
#define CreateBugSub_						((bool(__cdecl*)(int Type, int Position, int Owner, int o, int SubType, int LinkBone)) 0x005013B0)
#define PetProcess							((int(*)()) 0x004DB230)
#define IsPetProcess						((bool(__thiscall*)(int thisa, int type)) 0x00925700)
#define Process_DeletePet					((void(__thiscall*)(int thisa, int Owner, int itemType)) 0x009253D0)
#define Process_CreatePet					((bool(__thiscall*)(int thisa, int itemType, int modelType, float* Position, int Owner, int SubType, int LinkBone)) 0x009250E0)
#define g_pNPCShop							((int(__thiscall*)(int Instance)) 0x00861280)
#define SetSellingItem						((void(__thiscall*)(int thls, bool bFlag)) 0x00847FF0)
#define ChangeChaosCastleUnit						((void(__cdecl*)(int Character)) 0x004E6670)

namespace SEASON3B
{
	void CreateFlyBug(int, int, int, int, int);
	bool CreatePetProcess(int, int, float*, int, int, int);
}


class CNewUIMyInventory
{
public:
	CNewUIMyInventory(void);
	virtual ~CNewUIMyInventory(void);

	void Init();
	//-- Protocolo
	void ReceiveInventory(BYTE* ReceiveBuffer);
	void ReceiveDropItem(BYTE* ReceiveBuffer);
	void ReceiveDurability(BYTE* ReceiveBuffer);
	void ReceiveItemChange(BYTE* ReceiveBuffer);
	void ReceiveDeleteInventory(BYTE* ReceiveBuffer);
	//--
	static void LoadImages();
	static void Backup_PickedItem();
	static bool __thiscall Update(DWORD* a1);
	static void __thiscall RenderFrame(DWORD thisa);
	static void __thiscall SetButtonInfo(DWORD thisa);
	static void __thiscall Render3D(signed int* thisa);
	static bool __thiscall InventoryProcess(int thisa);
	static void __thiscall RenderEquippedItem(DWORD thisa);
	static bool __thiscall EquipmentWindowProcess(DWORD thisa);
	static void __thiscall SetEquipmentSlotInfo(DWORD thisa);
	static void __thiscall RenderItemToolTip(int thisa, int iSlotIndex);
	static void RenderEquipped(GLuint uiImageType, float x, float y, float width, float height);
	static void __thiscall RenderDetailsText(int thisa, int iPos_x, int iPos_y, LPCSTR pszText, int iBoxWidth, int iBoxHeight, int iSort, OUT SIZE* lpTextSize);
	//--
	static bool __thiscall NewUIManager_Render(int thls);

	static void __thiscall RenderLeft(int thls);
};

extern int TypeInventory;
extern CNewUIMyInventory g_pMyInventory;
extern CCharacterMachine* Character_Machin;

#endif