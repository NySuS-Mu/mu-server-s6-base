#include "StdAfx.h"
#include "user.h"
#include "MemScript.h"
#include "Util.h"
#include "CashShop.h"
#include "Monster.h"
#include "Notice.h"
#include "Message.h"
#include "Guild.h"
#include "CustomBonusPoint.h"
// -------------------------------------------------------------------------------
ShopPointEx gShopPointEx;
// -------------------------------------------------------------------------------

ShopPointEx::ShopPointEx()
{
	this->Init();
}
// -------------------------------------------------------------------------------

ShopPointEx::~ShopPointEx()
{
	// ----
}
// -------------------------------------------------------------------------------

void ShopPointEx::Init()
{
	this->m_IsLoaded			= false;
	this->m_MonsterLoaded		= 0;
	// ----
	for( int i = 0; i < MAX_SHOPPOINTEX_EVENT; i++ )
	{
		this->m_EventBonus[i].AddCoinC = 0;
		this->m_EventBonus[i].AddCoinP = 0;
		this->m_EventBonus[i].AddCoinG = 0;
	}
	// ----
	this->m_MobsData.clear();
}
// -------------------------------------------------------------------------------

void ShopPointEx::Load(char* path)
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
		
			int section = lpMemScript->GetNumber();

			while(true)
			{
				
				if(section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					int Slot = lpMemScript->GetNumber();

					this->m_EventBonus[Slot].AddCoinC = lpMemScript->GetAsNumber();

					this->m_EventBonus[Slot].AddCoinP = lpMemScript->GetAsNumber();

					this->m_EventBonus[Slot].AddCoinG = lpMemScript->GetAsNumber();

					this->m_EventBonus[Slot].AddRuud = lpMemScript->GetAsNumber();

				}
				else if(section == 2)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					SHOPPOINTEX_MONSTER info;

					info.MonsterID = lpMemScript->GetNumber();

					info.MapNumber = lpMemScript->GetAsNumber();

					info.AddCoinC = lpMemScript->GetAsNumber();
					info.AddCoinP = lpMemScript->GetAsNumber();
					info.AddCoinG = lpMemScript->GetAsNumber();
					info.AddRuud = lpMemScript->GetAsNumber();
					info.AddGuildScore = lpMemScript->GetAsNumber();

					this->m_MobsData.push_back(info);
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
	this->m_IsLoaded = true;
}
// -------------------------------------------------------------------------------

int ShopPointEx::GetMonsterSlot(int Class, int Map)
{
	for( int i = 0; i < this->m_MobsData.size(); i++ )
	{
		if( this->m_MobsData[i].MonsterID != Class )
		{
			continue;
		}
		// ----
		if( this->m_MobsData[i].MapNumber != Map && this->m_MobsData[i].MapNumber != -1 )
		{
			continue;
		}
		// ----
		return i;
	}
	// ----
	return -1;
}

// -------------------------------------------------------------------------------

void ShopPointEx::AddEventBonus(int UserIndex, ShopPointExEvent::T Event)
{
	if( !this->m_IsLoaded )
	{
		return;
	}
	// ----
	//gGameShop.GDReqPoint(UserIndex);
	//gObj[UserIndex].GameShop.WCoinC			+= this->m_EventBonus[Event].AddCoinC;
	//gObj[UserIndex].GameShop.WCoinP			+= this->m_EventBonus[Event].AddCoinP;
	//gObj[UserIndex].GameShop.GoblinPoint	+= this->m_EventBonus[Event].AddCoinG;
	gCashShop.GDCashShopAddPointSaveSend(UserIndex,0, this->m_EventBonus[Event].AddCoinC, this->m_EventBonus[Event].AddCoinP, this->m_EventBonus[Event].AddCoinG, this->m_EventBonus[Event].AddRuud);
	gCashShop.CGCashShopPointRecv(UserIndex);
	// ----
	/*gObj[UserIndex].BankEx.Credits += this->m_EventBonus[Event].AddCredits;
	gBankEx.GCUpdateBankEx(UserIndex);
	gBankEx.GDSavePoint(UserIndex);*/
	// ----
	this->SendNotify(UserIndex, this->m_EventBonus[Event].AddCoinC, this->m_EventBonus[Event].AddCoinP, this->m_EventBonus[Event].AddCoinG, this->m_EventBonus[Event].AddRuud, gMessage.GetMessage(883));
}
// -------------------------------------------------------------------------------

void ShopPointEx::AddMonsterBonus(LPOBJ lpMonster, LPOBJ lpObj)
{
	if( !this->m_IsLoaded )
	{
		return;
	}
	// ----
	int MonsterSlot = this->GetMonsterSlot(gObj[lpMonster->Index].Class, gObj[lpMonster->Index].Map);
	// ----
	if( MonsterSlot == -1 )
	{
		return;
	}

	int aIndex = gObjMonsterGetTopHitDamageUser(lpObj);

	if(OBJECT_RANGE(aIndex) != 0)
	{
		lpObj = &gObj[aIndex];
	}
	// ----

	gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0, this->m_MobsData[MonsterSlot].AddCoinC, this->m_MobsData[MonsterSlot].AddCoinP, this->m_MobsData[MonsterSlot].AddCoinG, this->m_MobsData[MonsterSlot].AddRuud);
	// ----
	gCashShop.CGCashShopPointRecv(lpObj->Index);
	/*lpObj->BankEx.Credits += this->m_MobsData[MonsterSlot].AddCredits;
	gBankEx.GCUpdateBankEx(lpObj->Index);
	gBankEx.GDSavePoint(lpObj->Index);*/
	if (lpObj->Guild != 0)
	{
		lpObj->Guild->TotalScore += this->m_MobsData[MonsterSlot].AddGuildScore;
		if (this->m_MobsData[MonsterSlot].AddGuildScore > 0)
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(884), this->m_MobsData[MonsterSlot].AddGuildScore);
		}
		//DGGuildScoreUpdate(lpObj->Guild->Name,lpObj->Guild->TotalScore);

		for(int n = 0; n < MAX_GUILD_USER; n++)
		{
			if(lpObj->Guild->Use[n] && lpObj->Guild->Index[n] >= 0)
			{
				gGuild.GCGuildWarScoreSend(lpObj->Guild->Index[n]);
			}
		}
	}
	
	// ----
	this->SendNotify(lpObj->Index, this->m_MobsData[MonsterSlot].AddCoinC, this->m_MobsData[MonsterSlot].AddCoinP, this->m_MobsData[MonsterSlot].AddCoinG, this->m_MobsData[MonsterSlot].AddRuud, gMessage.GetMessage(885));
}
// -------------------------------------------------------------------------------

void ShopPointEx::SendNotify(int UserIndex, int CoinC, int CoinP, int CoinG,int Ruud, char* Text)
{
	//gGameShop.GDSavePoint(UserIndex);
	// ----
	//char Text[256];
	//ZeroMemory(Text, sizeof(Text));
	// ----
	if( CoinC > 0 )
	{
		gNotice.GCNoticeSend(UserIndex,1,0,0,0,0,0,gMessage.GetMessage(886), Text, CoinC);
	}
	// ----
	if( CoinP > 0 )
	{
		gNotice.GCNoticeSend(UserIndex,1,0,0,0,0,0,gMessage.GetMessage(887), Text, CoinP);
	}
	// ----
	if( CoinG > 0 )
	{
		gNotice.GCNoticeSend(UserIndex,1,0,0,0,0,0,gMessage.GetMessage(888), Text, CoinG);
	}
	if (Ruud > 0)
	{
		gNotice.GCNoticeSend(UserIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(890), Text, Ruud);
	}
	/*if ( Credits > 0)
	{
		gNotice.GCNoticeSend(UserIndex,1,0,0,0,0,0,"[%s] Obtained %d WCoinC", Text, Credits,gMessage.GetMessage(527));
	}*/
}
// -------------------------------------------------------------------------------