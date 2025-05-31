#pragma once
#include "UITextInputBox.h"
#include "Protocol.h"


#define pNIDrawGUI	((void(__cdecl*)(DWORD ModelID, float PosX, float PosY, float Width, float Height, float SourceX, float SourceY, float ScaleX, float ScaleY, bool Scale, bool Arg11, float Arg12)) 0x637C60)
#define pDrawImage2  ((void(__cdecl*)(int ImageID, int PosX, int PosY, float Width, float Height, int Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, bool ScaleAlpha)) 0x637C60)

#define MAIN_FONT_SIZE 0x081C0380
#define MAIN_RESOLUTION 0x00E8C240
#define MAIN_RESOLUTION_X 0x00E61E58
#define MAIN_RESOLUTION_Y 0x00E61E5C
#define EnableAlphaGL				((void(__cdecl*)(char a1)) 0x00635FD0)
#define sub_41FF80					((int(__thiscall*)(LPVOID This)) 0x0041FF80)
#define sub_401C10					((int(*)())0x401C10)
#define sub_4DB0C0					((double(__cdecl*)(float a1))0x4DB0C0)
#define resizeGuiRate				1.875
#define resizeGuiScaleRateX			(float)*(DWORD*)MAIN_RESOLUTION_X / 800.0f
#define resizeGuiScaleRateY			(float)*(DWORD*)MAIN_RESOLUTION_Y / 600.0f
#define resizeGuiRateX				resizeGuiRate * resizeGuiScaleRateX
#define resizeGuiRateY				resizeGuiRate * resizeGuiScaleRateY
//#define sub_9593B0					((int(__stdcall*)(HDC This, LPCSTR lpMultiByteStr, int, LPSIZE psizl)) 0x9593B0)
#define buffScaleX				1.15f
#define scaleX					1.5f
#define scaleY					1.5f
#define scaleDefault			1.0f
#define defaultScaleX			1.25f
#define defaultScaleY			1.25f
#define sub_635FD0				((void(__cdecl*)(BYTE Mode)) 0x635FD0)
#define sub_635F50				((void(__cdecl*)()) 0x635F50)
#define resizeScaleY			(float)pWinHeight / 600.0f
#define windowsWidth			*(float*)0x00D24E88

#define scale_ratio				1.710526315789474
#define scale_width				scale_ratio / pWinWidthReal
#define scale_height			scale_ratio / pWinHeightReal

#define BUTTON_WIDTH			65
#define BUTTON_HEIGHT			30

#define sub_50B820				((int(__thiscall*)(int This)) 0x50B820)
#define sub_521FE0				((int(__thiscall*)(char *This)) 0x521FE0)
#define sub_521FC0				((int(__thiscall*)(int This)) 0x521FC0)
#define sub_9593B0				((int(__stdcall*)(HDC This, LPCSTR lpMultiByteStr, int, LPSIZE psizl)) 0x9593B0)

#define setPosCenterX(x)       ((GetWindowsX() / 2.f) - (x / 2.f))
#define GetWindowsX()          (WindowWidth2  / g_fScreenRate_x)
#define g_fScreenRate_x        (float)0xE7C3D4
#define WindowWidth2           (GLsizei)0x00E61E58

enum nInterfaceObj
{
	eToolTip_ID = 999999,
};
struct position
{
	float X;
	float Y;
	float Width;
	float Height;
	float Max_X;
	float Max_Y;

	position(float a1 = 0, float a2 = 0, float a3 = 0, float a4 = 0)
	{
		X = a1;
		Y = a2;
		Width = a3;
		Height = a4;
		Max_X = X + Width;
		Max_Y = Y + Height;
	}
};

struct textSize
{
	float	width;
	float	height;
	float	resize_width;
	float	resize_height;
};

struct GUICheckbox
{
	position* pos;
	BYTE state;
	short delay;
	DWORD lastActionTime;

	GUICheckbox(float a1, float a2, float a3, float a4, int a5)
	{
		pos = new position(a1, a2, a3, a4);
		state = 0;
		delay = a5;
		lastActionTime = GetTickCount();
	}
};


struct GUIresource
{
	DWORD	ID;
	float	CellWidth;
	float	CellHeight;
	float	SourceX;
	float	SourceY;
	float	SourceWidth;
	float	SourceHeight;
	float	ScaleX;
	float	ScaleY;
	DWORD	TextColor;
	DWORD	TextBGColor;

	GUIresource(DWORD a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8 = 0, float a9 = 0, DWORD a10 = 0x999999FF, DWORD a11 = 0x0)
	{
		ID = a1;
		CellWidth = a2;
		CellHeight = a3;
		SourceX = a4;
		SourceY = a5;
		SourceWidth = a6;
		SourceHeight = a7;
		ScaleX = a8;
		ScaleY = a9;
		TextColor = a10;
		TextBGColor = a11;
	}
};


struct GUIButton
{
	float X;
	float Y;
	float Width;
	float Height;
	float Max_X;
	float Max_Y;
	bool  clickDown;
	BYTE  state;
	int	  delay;
	DWORD lastActionTime;

	GUIButton()
	{
		clickDown = false;
		state = 0;
		lastActionTime = GetTickCount();
	}

	GUIButton(float a1, float a2, float a3, float a4, int a5)
	{
		clickDown = false;
		state = 0;
		lastActionTime = GetTickCount();
		X = a1;
		Y = a2;
		Width = a3;
		Height = a4;
		Max_X = X + Width;
		Max_Y = Y + Height;
		delay = a5;
		lastActionTime = GetTickCount();
	}
};

struct GUIObj
{
	float X;
	float Y;
	float Default_X;
	float Default_Y;
	float curX;
	float curY;
	float Width;
	float Height;
	float Max_X;
	float Max_Y;
	bool  isFocus;
	bool onShow;
	bool dragging;
	bool allowDrag;
	bool scaleUp;
	BYTE state;
	DWORD lastActionTime;

	GUIObj() {
		onShow = false;
		dragging = false;
		lastActionTime = GetTickCount();
		state = 0;
		isFocus = false;
		allowDrag = false;
		scaleUp = true;
	}

	GUIObj(float a1, float a2, float a3, float a4, bool a5 = false, bool a6 = true) {
		onShow = false;
		dragging = false;
		lastActionTime = GetTickCount();
		state = 0;
		isFocus = false;
		allowDrag = false;
		scaleUp = true;

		X = a1;
		Y = a2;
		Default_X = a1;
		Default_Y = a2;
		Width = a3;
		Height = a4;
		Max_X = X + Width;
		Max_Y = Y + Height;
		allowDrag = a5;
		scaleUp = a6;
	}

};

struct floatInput
{
	bool	selected;
	float	value;
	float	max;
	int		delay;
	DWORD	lastActionTime;

	floatInput()
	{
		selected = false;
		value = 0;
		max = FLT_MAX;
		delay = 150;
		lastActionTime = GetTickCount();
	}
	floatInput(float a1, float a2, int a3)
	{
		selected = false;
		value = a1;
		max = a2;
		delay = a3;
		lastActionTime = GetTickCount();
	}
};

struct uintInput
{
	bool	selected;
	UINT	value;
	UINT	max;
	int		delay;
	DWORD	lastActionTime;

	uintInput()
	{
		selected = false;
		value = 0;
		max = UINT_MAX;
		delay = 150;
		lastActionTime = GetTickCount();
	}
	uintInput(UINT a1, UINT a2, int a3)
	{
		selected = false;
		value = a1;
		max = a2;
		delay = a3;
		lastActionTime = GetTickCount();
	}
};

struct GUItga
{
	DWORD	ID;
	float	CellWidth;
	float	CellHeight;
	float	SourceWidth;
	float	SourceHeight;
	GUItga(DWORD a1, float a2, float a3, float a4, float a5)
	{
		ID = a1;
		CellWidth = a2;
		CellHeight = a3;
		SourceWidth = a4;
		SourceHeight = a5;
	}
};

struct GUIAnimation
{
	position* pos;
	GUItga* Resource;
	BYTE		maxX;
	BYTE		maxY;
	BYTE		step;
	BYTE		maxStep;
	int			delay;
	DWORD		lastActionTime;

	GUIAnimation(GUItga* a1)
	{
		Resource = a1;
		pos = new position();
		step = 0;
		maxStep = 0;
		delay = 0;
		maxX = 0;
		maxY = 0;
		lastActionTime = GetTickCount();
	}
	GUIAnimation(GUItga* a1, float X, float  Y, float  W, float  H, BYTE a6, BYTE a7, BYTE a8, int a9)
	{
		Resource = a1;
		pos = new position(X, Y, W, H);
		step = 0;
		maxStep = a6;
		maxX = a7;
		maxY = a8;
		delay = a9;
		lastActionTime = GetTickCount();
	}
};

struct GUIbutton
{
	GUIButton* data;
	GUIresource* normalFrame;
	GUIresource* hoverFrame;
	GUIresource* clickedFrame;
	GUIresource* disabledFrame;
};


struct CGPACKET_LOCKWINDOW
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD Status;
	DWORD InPass;

};

struct CGPACKET_GETRS
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD Status;
	DWORD StrRS;
	DWORD AgiRS;
	DWORD VitRS;
	DWORD EneRS;
	DWORD CmdRS;
	DWORD Point;
	DWORD Zen;
	DWORD Level;

};

struct CGPACKET_ADDPOINT
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD Status;
	DWORD Str;
	DWORD Agi;
	DWORD Vit;
	DWORD Ene;
	DWORD Cmd;

};

class CNewUIWindowsClient
{
public:
	CNewUIWindowsClient();
	~CNewUIWindowsClient();
	uintInput* bufferUint;
	void		Load();
	float		resizeX(float);
	float		resizeY(float);
	void		DrawGui(DWORD ModelID, float X, float Y, float W, float H, float SourceX = 0, float SourceY = 0, float SourceW = 1024, float SourceH = 512, float ScaleW = 1.5f, float ScaleH = 1.5f, bool ScaleUp = 0);
	//void		DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX = 0, float SourceY = 0, float SourceW = 1024, float SourceH = 512, float ScaleW = 1.5f, float ScaleH = 1.5f, bool ScaleUp = 0);
	void		DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX = 0, float SourceY = 0, float SourceW = 1024, float SourceH = 512, float ScaleW = 1.5f, float ScaleH = 1.5f, bool ScaleUp = 0);
	void		DrawCircle(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float Scale, bool ScaleUp = 0);
	void		DrawToolTipBG(float, float, float, float);
	void		DrawWindowBG(float, float);
	bool		DrawBG(DWORD ModelID, float X, float Y, float W, float H, float rW, float rH, float sX = 0, float sY = 0, float sW = 1024, float sH = 1024);
	bool		DrawWindowBGEX700(GUIObj*, LPCSTR, ...);
	bool		DrawWindowActiveInvasionEX700(GUIObj*, LPCSTR, ...);
	bool		DrawWindowBGPanelEX700(GUIObj*, LPCSTR, ...);
	bool		DrawButton(GUIButton*, LPCSTR, ...);
	bool		DrawButton(GUIButton*, float, float, LPCSTR, ...);
	bool		DrawButton(GUIButton*, float, float, float, float, LPCSTR, ...);
	bool		Drawbutton(GUIbutton*, LPCSTR, ...);
	bool		Drawbutton(GUIbutton*, float, float, LPCSTR, ...);
	bool		DrawCheckbox(GUICheckbox*, LPCSTR, ...);
	bool		DrawCheckbox(GUICheckbox*, float, float, LPCSTR, ...);
	bool		DrawCheckbox(GUICheckbox*, float, float, float, float, LPCSTR, ...);
	bool		DrawAnimation(GUIAnimation*, float = 0, float = 0, float = 0, float = 0);
	void		UpdatePosition(position*, float = 0, float = 0, float = 0, float = 0);
	void		UpdateButton(GUIButton*, float, float, float = 0, float = 0);
	void		DrawInput(float, float, float, float, BYTE, uintInput*, DWORD = 0x000099, DWORD = 0x000055, DWORD = 0xFFFFFFFF);
	bool		IsWorkZone(float, float, float, float);

	char* NumberFormat(int Number);
	const char* NumberFormat(float Number);
	char* NumberFormat(DWORD Number);
	float		CaiDetConMet;
	float		ResizeGuiScaleRateX;
	float		ResizeGuiScaleRateY;
	float		val1;
	float		val2;
	float		val3;
	float		val4;
	textSize	getTextSize(char*);
	void		DrawText(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	void		keyPressed(DWORD a1);
	DWORD		ActiveLockMouse;
	void		RenderCaptchaNumber(float PosX, float PosY, CUITextInputBox* a6, LPCSTR Text, ...);
	bool DrawWindowBG3(GUIObj* gui, LPCSTR Text, int eNumWindow,...);
	bool DrawWindowBG4(GUIObj* gui, LPCSTR Text, int eNumWindow,...);
	bool DrawWindowAlpha(GUIObj* gui, LPCSTR Text, int eNumWindow,...);
	bool DrawWindowOption(GUIObj* gui, LPCSTR Text, int eNumWindow,...);
	bool DrawWindowActiveInvasion(GUIObj* gui, LPCSTR Text, int eNumWindow,...);
	bool		check_Captcha(std::string& captcha, std::string& user_input);
	std::string generateCaptcha(int n);
	std::string vCaptcha;
	static void DrawBarForm(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	bool  BDrawButton(float PosX, float PosY, float SizeButton, float mSizeButtonH, bool IsEnter, LPCSTR Text, ...);
	/*Windows X803*/
	GUIbutton* CloseWindowsUP;
	
	GUIObj* CustomReset;
	GUICheckbox*	ResetTypeNOR;
	#if(JEWELBANKVER2)
	GUIObj* JEWELBANK_WINDOW;
#endif
	GUIObj* ACTIVE_INVASION_WINDOW;
	GUIObj* MENU_WINDOW;
	GUIObj* EVENT_TIME_WINDOW;
	GUIObj* COMMAND_WINDOW;
	GUIObj* BUY_VIP_WINDOW;
	GUIObj* OPTION_WINDOW;
	GUIObj* SKIN_WINDOW;
	GUIObj* FLAG_WINDOW;
	GUIObj* DAILY_REWARD_WINDOW;

	GUIObj* ESCAPE_PANEL;
	GUIObj* MIX_PANEL;

private:

}; extern CNewUIWindowsClient nInterface;
