// Shop.cpp: implementation of the CShop class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ItemValue.h"
#include "Shop.h"
#include "SocketItemOption.h"
#include "SocketItemType.h"
#include "MemScript.h"
#include "User.h"
#include "Util.h"
#include "ItemValue.h"

CShop gShop;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShop::CShop() // OK
{
	this->Init();
}

CShop::~CShop() // OK
{

}

void CShop::Init() // OK
{
	for(int n=0;n < SHOP_SIZE;n++)
	{
		this->m_Item[n].Clear();
		this->m_InventoryMap[n] = -1;
	}
}

void CShop::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			int ItemIndex = SafeGetItem(GET_ITEM(lpMemScript->GetNumber(),lpMemScript->GetAsNumber()));

			int ItemLevel = lpMemScript->GetAsNumber();

			int ItemDurability = lpMemScript->GetAsNumber();

			int ItemOption1 = lpMemScript->GetAsNumber();

			int ItemOption2 = lpMemScript->GetAsNumber();

			int ItemOption3 = lpMemScript->GetAsNumber();

			int ItemNewOption = lpMemScript->GetAsNumber();

			int AncOption = lpMemScript->GetAsNumber();

			int JOH	= lpMemScript->GetAsNumber();

			int OpEx = lpMemScript->GetAsNumber();

			int Socket1 = lpMemScript->GetAsNumber();

			int Socket2 = lpMemScript->GetAsNumber();

			int Socket3 = lpMemScript->GetAsNumber();

			int Socket4 = lpMemScript->GetAsNumber();

			int Socket5 = lpMemScript->GetAsNumber();

			this->InsertItemNew(ItemIndex,ItemLevel,ItemDurability,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,AncOption,JOH,OpEx,Socket1,Socket2,Socket3,Socket4,Socket5,0);


			//this->InsertItem(ItemIndex,ItemLevel,ItemDurability,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,0);
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CShop::ShopItemSet(int slot,BYTE type) // OK
{
	if(SHOP_INVENTORY_RANGE(slot) == 0)
	{
		return;
	}

	ITEM_INFO ItemInfo;

	if(gItemManager.GetInfo(this->m_Item[slot].m_Index,&ItemInfo) == 0)
	{
		return;
	}

	int x = slot%8;
	int y = slot/8;

	if((x+ItemInfo.Width) > 8 || (y+ItemInfo.Height) > 15)
	{
		return;
	}

	for(int sy=0;sy < ItemInfo.Height;sy++)
	{
		for(int sx=0;sx < ItemInfo.Width;sx++)
		{
			this->m_InventoryMap[(((sy+y)*8)+(sx+x))] = type;
		}
	}
}

BYTE CShop::ShopRectCheck(int x,int y,int width,int height) // OK
{
	if((x+width) > 8 || (y+height) > 15)
	{
		return 0xFF;
	}

	for(int sy=0;sy < height;sy++)
	{
		for(int sx=0;sx < width;sx++)
		{
			if(this->m_InventoryMap[(((sy+y)*8)+(sx+x))] != 0xFF)
			{
				return 0xFF;
			}
		}
	}

	return ((y*8)+x);
}

void CShop::InsertItem(int ItemIndex,int ItemLevel,int ItemDurability,int ItemOption1,int ItemOption2,int ItemOption3,int ItemNewOption,int ItemValue) // OK
{
	ITEM_INFO ItemInfo;

	if(gItemManager.GetInfo(ItemIndex,&ItemInfo) == 0)
	{
		return;
	}

	for(int y=0;y < 15;y++)
	{
		for(int x=0;x < 8;x++)
		{
			if(this->m_InventoryMap[((y*8)+x)] == 0xFF)
			{
				BYTE slot = this->ShopRectCheck(x,y,ItemInfo.Width,ItemInfo.Height);

				if(slot != 0xFF)
				{
					this->m_Item[slot].m_Level = ItemLevel;
					this->m_Item[slot].m_Durability = (float)((ItemDurability==0)?gItemManager.GetItemDurability(ItemIndex,ItemLevel,ItemNewOption,0):ItemDurability);
					this->m_Item[slot].Convert(ItemIndex,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,0,0,0,0,0xFF);
					this->m_Item[slot].m_PcPointValue = ItemValue;
					this->ShopItemSet(slot,1);
					return;
				}
			}
		}
	}
}

void CShop::InsertItemNew(int ItemIndex,int ItemLevel,int ItemDurability,int ItemOption1,int ItemOption2,int ItemOption3,int ItemNewOption,int Anc, int JOH, int OpEx, int Socket1, int Socket2, int Socket3, int Socket4, int Socket5, int ItemValue) // OK
{
	ITEM_INFO ItemInfo;

	if(gItemManager.GetInfo(ItemIndex,&ItemInfo) == 0)
	{
		return;
	}

	for(int y=0;y < 15;y++)
	{
		for(int x=0;x < 8;x++)
		{
			if(this->m_InventoryMap[((y*8)+x)] == 0xFF)
			{
				BYTE slot = this->ShopRectCheck(x,y,ItemInfo.Width,ItemInfo.Height);

				if(slot != 0xFF)
				{
					this->m_Item[slot].m_Level = ItemLevel;
					this->m_Item[slot].m_Durability = (float)((ItemDurability==0)?gItemManager.GetItemDurability(ItemIndex,ItemLevel,ItemNewOption,0):ItemDurability);


					BYTE ItemSocketOption[MAX_SOCKET_OPTION] = {0xFF,0xFF,0xFF,0xFF,0xFF};

					int qtd;

					if (gSocketItemType.CheckSocketItemType(ItemIndex) == 1)
					{
						qtd = gSocketItemType.GetSocketItemMaxSocket(ItemIndex);

						ItemSocketOption[0] = (BYTE)((qtd > 0)?((Socket1 != 255)?Socket1:255):255);
						ItemSocketOption[1] = (BYTE)((qtd > 1)?((Socket2 != 255)?Socket2:255):255);
						ItemSocketOption[2] = (BYTE)((qtd > 2)?((Socket3 != 255)?Socket3:255):255);
						ItemSocketOption[3] = (BYTE)((qtd > 3)?((Socket4 != 255)?Socket4:255):255);
						ItemSocketOption[4] = (BYTE)((qtd > 4)?((Socket5 != 255)?Socket5:255):255);
						//this->m_Item[slot].m_SocketOptionBonus = gSocketItemOption.GetSocketItemBonusOption(this->m_Item);
					}


					this->m_Item[slot].Convert(ItemIndex,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,Anc,JOH,OpEx,ItemSocketOption,0xFF);
					
					this->m_Item[slot].m_PcPointValue = ItemValue;

					//int value = 0;
					//int coin1 = 0;
					//int coin2 = 0;
					//int coin3 = 0;

					//if(gItemValue.GetItemValueNew(&this->m_Item[slot],&value,&coin1,&coin2,&coin3) != 0)
					//{
					//	this->m_Item[slot].Zen = value;
					//	this->m_Item[slot].Zen = value;
					//	this->m_Item[slot].Zen = value;
					//	this->m_Item[slot].Zen = value;
					//}
					//else 
					//{
					//	this->m_Item[slot].Zen = this->m_Item[slot].m_BuyMoney;
					//}
						

					this->ShopItemSet(slot,1);
					return;
				}
			}
		}
	}
}

bool CShop::GetItem(CItem* lpItem,int slot) // OK
{
	if(SHOP_INVENTORY_RANGE(slot) != 0)
	{
		if(this->m_Item[slot].IsItem() != 0)
		{
			(*lpItem) = this->m_Item[slot];
			return 1;
		}
	}

	return 0;
}

long CShop::GetItemCount() // OK
{
	int count = 0;

	for(int n=0;n < SHOP_SIZE;n++)
	{
		if(this->m_Item[n].IsItem() != 0)
		{
			count++;
		}
	}

	return count;
}

int CShop::GetItemPrice(CItem* lpItem, int* type)
{
	for (int n = 0; n < SHOP_SIZE; n++)
	{
		if (this->m_Item[n].IsItem() != 0)
		{
			if (this->m_Item[n].m_Index == lpItem->m_Index && this->m_Item[n].m_Level == lpItem->m_Level &&
				this->m_Item[n].m_Option1 == lpItem->m_Option1 && this->m_Item[n].m_Option2 == lpItem->m_Option2 &&
				this->m_Item[n].m_NewOption == lpItem->m_NewOption && this->m_Item[n].m_SetOption == lpItem->m_SetOption &&
				this->m_Item[n].m_ItemOptionEx == lpItem->m_ItemOptionEx)
			{
				(*type) = this->m_Item[n].m_PriceType;

				switch (this->m_Item[n].m_PriceType)
				{
				case WCOINC: return this->m_Item[n].m_SellWCoinC;
				case WCOINP: return this->m_Item[n].m_SellWCoinP;
				case WCOING: return this->m_Item[n].m_SellWCoinG;
				case RUUD: return this->m_Item[n].m_SellRuud;
				default: return this->m_Item[n].m_SellMoney;
				}
			}
		}
	}

	return 0;
}


bool CShop::GCShopItemListSend(int aIndex) // OK
{
	BYTE send[2048];

	PMSG_SHOP_ITEM_LIST_SEND pMsg;

	pMsg.header.set(0x31,0);

	int size = sizeof(pMsg);

	pMsg.type = 0;

	pMsg.count = 0;

	PMSG_SHOP_ITEM_LIST info;

	for(int n=0;n < SHOP_SIZE;n++)
	{
		if(this->m_Item[n].IsItem() != 0)
		{
			info.slot = n;

			gItemManager.ItemByteConvert(info.ItemInfo,this->m_Item[n]);

			memcpy(&send[size],&info,sizeof(info));
			size += sizeof(info);

			pMsg.count++;
		}
	}

	pMsg.header.size[0] = SET_NUMBERHB(size);
	pMsg.header.size[1] = SET_NUMBERLB(size);

	memcpy(send,&pMsg,sizeof(pMsg));

	DataSend(aIndex,send,size);

	return 1;
}