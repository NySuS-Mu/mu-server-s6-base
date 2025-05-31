#pragma once

#include "Protocol.h"
#include "Interface.h"
#include "CNewUIWindowsClient.h"

#define MAX_INVASION 30
#define MAX_INVASION_MONSTER 500
#define pCheckInMouse						((bool(__cdecl*)(int x, int y, int w, int h)) 0x00790B10)
#define IsRelease							((bool  (__cdecl*)(int iVirtKey))0x00791050)

struct EVENT_INVASION_ACTION
{
	PSBMSG_HEAD h;
	int index;
};

struct INVASION_INFO
{
	int Index;
	int State;
	int RemainTime;
	char NameInvasion[128];
	int Page;
};

struct PMSG_INVASION_INFO
{
	PWMSG_HEAD2 h;
	INVASION_INFO Info[MAX_INVASION];
};

struct INVASION_INFO_MONTER
{
	int Class;
	int Count;
	int CountMax;
	int RegenTime;
	int RegenType;
	int RegenTimeSave;
};

struct PMSG_INVASION_INFO_MONTER
{
	PWMSG_HEAD2 h;
	INVASION_INFO_MONTER Info[20];
};

class EventInvasion
{
public:
	EventInvasion();

	void ImageLoad();
	void BinObeject();
	void Button(DWORD Event);
	void Draw();
	void OpenMain();
	bool EventDraw_Open(DWORD Event);
	void GCListEvent(PMSG_INVASION_INFO* lpMsg);
	void GCListMonter(PMSG_INVASION_INFO_MONTER* lpMsg);
	
private:
	int IdEventInvasion;
	int Count;
	int HightFix;
	int MaxEventInvasion;
	INVASION_INFO m_Info[MAX_INVASION];
	INVASION_INFO_MONTER m_Monter[20];
	int Page;
	float StartY;
	float StartX;
	bool Moving;
	short maxX;
	short maxY;
	float drawx;
	float drawy;
	DWORD DelayMove;
	DWORD ultimoX;
	DWORD ultimoY;
	DWORD VKBUTTON_DELAY2;

};
extern int CloseInvasion;
extern int NextInvasion;
extern int PrewInvasion;
extern EventInvasion gEventInvasion;