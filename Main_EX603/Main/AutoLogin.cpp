#include "stdafx.h"
#include "Util.h"
#include "Interface.h"
#include "CustomFont.h"
#include "AutoLogin.h"
#include "SEASON3B.h"
#include "Import.h"
#include "Protect.h"

cAutoLogin AutoLogin;


cAutoLogin::cAutoLogin()
{
}

cAutoLogin::~cAutoLogin()
{
}

float getX(float x) {
	return x / g_fScreenRate_x;
}
float getY(float y) {
	return y / g_fScreenRate_x;
}

bool IsCursorInZone(short x, short y, short x2, short y2) {
	return pCursorX >= x && pCursorX <= x + x2 && pCursorY >= y && pCursorY <= y + y2;
}

bool WriteString(const std::string& name, const std::string& value) {
	HKEY	hKey = NULL;
	DWORD	dwDisp;
	DWORD	dwSize = value.size();

	if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp))
		return false;

	RegSetValueEx(hKey, name.c_str(), 0L, REG_SZ, (CONST BYTE*)value.c_str(), dwSize);
	RegCloseKey(hKey);
	return true;
}

bool WriteDword(const std::string& name, DWORD value) {
	HKEY	hKey = NULL;
	DWORD	dwDisp;
	DWORD	dwSize = sizeof(DWORD);

	if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp))
		return false;

	RegSetValueEx(hKey, name.c_str(), 0L, REG_DWORD, (BYTE*)&value, dwSize);
	RegCloseKey(hKey);
	return true;
}

void DoRequestLogin()
{
	int Struct = _Instance() + 16968;

	InputBox_GetText(*(DWORD*)(Struct + 848), AutoLogin.iUser, 11);
	InputBox_GetText(*(DWORD*)(Struct + 852), AutoLogin.iPassword, 11);
	if (AutoLogin.savePass) {
		WriteString("ID", AutoLogin.iUser);
		WriteString("PW", AutoLogin.iPassword);
		WriteDword("SavePass", 1);
	}
	else {
		WriteDword("SavePass", 0);
	}
	//do it
	RequestLogin(_Instance() + 16968);
}

void CButtonAutoLogin(int This, int a2)
{
	CUIRenderText_SetFont((int)pTextThis(), *(int*)0xE8C594);

	float startX;
	float startY;

	int JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	startX = JCResto + (640.0 - getX(329)) / 2;

	if (pGameResolutionMode == 0)
	{
		startY = Fix_DisplayHeightExt + (480.0 - getY(245)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 1)
	{
		startY = Fix_DisplayHeightExt + (480.0 - getY(245)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 2)
	{
		startY = Fix_DisplayHeightExt + (480.0 - getY(325)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 3)
	{
		startY = Fix_DisplayHeightExt + (480.0 - getY(325)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 4)
	{
		startY = Fix_DisplayHeightExt + (480.0 - getY(375)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 5)
	{
		startY = Fix_DisplayHeightExt + (480.0 - getY(375)) * 2.0 / 3.0; //1440
	}
	else if (pGameResolutionMode == 6)
	{
		startY = Fix_DisplayHeightExt + (480.0 - getY(375)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 7)
	{
		startY = Fix_DisplayHeightExt + (480.0 - getY(375)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 8)
	{
		startY = Fix_DisplayHeightExt + (480.0 - getY(375)) * 2.0 / 3.0;
	}


	int Struct = _Instance() + 16968;

	if (IsCursorInZone(startX + getX(250.0), startY + getY(155), getX(15), getY(15)))
	{
		if (pIsKeyRelease(VK_LBUTTON))
		{
			RenderBitmap(0x7B69, startX + getX(250.0), startY + getY(155), 15.0, 15.0, 0.0, 0.0, 15.0 / 16.0, 15.0 / 32.0, 0, 1, 0.0);
			AutoLogin.savePass = !AutoLogin.savePass;
			PlayBuffer(25, 0, 0);
		}
	}
	if (!AutoLogin.savePass)
	{
		RenderBitmap(0x7B69, startX + getX(250.0), startY + getY(155), 15.0, 15.0, 0.0, 15.0 / 32.0, 15.0 / 16.0, 15.0 / 32.0, 0, 1, 0.0);
	}
	else
	{
		RenderBitmap(0x7B69, startX + getX(250.0), startY + getY(155), 15.0, 15.0, 0.0, 0.0, 15.0 / 16.0, 15.0 / 32.0, 0, 1, 0.0);
	}

	CustomFont.Draw((HFONT)pFontNormal, startX + getX(110), startY + getY(158), 0xffffffD1, 0x0, getX(140), 0, 4, GlobalText(GlobalLine, 3842)); //Save Account/Password
}


void DoLoginWinCreate(int)
{
	int Struct = _Instance() + 16968;
	LoginWinCreate(Struct);
	if (AutoLogin.savePass) {
		InputBox_SetText(*(DWORD*)(Struct + 848), AutoLogin.iUser);
		InputBox_SetText(*(DWORD*)(Struct + 852), AutoLogin.iPassword);
	}
}

void cAutoLogin::Load()
{
	//read data
	HKEY hKey;
	DWORD dwDisp;
	DWORD dwSize;
	if (ERROR_SUCCESS == RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp))
	{
		dwSize = 11;
		if (RegQueryValueEx(hKey, "ID", 0, NULL, (LPBYTE)AutoLogin.iUser, &dwSize) != ERROR_SUCCESS)
		{
			ZeroMemory(AutoLogin.iUser, sizeof(AutoLogin.iUser));
		}
		dwSize = 11;
		if (RegQueryValueEx(hKey, "PW", 0, NULL, (LPBYTE)AutoLogin.iPassword, &dwSize) != ERROR_SUCCESS)
		{
			ZeroMemory(AutoLogin.iPassword, sizeof(AutoLogin.iPassword));
		}
		dwSize = sizeof(int);
		if (RegQueryValueEx(hKey, "SavePass", 0, NULL, (LPBYTE)&AutoLogin.savePass, &dwSize) != ERROR_SUCCESS)
		{
			AutoLogin.savePass = false;
		}
	}

	//end

	SetCompleteHook(0xE8, 0x0040B5A9, &CButtonAutoLogin);
	SetCompleteHook(0xE8, 0x0040B400, &DoRequestLogin);
	SetCompleteHook(0xE8, 0x0040B44F, &DoRequestLogin);
	SetCompleteHook(0xE8, 0x00483711, &DoLoginWinCreate);
}
