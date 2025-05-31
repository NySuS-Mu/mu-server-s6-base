// ServerDisplayer.cpp: implementation of the CServerDisplayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServerDisplayer.h"
#include "CustomArena.h"
#include "GameMain.h"
#include "Log.h"
#include "Protect.h"
#include "resource.h"
#include "ServerInfo.h"
#include "SocketManager.h"
#include "User.h"

CServerDisplayer gServerDisplayer;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerDisplayer::CServerDisplayer() // OK
{
	this->EventBc = -1;

	for(int n=0;n < MAX_LOG_TEXT_LINE;n++)
	{
		memset(&this->m_log[n],0,sizeof(this->m_log[n]));
	}

	this->m_font = CreateFont(50,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Times");
	this->m_font2 = CreateFont(24,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Times");
	this->m_font3 = CreateFont(15,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"MS Sans Serif");
	this->m_font4 = CreateFont(20,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Times");
	
	
	this->m_brush[0] = CreateSolidBrush(RGB(100, 100, 255));		
	this->m_brush[1] = CreateSolidBrush(RGB(120, 120, 120));	
	this->m_brush[2] = CreateSolidBrush(RGB(49, 54, 56));	
	this->m_brush[3] = CreateSolidBrush(RGB(0, 0, 0));
	this->m_brush[4] = CreateSolidBrush(RGB(49, 54, 56));
}

CServerDisplayer::~CServerDisplayer() // OK
{
	DeleteObject(this->m_font);
	DeleteObject(this->m_brush[0]);
	DeleteObject(this->m_brush[1]);
	DeleteObject(this->m_brush[2]);
	DeleteObject(this->m_brush[3]);
	DeleteObject(this->m_brush[4]);
}

void CServerDisplayer::Init(HWND hWnd) // OK
{
	PROTECT_START

	this->m_hwnd = hWnd;

	PROTECT_FINAL

	gLog.AddLog(1,"LOG");

	gLog.AddLog(gServerInfo.m_WriteChatLog,"LOG\\CHAT_LOG");

	gLog.AddLog(gServerInfo.m_WriteCommandLog,"LOG\\COMMAND_LOG");

	gLog.AddLog(gServerInfo.m_WriteTradeLog,"LOG\\TRADE_LOG");

	gLog.AddLog(gServerInfo.m_WriteConnectLog,"LOG\\CONNECT_LOG");

	gLog.AddLog(gServerInfo.m_WriteHackLog,"LOG\\HACK_LOG");

	gLog.AddLog(gServerInfo.m_WriteCashShopLog,"LOG\\CASH_SHOP_LOG");

	gLog.AddLog(gServerInfo.m_WriteChaosMixLog,"LOG\\CHAOS_MIX_LOG");

	gLog.AddLog(gServerInfo.m_WriteItemLog,"LOG\\ITEM_LOG");
}

void CServerDisplayer::Run() // OK
{
	this->LogTextPaint();
	this->PaintName();
	this->SetWindowName();
	this->PaintAllInfo();
	this->PaintOnline();
	this->PaintUpdate();
	this->PaintEventTime();
	this->PaintInvasionTime();
	this->PaintCustomEventTime();
	this->LogTextPaintConnect();
	this->LogTextPaintGlobalMessage();
	this->PaintBarInfo();
}

void CServerDisplayer::SetWindowName() // OK
{
	char buff[256];

	wsprintf(buff,"[%s] %s - %s",GAMESERVER_VERSION,GAMESERVER_CLIENT,gServerInfo.m_ServerName);

	SetWindowText(this->m_hwnd,buff);

}

void CServerDisplayer::PaintBarInfo() // OK
{
	HWND hWndStatusBar = GetDlgItem(this->m_hwnd,IDC_STATUSBAR);

	char text[256];

	wsprintf(text, "Online Players: %d/%d", gObjTotalUser,gServerInfo.m_ServerMaxUserNumber);

	SendMessage(hWndStatusBar, SB_SETTEXT, 0,(LPARAM)text);

	wsprintf(text, "OffStore: %d", gObjOffStore);

	SendMessage(hWndStatusBar, SB_SETTEXT, 1,(LPARAM)text);

	wsprintf(text, "OffAttack: %d", gObjOffAttack);

	SendMessage(hWndStatusBar, SB_SETTEXT, 2,(LPARAM)text);

	wsprintf(text, "All Bots: %d", gObjTotalBot);

	SendMessage(hWndStatusBar, SB_SETTEXT, 3,(LPARAM)text);

	wsprintf(text, "Monsters: %d/%d", gObjTotalMonster,MAX_OBJECT_MONSTER);

	SendMessage(hWndStatusBar, SB_SETTEXT, 4,(LPARAM)text);

	SendMessage(hWndStatusBar, SB_SETTEXT, 5,(LPARAM)NULL);

	ShowWindow(hWndStatusBar, SW_SHOWMAXIMIZED);
	ShowWindow(hWndStatusBar, SW_RESTORE);
}

void CServerDisplayer::PaintAllInfo() // OK activo y desactivado
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	long Medida = rect.right - 550;

	Medida = Medida / 3;

	rect.right = rect.right - 550 - Medida - Medida;
	//--
	rect.top = rect.top + 60;

	rect.bottom = rect.top + 25;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font4);

	if(gJoinServerConnection.CheckState() == 0 || gDataServerConnection.CheckState() == 0)
	{
		SetTextColor(hdc, RGB(250, 250, 250));
		FillRect(hdc, &rect, this->m_brush[1]);
		DrawText(hdc, GAMESERVER_STATUS, sizeof(GAMESERVER_STATUS), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		SetTextColor(hdc, RGB(250, 250, 250));
		FillRect(hdc, &rect, this->m_brush[0]);
		DrawText(hdc, GAMESERVER_STATUS_MODE, sizeof(GAMESERVER_STATUS_MODE), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	SelectObject(hdc,OldFont);

	SetBkMode(hdc,OldBkMode);

	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::PaintOnline() // OK
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	long Medida = rect.right - 550;
	long Media = Medida / 2;
	Medida = Medida / 3;

	rect.right = rect.right - 550 - Medida;

	rect.left = Medida + 2;
	//--
	rect.top = rect.top + 60;

	rect.bottom = rect.top + 25;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font4);

	char text[50];

	wsprintf(text, "ONLINE: %d/%d", gObjTotalUser,gServerInfo.m_ServerMaxUserNumber);


	if (gObjTotalUser > 0 )
	{
		SetTextColor(hdc, RGB(250, 250, 250));
		FillRect(hdc, &rect, this->m_brush[0]);
		TextOut(hdc, Media - 60, rect.top + 2, text, strlen(text));
	}
	else
	{
		SetTextColor(hdc, RGB(250, 250, 250));
		FillRect(hdc, &rect, this->m_brush[1]);
		TextOut(hdc, Media - 60, rect.top + 2, text, strlen(text));
	}

	SelectObject(hdc,OldFont);

	SetBkMode(hdc,OldBkMode);

	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::PaintUpdate() // OK Season6
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	long Medida = rect.right - 550;

	Medida = Medida / 3;

	rect.right = rect.right - 550;

	rect.left = Medida + Medida + 2;
	//--
	rect.top = rect.top + 60;

	rect.bottom = rect.top + 25;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc, TRANSPARENT);

	HFONT OldFont = (HFONT) SelectObject(hdc, this->m_font4);

	SetTextColor(hdc, RGB(250, 250, 250));
	
	FillRect(hdc, &rect, this->m_brush[0]);

	DrawText(hdc, UPDATE_NAME, sizeof(UPDATE_NAME), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(hdc, OldFont);
	SetBkMode(hdc, OldBkMode);
	ReleaseDC(this->m_hwnd, hdc);
}

void CServerDisplayer::PaintName() // OK nombre
{
	RECT rect;
	GetClientRect(this->m_hwnd,&rect);

	rect.top = 0;

	rect.bottom = 60;

	rect.right= rect.right - 550;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font);

	SetTextColor(hdc,RGB(250, 250, 250));

	FillRect(hdc,&rect,this->m_brush[2]);

#if (GAMESERVER_TYPE == 0)
	{
		DrawText(hdc, GAMESERVER_CLIENT, sizeof(GAMESERVER_CLIENT), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
#else
		{
			DrawText(hdc, GAMESERVER_CLIENT, sizeof(GAMESERVER_CLIENT), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
#endif

	SelectObject(hdc,OldFont);

	SetBkMode(hdc,OldBkMode);
	
	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::PaintCustomEventTime() // OK
{
#if(GAMESERVER_TYPE==0)
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	int posX1 = rect.right-545;
	int posX2 = rect.right-410;

	rect.left	= rect.right-550;
	rect.right	= rect.right-365;
	//rect.top	= 60;
	rect.bottom = 290;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	FillRect(hdc,&rect,this->m_brush[4]);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font3);

	char text1[20];
	char text2[30];
	int totalseconds;
	int hours;
	int minutes;
	int seconds;
	int days;

	SetTextColor(hdc,RGB(160, 160, 255));
	TextOut(hdc,rect.left+5,rect.top+2,"CUSTOM EVENTS:",13);

	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Online Lottery: ");

	if (this->EventCustomLottery == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventCustomLottery == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventCustomLottery;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}

	TextOut(hdc,posX1,rect.top + 2 + 15,text1,strlen(text1));
	if (this->EventCustomLottery == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventCustomLottery == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventCustomLottery < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}
	TextOut(hdc,posX2,rect.top + 2 + 15,text2,strlen(text2));

	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Quiz Event: ");

	if (this->EventCustomQuiz == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventCustomQuiz == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventCustomQuiz;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;
		wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}

	TextOut(hdc,posX1,rect.top + 2 + 30,text1,strlen(text1));
	if (this->EventCustomQuiz == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventCustomQuiz == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventCustomQuiz < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}
	TextOut(hdc,posX2,rect.top + 2 + 30,text2,strlen(text2));

	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Bonus Event: ");

	if (this->EventCustomBonus == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventCustomBonus == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventCustomBonus;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}

	TextOut(hdc,posX1,rect.top + 2 + 45,text1,strlen(text1));
	if (this->EventCustomBonus == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventCustomBonus == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventCustomBonus < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}
	TextOut(hdc,posX2,rect.top + 2 + 45,text2,strlen(text2));
	
	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Drop Event: ");

	if (this->EventDrop == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventDrop == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventDrop;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}

	TextOut(hdc,posX1,rect.top + 2 + 60,text1,strlen(text1));
	if (this->EventDrop == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventDrop == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventDrop < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}
	TextOut(hdc,posX2,rect.top + 2 + 60,text2,strlen(text2));

	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Team vs Team: ");

	if (this->EventTvT == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventTvT == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventTvT;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}

	TextOut(hdc,posX1,rect.top + 2 + 75,text1,strlen(text1));
	if (this->EventTvT == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventTvT == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventTvT < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}

	TextOut(hdc,posX2,rect.top + 2 + 75,text2,strlen(text2));

	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Guild vs Guild: ");

	if (this->EventGvG == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventGvG == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventGvG;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}

	TextOut(hdc,posX1,rect.top + 2 + 90,text1,strlen(text1));
	if (this->EventGvG == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventGvG == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventGvG < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc,RGB(0, 152, 239));
	}
	TextOut(hdc,posX2,rect.top + 2 + 90,text2,strlen(text2));

	SelectObject(hdc,OldFont);
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);

#else

	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	int posX1 = rect.right-545;
	int posX2 = rect.right-405;

	rect.left	= rect.right-550;
	rect.right	= rect.right-5;
	//rect.top	= 60;
	rect.bottom = 290;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	FillRect(hdc,&rect,this->m_brush[4]);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font3);

	char text1[20];
	char text2[30];
	char text3[30];
	char text4[30];
	int totalseconds;
	int hours;
	int minutes;
	int seconds;
	int days;

	SetTextColor(hdc,RGB(160, 160, 255));
	TextOut(hdc,rect.left+5,rect.top + 2,"EVENTS:",7);

	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Loren Deep: ");

	if (this->EventCastleDeep == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventCastleDeep == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventCastleDeep;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}

	TextOut(hdc, posX1, 30, text1, strlen(text1));
	if (this->EventCastleDeep == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventCastleDeep == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventCastleDeep < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc,RGB(0, 152, 239));
	}
	TextOut(hdc, posX2, 30, text2, strlen(text2));

	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "CryWolf: ");

	if (this->EventCryWolf == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventCryWolf == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventCryWolf;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}

	TextOut(hdc, posX1, 50, text1,strlen(text1));
	if (this->EventCryWolf == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventCryWolf == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventCryWolf < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}
	TextOut(hdc, posX2, 50,text2,strlen(text2));

	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Castle Siege: ");

	if (this->EventCs == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventCs == 0)
	{
		wsprintf(text2, "Adjust Date");
		wsprintf(text3, " ");
		wsprintf(text4, " ");
	}
	else
	{
		totalseconds	= this->EventCs;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text4, "- Next Stage: %d day(s)+", days);
		}
		else
		{
			wsprintf(text4, "- Next Stage: %02d:%02d:%02d", hours, minutes, seconds);
		}

		if(this->EventCsState == -1)
			wsprintf(text3, "- Stage %d: None", this->EventCsState);
		if(this->EventCsState == 0)
			wsprintf(text3, "- Stage %d: Idle 1", this->EventCsState);
		if(this->EventCsState == 1)
			wsprintf(text3, "- Stage %d: Guild Register", this->EventCsState);
		if(this->EventCsState == 2)
			wsprintf(text3, "- Stage %d: Idle 2", this->EventCsState);
		if(this->EventCsState == 3)
			wsprintf(text3, "- Stage %d: Mark Register", this->EventCsState);
		if(this->EventCsState == 4)
			wsprintf(text3, "- Stage %d: Idle 3", this->EventCsState);
		if(this->EventCsState == 5)
			wsprintf(text3, "- Stage %d: Notify", this->EventCsState);
		if(this->EventCsState == 6)
			wsprintf(text3, "- Stage %d: Ready Siege", this->EventCsState);
		if(this->EventCsState == 7)
			wsprintf(text3, "- Stage %d: Started Siege", this->EventCsState);
		if(this->EventCsState == 8)
			wsprintf(text3, "- Stage %d: Ended Siege", this->EventCsState);
		if(this->EventCsState == 9)
			wsprintf(text3, "- Stage %d: End All", this->EventCsState);
			
		if (this->EventCs)
			wsprintf(text2, "Stage %d", this->EventCsState);
	}

	TextOut(hdc, posX1, 70, text1, strlen(text1));
	if (this->EventCs == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}
	TextOut(hdc, posX2, 70, text2, strlen(text2));

	TextOut(hdc,posX1+5,155,text3,strlen(text3));

	TextOut(hdc,posX1+5,175,text4,strlen(text4));

	SelectObject(hdc,OldFont);
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);

#endif

}

void CServerDisplayer::PaintEventTime() // OK
{
#if(GAMESERVER_TYPE==0)
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	int posX1 = rect.right-355;
	int posX2 = rect.right-240;

	rect.left	= rect.right-360;
	rect.right	= rect.right-190;
	rect.bottom = 290;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	FillRect(hdc,&rect,this->m_brush[4]);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font3);

	char text1[20];
	char text2[30];
	int totalseconds;
	int hours;
	int minutes;
	int seconds;
	int days;

	SetTextColor(hdc,RGB(160, 160, 255));
	TextOut(hdc,rect.left+5,rect.top+2,"EVENTS:",7);

	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Blood Castle: ");

	if (this->EventBc == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventBc == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventBc;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;
		wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
	}
	
	TextOut(hdc,posX1,rect.top + 2 + 15,text1,strlen(text1));
	if (this->EventBc == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventBc == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventBc < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}
	TextOut(hdc,posX2,rect.top + 2 + 15,text2,strlen(text2));

	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Devil Square: ");

	if (this->EventDs == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventDs == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventDs;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;
		wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
	}

	TextOut(hdc,posX1,rect.top + 2 + 30,text1,strlen(text1));
	if (this->EventDs == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventDs == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventDs < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}

	TextOut(hdc,posX2,rect.top + 2 + 30,text2,strlen(text2));

	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Chaos Castle: ");

	if (this->EventCc == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventCc == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventCc;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;
		wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
	}

	TextOut(hdc,posX1,rect.top + 2 + 45,text1,strlen(text1));
	if (this->EventCc == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventCc == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventCc < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}
	TextOut(hdc,posX2,rect.top + 2 + 45,text2,strlen(text2));

	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Illusion Temple");

	if (this->EventIt == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventIt == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventIt;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}
	
	TextOut(hdc,posX1,rect.top + 2 + 60,text1,strlen(text1));
	if (this->EventIt == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventIt == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventIt < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}
	TextOut(hdc,posX2,rect.top + 2 + 60,text2,strlen(text2));

	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Moss Merchant: ");

	if (this->EventMoss == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->EventMoss == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventMoss;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}

	TextOut(hdc,posX1,rect.top + 2 + 75,text1,strlen(text1));

	if (this->EventMoss == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->EventMoss == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->EventMoss < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 152, 239));
	}

	TextOut(hdc,posX2,rect.top + 2 + 75,text2,strlen(text2));

	//--
	SetTextColor(hdc,RGB(255,255,255));
	wsprintf(text1, "Luke Helper: ");

	if (this->LukeHelper == -1)
	{
		wsprintf(text2, "Disabled");
	}
	else if (this->LukeHelper == 0)
	{
		wsprintf(text2, "Online");
	}
	else
	{
		totalseconds	= this->EventGvG;
		hours			= totalseconds/3600;
		minutes			= (totalseconds/60) % 60;  
		seconds			= totalseconds % 60;

		if (hours > 23)
		{
			days = hours/24;
			wsprintf(text2, "%d day(s)+", days);
		}
		else
		{
			wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
		}
	}

	TextOut(hdc,posX1,rect.top + 2 + 90,text1,strlen(text1));
	if (this->LukeHelper == -1)
	{
		SetTextColor(hdc,RGB(250, 50, 50));
	}
	else if (this->LukeHelper == 0)
	{
		SetTextColor(hdc,RGB(0, 255, 0));
	}
	else if (this->LukeHelper < 300)
	{
		SetTextColor(hdc,RGB(255, 255, 0));
	}
	else
	{
		SetTextColor(hdc,RGB(0, 152, 239));
	}
	TextOut(hdc,posX2,rect.top + 2 + 90,text2,strlen(text2));

	SelectObject(hdc,OldFont);
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);
	
#endif
}

void CServerDisplayer::PaintInvasionTime() // OK
{
#if(GAMESERVER_TYPE==0)
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);
	int posX1 = rect.right-180;
	int posX2 = rect.right-50;

	rect.left	= rect.right-185;
	rect.right	= rect.right-5;
	rect.bottom = 720;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	FillRect(hdc,&rect,this->m_brush[4]);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font3);

	char text1[20];
	char text2[30];
	int totalseconds;
	int hours;
	int minutes;
	int seconds;
	int days;

	SetTextColor(hdc,RGB(160, 160, 255));
	TextOut(hdc,rect.left+5,rect.top+2,"INVASION:",9);

	for (int n=0; n < 30; n++)
	{

		SetTextColor(hdc,RGB(255,255,255));
		if (n==0) { wsprintf(text1,"%d - %s",n, "Skeleton King: "); }
		if (n==1) { wsprintf(text1,"%d - %s",n, "Red Dragon: "); }
		if (n==2) { wsprintf(text1,"%d - %s",n, "Golden Dragon: "); }
		if (n==3) { wsprintf(text1,"%d - %s",n, "White Wizard: "); }
		if (n==4) { wsprintf(text1,"%d - %s",n, "New Year: "); }
		if (n==5) { wsprintf(text1,"%d - %s",n, "Rabbits: "); }
		if (n==6) { wsprintf(text1,"%d - %s",n, "Summer: "); }
		if (n==7) { wsprintf(text1,"%d - %s",n, "Cursed Santa: "); }
		if (n==8) { wsprintf(text1,"%d - %s",n, "Medusa: "); }
		if (n==9) { wsprintf(text1,"%d - %s",n, "Custom 1: "); }
		if (n==10){ wsprintf(text1,"%d- %s",n, "Custom 2: "); }
		if (n==11){ wsprintf(text1,"%d- %s",n, "Custom 3: "); }
		if (n==12){ wsprintf(text1,"%d- %s",n, "Custom 4: "); }
		if (n==13){ wsprintf(text1,"%d- %s",n, "Custom 5: "); }
		if (n==14){ wsprintf(text1,"%d- %s",n, "Custom 6: "); }
		if (n==15){ wsprintf(text1,"%d- %s",n, "Custom 7: "); }
		if (n==16){ wsprintf(text1,"%d- %s",n, "Custom 8: "); }
		if (n==17){ wsprintf(text1,"%d- %s",n, "Custom 9: "); }
		if (n==18){ wsprintf(text1,"%d- %s",n, "Custom 10: "); }
		if (n==19){ wsprintf(text1,"%d- %s",n, "Custom 11: "); }
		if (n==20){ wsprintf(text1,"%d- %s",n, "Custom 12: "); }
		if (n==21){ wsprintf(text1,"%d- %s",n, "Custom 13: "); }
		if (n==22){ wsprintf(text1,"%d- %s",n, "Custom 14: "); }
		if (n==23){ wsprintf(text1,"%d- %s",n, "Custom 15: "); }
		if (n==24){ wsprintf(text1,"%d- %s",n, "Custom 16: "); }
		if (n==25){ wsprintf(text1,"%d- %s",n, "Custom 17: "); }
		if (n==26){ wsprintf(text1,"%d- %s",n, "Custom 18: "); }
		if (n==27){ wsprintf(text1,"%d- %s",n, "Custom 19: "); }
		if (n==28){ wsprintf(text1,"%d- %s",n, "Custom 20: "); }
		if (n==29){ wsprintf(text1,"%d- %s",n, "Custom 21: "); }

		if (this->EventInvasion[n] == -1)
		{
			wsprintf(text2, "Disabled");
		}
		else if (this->EventInvasion[n] == 0)
		{
			wsprintf(text2, "Online");
		}
		else
		{
			totalseconds	= this->EventInvasion[n];
			hours			= totalseconds/3600;
			minutes			= (totalseconds/60) % 60;  
			seconds			= totalseconds % 60;

			if (hours > 23)
			{
				days = hours/24;
				wsprintf(text2, "%d day(s)+", days);
			}
			else
			{
				wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
			}
		}
	
		TextOut(hdc,posX1,rect.top+20+(15*n),text1,strlen(text1));
		if (this->EventInvasion[n] == -1)
		{
			SetTextColor(hdc,RGB(250, 50, 50));
		}
		else if (this->EventInvasion[n] == 0)
		{
			SetTextColor(hdc,RGB(0, 255, 0));
		}
		else if (this->EventInvasion[n] < 300)
		{
			SetTextColor(hdc,RGB(255, 255, 0));
		}
		else
		{
			SetTextColor(hdc, RGB(0, 152, 239));
		}
		TextOut(hdc,posX2,rect.top+20+(15*n),text2,strlen(text2));
	}

	SelectObject(hdc,OldFont);
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);
#endif
}



void CServerDisplayer::LogTextPaint() // OK
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	FillRect(hdc,&rect,this->m_brush[3]);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font3);

	int line = MAX_LOG_TEXT_LINE;

	int count = (((this->m_count-1)>=0)?(this->m_count-1):(MAX_LOG_TEXT_LINE-1));

	for(int n=0;n < MAX_LOG_TEXT_LINE;n++)
	{
		switch(this->m_log[count].color)
		{
			case LOG_BLACK:
				SetTextColor(hdc,RGB(255,255,255));
				break;
			case LOG_RED:
				SetTextColor(hdc,RGB(250, 50, 50));
				break;
			case LOG_GREEN:
				SetTextColor(hdc,RGB(0,255,0));
				break;
			case LOG_BLUE:
				SetTextColor(hdc,RGB(0, 152, 239));
				break;
			case LOG_BOT:
				SetTextColor(hdc,RGB(255,0,64));
				break;
			case LOG_USER:
				SetTextColor(hdc,RGB(254,154,46));
				break;
			case LOG_EVENT:
				SetTextColor(hdc,RGB(255,255,255));
				break;
			case LOG_ALERT:
				SetTextColor(hdc,RGB(0, 173, 181));
				break;
		}

		int size = strlen(this->m_log[count].text);

		if(size > 1)
		{
			TextOut(hdc,0,(37+(line*15)),this->m_log[count].text,size);
			line--;
		}

		count = (((--count)>=0)?count:(MAX_LOG_TEXT_LINE-1));
	}

	SelectObject(hdc,OldFont);
	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::LogTextPaintConnect() // OK
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);
#if(GAMESERVER_TYPE==0)
	rect.left	= rect.right - 550;
	rect.right	= rect.right-190;
	rect.top = 445;
	rect.bottom = rect.bottom-20;
#endif

#if(GAMESERVER_TYPE==1)
	rect.left	= rect.right - 550;
	rect.right	= rect.right-5;
	rect.top = 445;
	rect.bottom = rect.bottom-20;
#endif

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font3);

	FillRect(hdc,&rect,this->m_brush[4]);

	SetTextColor(hdc,RGB(160, 160, 255));
	TextOut(hdc,rect.left+5,rect.top+2,"CONNECTION LOG:",15);

	int line = MAX_LOGCONNECT_TEXT_LINE;

	int count = (((this->m_countConnect-1)>=0)?(this->m_countConnect-1):(MAX_LOGCONNECT_TEXT_LINE-1));

	for(int n=0;n < MAX_LOGCONNECT_TEXT_LINE;n++)
	{
		switch(this->m_logConnect[count].color)
		{
			case LOG_BLACK:
				SetTextColor(hdc,RGB(255,255,255));
				break;
			case LOG_RED:
				SetTextColor(hdc,RGB(255,0,0));
				break;
			case LOG_GREEN:
				SetTextColor(hdc,RGB(0,190,0));
				break;
			case LOG_BLUE:
				SetTextColor(hdc,RGB(0,0,255));
				break;
			case LOG_BOT:
				SetTextColor(hdc,RGB(255,0,64));
				SetBkMode(hdc,TRANSPARENT);
				break;
			case LOG_USER:
				SetTextColor(hdc,RGB(254,154,46));
				SetBkMode(hdc,TRANSPARENT);
				break;
			case LOG_EVENT:
				SetTextColor(hdc,RGB(255,255,255));
				SetBkMode(hdc,TRANSPARENT);
				break;
			case LOG_ALERT:
				SetTextColor(hdc,RGB(0, 173, 181));
				SetBkMode(hdc,TRANSPARENT);
				break;
		}

		int size = strlen(this->m_logConnect[count].text);

		if(size > 1)
		{
			TextOut(hdc,rect.left+10,(rect.top+5+(line*15)),this->m_logConnect[count].text,size);
			line--;
		}

		count = (((--count)>=0)?count:(MAX_LOGCONNECT_TEXT_LINE-1));
	}

	SelectObject(hdc,OldFont);
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::LogTextPaintGlobalMessage() // OK
{
	RECT rect;

	GetClientRect(this->m_hwnd, &rect);
#if(GAMESERVER_TYPE==0)
	rect.left	= rect.right - 550;
	rect.right	= rect.right-190;
	rect.top = 295;
	rect.bottom = 440;
#endif

#if(GAMESERVER_TYPE==1)
	rect.left	= rect.right - 550;
	rect.right	= rect.right-5;
	rect.top = 295;
	rect.bottom = 440;
#endif

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc, TRANSPARENT);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font3);

	FillRect(hdc,&rect,this->m_brush[4]);

	SetTextColor(hdc,RGB(160, 160, 255));

	TextOut(hdc,rect.left+5,rect.top+2,"GLOBAL MESSAGE:",15);

	int line = MAX_LOGGLOBAL_TEXT_LINE;

	int count = (((this->m_countGlobal-1)>=0)?(this->m_countGlobal-1):(MAX_LOGGLOBAL_TEXT_LINE-1));

	for(int n=0;n < MAX_LOGGLOBAL_TEXT_LINE;n++)
	{

		SetTextColor(hdc,RGB(0,190,0));

		int size = strlen(this->m_logGlobal[count].text);

		if(size > 1)
		{
			TextOut(hdc,rect.left+10,(rect.top+5+(line*15)),this->m_logGlobal[count].text,size);
			line--;
		}

		count = (((--count)>=0)?count:(MAX_LOGGLOBAL_TEXT_LINE-1));
	}

	SelectObject(hdc,OldFont);
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::LogAddText(eLogColor color,char* text,int size) // OK
{
	PROTECT_START

	size = ((size>=MAX_LOG_TEXT_SIZE)?(MAX_LOG_TEXT_SIZE-1):size);

	memset(&this->m_log[this->m_count].text,0,sizeof(this->m_log[this->m_count].text));

	memcpy(&this->m_log[this->m_count].text,text,size);

	this->m_log[this->m_count].color = color;

	this->m_count = (((++this->m_count)>=MAX_LOG_TEXT_LINE)?0:this->m_count);

	PROTECT_FINAL

	gLog.Output(LOG_GENERAL,"%s",&text[9]);
}

void CServerDisplayer::LogAddTextConnect(eLogColor color,char* text,int size) // OK
{
	PROTECT_START

	size = ((size>=MAX_LOGCONNECT_TEXT_SIZE)?(MAX_LOGCONNECT_TEXT_SIZE-1):size);

	memset(&this->m_logConnect[this->m_countConnect].text,0,sizeof(this->m_logConnect[this->m_countConnect].text));

	memcpy(&this->m_logConnect[this->m_countConnect].text,text,size);

	this->m_logConnect[this->m_countConnect].color = color;

	this->m_countConnect = (((++this->m_countConnect)>=MAX_LOGCONNECT_TEXT_LINE)?0:this->m_countConnect);

	PROTECT_FINAL

	gLog.Output(LOG_GENERAL,"%s",&text[9]);
}

void CServerDisplayer::LogAddTextGlobal(eLogColor color,char* text,int size) // OK
{
	PROTECT_START

	size = ((size>=MAX_LOGGLOBAL_TEXT_SIZE)?(MAX_LOGGLOBAL_TEXT_SIZE-1):size);

	memset(&this->m_logGlobal[this->m_countGlobal].text,0,sizeof(this->m_logGlobal[this->m_countGlobal].text));

	memcpy(&this->m_logGlobal[this->m_countGlobal].text,text,size);

	this->m_logGlobal[this->m_countGlobal].color = color;

	this->m_countGlobal = (((++this->m_countGlobal)>=MAX_LOGGLOBAL_TEXT_LINE)?0:this->m_countGlobal);

	PROTECT_FINAL
}