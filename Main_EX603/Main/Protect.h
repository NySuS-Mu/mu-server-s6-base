// Protect.h: interface for the CProtect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CustomFog.h"
#include "CustomJewel.h"
#include "CustomMessage.h"
#include "CustomWing.h"
#include "ItemSmoke.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "CustomItem.h"
#include "CustomNpcName.h"
#include "CustomMonster.h"
#include "CustomBow.h"
#include "CustomGloves.h"
#include "CustomBuffIcon.h"
#include "CustomCloak.h"
#include "CustomEarthQuakeSkill.h"
#include "CustomMonsterEffect.h"
#include "CustomMonsterGlow.h"
#include "CustomPet.h"
#include "CustomPetEffect.h"
#include "CustomPetEffectDynamic.h"
#include "CustomPetGlow.h"
#include "CustomRenderExcGlow.h"
#include "ItemManager.h"
#include "ItemTooltip.h"
#include "ItemTRSData.h"
#include "CustomModelEffect.h"
#include "CustomServerInfo.h"
#include "CustomMap.h"
#include "RuneEffect.h"
#include "ItemShopValue.h"

struct MAIN_FILE_INFO
{
	BYTE LauncherType; 
	char LauncherName[32];
	char CustomerName[32];
	char IpAddress[32];
	WORD IpAddressPort;
	char ClientVersion[8];
	char ClientSerial[17];
	char WindowName[32];
	char ScreenShotPath[50];
	char ClientName[32];
	char PluginName[32];
	char PluginName2[32];
	char PluginName3[32];
	char PluginName4[32];
	char PluginName5[32];
	DWORD ClientCRC32;
	DWORD PluginCRC32;
	DWORD Plugin2CRC32;
	DWORD Plugin3CRC32;
	DWORD Plugin4CRC32;
	DWORD Plugin5CRC32;
	DWORD HelperActiveAlert;
	DWORD HelperActiveLevel;
	DWORD DWMaxAttackSpeed;
	DWORD DKMaxAttackSpeed;
	DWORD FEMaxAttackSpeed;
	DWORD MGMaxAttackSpeed;
	DWORD DLMaxAttackSpeed;
	DWORD SUMaxAttackSpeed;
	DWORD RFMaxAttackSpeed;
	DWORD ReconnectTime;
	DWORD Language;
	DWORD ReduceMemory;
	DWORD SystemFPS;
	DWORD CameraType;
	DWORD ServerTime;
	DWORD MaxPartyMembers;
	DWORD ShowInfoWindowedMode;
	DWORD ShowInfoWindowedModeType;
	DWORD RemoveClass;
	DWORD RankUserType; 
	DWORD CsSkill; 
	DWORD PrintLogo;
	DWORD CustomStoreEnableJoB;
	DWORD CustomStoreEnableJoS;
	DWORD CustomStoreEnableJoC;
	DWORD CustomStoreEnableCoin1;
	DWORD CustomStoreEnableCoin2;
	DWORD CustomStoreEnableCoin3;
	DWORD CustomOffStoreEnable;
	DWORD DisablePartyHpBar;
	DWORD RankUserShowOverHead;
	DWORD RankUserOnlyOnSafeZone;
	DWORD RankUserShowReset;
	DWORD RankUserShowMasterReset;
	DWORD RankUserNeedAltKey;
	DWORD ActiveInvasion;
	DWORD CustomOptionPanel;
	DWORD ItemTooltipDrop;
	DWORD ItemTooltipDropType;
	DWORD AlwaysPlayerShowName;
	DWORD PlayerShowGuildLogo;
	DWORD RuneEffect;
	DWORD ItemTooltipUpgrade;
	DWORD InventoryUpgrade;
	DWORD CustomInterfaceType;
	DWORD ScaleWidescreen;
	DWORD ScaleItem;
	DWORD SelectServerType;
	DWORD SelectCharacterType;
	DWORD SelectCharacterSystem;
	DWORD SelectCharacterAnimation;
	DWORD DisableCustomAutoLogin;
#if(REGISTER_ACCOUNT)
	DWORD DisableCustomRegister;
#endif
	DWORD DisableCustomClaws;
	DWORD DisableCustomBow;
	DWORD DisableCustomCloack;
	DWORD DisableCustomPosition;
	DWORD DisableCustomPet;
	DWORD DisableAdvance;

	DWORD DisableTree;
	DWORD DisableReflectEffect;
	DWORD DisableEffectPlus15;
	DWORD DisableGens;
	DWORD DisableTabMap;
	DWORD DisableBattleZoneWindow;
	DWORD DisableMoveWindow;
	DWORD DisableBCDSCCMaster;
	DWORD Disable380MixChaosMachine;
	DWORD DisableHelper;
	DWORD DisableClickEffect;
	DWORD DisableCashShopKeyX;
	DWORD DisableWCoinCCashShop;
	DWORD DisableWCoinPCashShop;
	DWORD DisableWCoinGCashShop;
	DWORD DisableSocketInvetory;
	DWORD DisableAncientInventory;
	DWORD DisableRepeirInInventory;
	DWORD DisableButtonOpenStore;
	DWORD DisableButtonInventoryExt;
	DWORD DisableButtonQuestInStats;
	DWORD DisableButtonPetsInStats;
	DWORD DisableButtonSkillMaster;
	DWORD DisableButtonVaultExt;
	DWORD DisableBlueEyeEffect;
	DWORD DisableFlareGlovesEffect;
	DWORD DisableGlowMuSignEffect;
	DWORD DisableWebzenChatCommand;
	DWORD DiscordRPCSwitch;
	char APPLICATION_ID[32];
	char state[32];
	char details[32];
	char largeImageKey[32];
	char largeImageText[32];
	char smallImageKey[32];
	char smallImageText[32];
	int m_BloodCastleEntryLevelCommon[7][2];
	int m_BloodCastleEntryLevelSpecial[7][2];
	int m_DevilSquareEntryLevelCommon[6][2];
	int m_DevilSquareEntryLevelSpecial[6][2];
	int m_ChaosCastleEntryLevelCommon[6][2];
	int m_ChaosCastleEntryLevelSpecial[6][2];
	int m_KalimaEntryLevelCommon[7][2];
	int m_KalimaEntryLevelSpecial[7][2];
	int m_IllusionTempleEntryLevelMin[5];
	int m_IllusionTempleEntryLevelMax[5];
	CUSTOM_MESSAGE_INFO EngCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO PorCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO SpnCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOMMONSTER_DATA CustomMonsters[MAX_CUSTOMMONSTER];
	BOSSCLASS_DATA CustomBossClass[MAX_BOSSCLASS];
	NPCNAME_DATA CustomNPCName[MAX_CUSTOM_NPCNAME];
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	CUSTOM_WING_EFFECT_INFO CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
	DYNAMIC_WING_EFFECT_INFO DynamicWingEffectInfo[MAX_DYNAMIC_WING_EFFECT];
	CUSTOM_SMOKEEFFECT CustomSmokeEffect[MAX_SMOKE_ITEMS];
	CUSTOM_BOW_INFO CustomBowInfo[MAX_CUSTOM_BOW];
	CUSTOM_RF_GLOVES CustomGloves[MAX_CUSTOM_GLOVES];
	RenderTooltipBuff m_TooltipTRSDataEng[256];
	CUSTOMCLOAK_DATA m_CustomCloak[MAX_CUSTOMCLOAK];
	HORSE_EARTH_QUAKE m_EarthQuakeLoad[MAX_EARTH_QUAKE];
	xMonsterEffect m_CustomMonsterEffect[MAX_EFFECT_MONSTER];
	CUSTOM_MONSTERGLOW_INFO m_CustomMonsterGlow[MAX_CUSTOM_MONSTERGLOW];
	CUSTOM_GLOW_INFO m_CustomMonsterbrightness[MAX_CUSTOM_MONSTERGLOW];
	CUSTOM_PET_INFO CustomPetInfo[MAX_PET_ITEM];
	PET_EFFECT_CUSTOM m_CustomPetCEffect[MAX_PET_EFFECT_STATIC];
	PET_DYNAMIC_CUSTOM m_DynamicPetEffect[MAX_PET_EFFECT_DYNAMIC];
	RENDER_MESH RenderMeshPet[MAX_PET_GLOW];
	JCItemnoGlow m_JCWRemoveGlow[ MAX_NOGLOW ];
	ITEM_INFO m_ItemInfoEx[MAX_ITEM2];
	nInformation m_TRSTooltipData[MaxLine];
	nText m_TRSTooltipText[MaxLine];
	CUSTOM_POSITION_INFO CustomPosition[MAX_POSITION_ITEM];
	CUSTOM_MODEL_EFFECT_INFO m_CustomModelInfo[MAX_MODEL_EFFECT];
	CUSTOM_FOG_INFO CustomFogInfo[MAX_FOG];
	SERVERINFO_DATA m_ServerInfo[MAX_SERVER_CLASS];
	PathMap m_MapInfo[MAX_CUSTOM_MAP];
	RuneEffectType m_RuneEffect[MAX_TYPE_RUNEEFFECT];
	CUSTOM_ITEMPRICE CustomItemPrice[MAX_ITEMPRICE];

};

class CProtect
{
public:
	CProtect();
	virtual ~CProtect();
	bool ReadMainFile(char* name);
	void CheckLauncher();
	void CheckInstance();
	void CheckClientFile();
	void CheckPluginFile();
	void CheckPluginFile2();
	void CheckPluginFile3();
	void CheckPluginFile4();
	void CheckPluginFile5();
	void CheckLauncherCommandLine();
public:
	MAIN_FILE_INFO m_MainInfo;
	DWORD m_ClientFileCRC;
};

extern CProtect gProtect;
