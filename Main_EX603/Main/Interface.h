#pragma once

#include "stdafx.h"
#include "import.h"
#include "Protocol.h"
#include "NewInterface.h"

#define MAX_OBJECT			500

#define FULL_X_IN_GAME_X(x)		( (MAX_WIN_WIDTH * x) / pWinWidth)
#define FULL_Y_IN_GAME_Y(x)		( (MAX_WIN_HEIGHT * x) / pWinHeight)

#define GET_ITEM(x,y) (((x)*MAX_ITEM_TYPE)+(y))

float TransForX(float num);
float TransForY(float num);
float TransFor2X(float num);
float ReturnX(float num);
float Return2X(float num);
float ReturnY(float num);
bool CheckButtonPressed(int x, int y, int w, int h);
bool CheckButtonPressedRMouse(int x, int y, int w, int h);

enum ObjectID
{
	eFlag01=1,
	eFlag02,
	eFlag03,
	eFlag04,
	eFlag05,
	eFlag06,
	eFlag07,
	eFlag08,
	eFlag09,
	eFlag10,
	eFlag11,
	eFlag12,
	eFlag13,
	eFlag14,
	eFlag15,
	eFlag16,
	eFlag17,
	eFlag18,
	eFlag19,
	eFlag20,
	eFlag21,
	eFlag22,
	eTIME,
	eSAMPLEBUTTON,
	eSAMPLEBUTTON2,
	eLogo,
	eOFFTRADE_JoB,
	eOFFTRADE_JoS,
	eOFFTRADE_JoC,
	eOFFTRADE_WCC,
	eOFFTRADE_WCP,
	eOFFTRADE_WCG,
	eOFFTRADE_OPEN,
	eSTORE_CLOSE,

	eCONFIRM_MAIN,
	eCONFIRM_BTN_OK,
	eCONFIRM_BTN_CANCEL,
	eCONFIRM_TITLE,
	eCONFIRM_FRAME,
	eCONFIRM_FOOTER,
	eCONFIRM_DIV,

	eNextEvent,
	ePrevEvent,

	#if(INFO_EVENTINVASION)
	//
	eINVASION_MAIN,
	eINVASION_MAIN_OPEN,
	eINVASION_CLOSE,
	eINVASION_XACNHAN,
	eINVASION_NextEvent,
	eINVASION_PrevEvent,
	//
	#endif

	eWindowMessageBox,
	eWindowElemental,

	eWAREHOUSE_LEFT,
	eWAREHOUSE_RIGHT,

	eWindowClick,

	eMenu,
	eMenuBG,

	ePLAYER_POINT,


	eSTATSADD_MAIN_STR,
	eSTATSADD_MAIN_AGI,
	eSTATSADD_MAIN_VIT,
	eSTATSADD_MAIN_ENE,
	eSTATSADD_MAIN_CMD,
	eSTATSADD_TITLE,
	eSTATSADD_FRAME,
	eSTATSADD_FOOTER,
	eSTATSADD_DIV,
	eSTATSADD_CLOSE,
	eSTATSADD_TEXTBOX01,
	eSTATSADD_STATBOX01,
	eSTATSADD_STATBOX02,
	eSTATSADD_STATBOX03,
	eSTATSADD_STATBOX04,
	eSTATSADD_STATBOX05,
	eSTATSADD_BTN_OK,

	eMoney1,
	eADVANCE_STAT_INFO,

	eMenu_MAIN,

	eGameOptionsEffectsButton1,
	eGameOptionsEffectsButton2,
	eGameOptionsEffectsButton3,
	eGameOptionsEffectsButton4,
	eGameOptionsEffectsButton5,

	CharacterSelect,
	CharacterSelect_Button1,
	CharacterSelect_Button2,
	CharacterSelect_Button3,
	CharacterSelect_Button4,
	CharacterSelect_Button5,
	//CharacterSelect_Button6,
};

enum ObjType
{
	objButton,
	objSelectBox,
	objTextBox,
	objScrollBar,
};

struct InterfaceObj
{
	int		BgIndex;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	bool	State;
	int		Type;
	int		OpenedValue;
	bool	leftButtonState;
	char	Text[256];
	char	Tooltip[256];
	//int		ScrollValue;

	void set_x(float x)
	{
		if (x < 0)
			x = 0;

		if (x + this->Width > 640.f)
			x = 640.f - this->Width;

		this->X = x;
		this->MaxX = x + this->Width;
	}

	void set_y(float y)
	{
		if (y < 0)
			y = 0;

		if (y + this->Height > 429.f)
			y = 429.f - this->Height;

		this->Y = y;
		this->MaxY = y + this->Height;
	}

	void set_width(float width)
	{
		this->Width = width;
		this->MaxX = this->X + width;
	}

	void set_height(float height)
	{
		this->Height = height;
		this->MaxY = this->Y + height;
	}

	void Open(std::string name)
	{
		this->OnShow = true;
	}

	void Open()
	{
		this->OnShow = true;
		//pSetCursorFocus = true;
	}

	void SetText(char* text)
	{
		strcpy_s(this->Text, text);
	}

	void SetTooltip(char* text)
	{
		strcpy_s(this->Tooltip, text);
	}

	void Open(int Value)
	{
		this->OnShow = true;
		this->OpenedValue = Value;
	}

	void Close(int Value)
	{
		this->OpenedValue = Value;
		this->OnShow = false;
	}

	void Close()
	{
		this->OnShow = false;
		pSetCursorFocus = false;
	}

	void Clear()
	{
		this->Width = 0;
		this->Height = 0;
		this->X = 0;
		this->Y = 0;
		this->MaxX = 0;
		this->MaxY = 0;
		this->OnClick = false;
		this->OnShow = false;
		this->State = false;
		this->Type = 0;
		//this->ScrollValue = 0;
		memset(this->Text, 0, sizeof(this->Text));
		memset(this->Tooltip, 0, sizeof(this->Tooltip));
	}
};

struct InterfaceElement
{
	DWORD	ModelID;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	DWORD	Attribute;
	long	OpenedValue;
	BYTE	Speed;
	char	StatValue[20];
	bool	ByClose;
	bool	FirstLoad;

	void Open()
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->ByClose = false;
		this->FirstLoad = true;
	};

	void Open(int Value, int Speed)
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
		this->FirstLoad = true;
	};

	void Close()
	{
		this->OnShow = false;
		pSetCursorFocus = false;
		this->ByClose = false;
		this->FirstLoad = false;
	};

	void Close(int Value, int Speed)
	{
		this->OnShow = false; pSetCursorFocus = false;
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
	}

	void CloseAnimated(int Speed)
	{
		pSetCursorFocus = false;
		//this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = true;
	}

	bool Check()
	{
		return this->OnShow;
	}
};


class Interface
{
public:

	void		Load();
	static void	LoadImages();
	static void	LoadModels();
	static void	Work();

	InterfaceElement* GetInfo(short ObjectID);

	static void InventoryUpgrade(int a1, int a2, int a3, int a4);

	void * item_post_;
	float PetY;
	float PetX;

	void		BindObject(short ObjectID, DWORD ModelID, float Width, float Height, float X, float Y);
	void		DrawGUI(short ObjectID, float PosX, float PosY);
	void        WindowedModeName();
	void		DrawTimeUI();
	int			DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	void		DrawIMG(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void		ResetDrawIMG(short ObjectID);
	int			DrawMessage(int Mode, LPCSTR Text, ...);
	void		DrawItem(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse);


	bool		CheckWindow(int WindowID);
	int			CloseWindow(int WindowID);
	int			OpenWindow(int WindowID);

	bool		IsWorkZone(short ObjectID);
	bool        IsWorkZone(float X, float Y, float MaxX, float MaxY, bool a5 = false);
	bool		IsWorkZone2(short ObjectID);
	bool		IsWorkZone4(float, float, float, float);
	float		GetResizeX(short ObjectID);
	int			DrawToolTip(int X, int Y, LPCSTR Text, ...);
	float		DrawRepeatGUI(short MonsterID, float X, float Y, int Count);
	void		DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color);
	void		DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);

	void		DrawConfirmOpen();
	bool		EventConfirm_OK(DWORD Event);
	bool		EventConfirm_CANCEL(DWORD Event);

	void		DrawLogo(bool active);
	void		CloseCustomWindow();

	//Mini Map
	bool		MiniMapCheck();
	bool		CombinedChecks();
	bool		CheckMap();

	int			ConfirmSlot;


	static void DrawItemIMG(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse);
	static void DrawItemToolTipText ( void * item, int x, int y );


	void		DrawButtonRender(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);

	#if(MAP_USAGE)
	void DrawTimeUseMap();
	#endif

	void		DrawItem3D(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int ExtOption,int Ancient, bool PickUp, float Scale, bool Center);
	bool		RenderCheckBox(float PosX, float PosY, DWORD TextColor, bool Checkis, LPCSTR Text,...);
	void		DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float ScaleW, float ScaleH, bool ScaleUp); 
	void		DrawFrameAlpha(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float ScaleW, float ScaleH, bool ScaleUp);
	void		NewModelRender3D(float x, float y, float Width, float Height, int ItemID, int Level = 0, int Excl = 0, int Anc = 0, bool OnMouse = 0);

	bool		IsWorkZone5(float X, float Y, float MaxX, float MaxY);
	int			DrawToolTipEx(DWORD Color, int PosX, int PosY, int Width, int Height, int Align, LPCSTR Text, ...);
	void		DrawColoredButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY, DWORD Color);
	bool		gDrawButtonGUI(int IDGUID, float PosX, float PosY, float SizeW, float SizeH, int TypeButton = 0);
	void		DrawBarForm(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void		DrawAnimatedGUI(short ObjectID, float X, float Y);
	// ----
	bool		ControlTextBox(KBDLLHOOKSTRUCT Hook);

	void		DrawColoredAnimatedGUI(short ObjectID, float X, float Y, DWORD Color);
	void		DrawAnimatedButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);

	static void		draw_chat_message(int mode, char* name, char* text);
	bool IsWorkZone7(int Index, int add_points = 0);
	void TextDraw(int PosX, int PosY, int box_width, int Arg5, int Color, int Arg7, int Align, HGDIOBJ Font, LPCTSTR Format, ...);
	void DrawButton7(int Index, float PosX, float PosY, float Width, float Height, MU_4float* Base, MU_4float* OnClick, MU_4float* Hover, LPCTSTR Text = NULL/*, ...*/);
	static void DrawBarForm2(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	

	BYTE m_QuickAdd;

	MU_4float MenuButtonClick;
	MU_4float base;
	MU_4float base_black;
	MU_4float base_color_selected;
	MU_4float base_color_hover;
	char scrollable_buffer[128];
	int scrollable_counter;
	InterfaceObj m_Data[MAX_OBJECT];
	InterfaceElement Data[MAX_OBJECT];
private:
	
};
extern Interface gInterface;

GLvoid GetDrawCircle(int ID, float X, float Y, float W, float CurrenX, float CurrenY, float SetScale, int ScaleSize, int ScalePosicion, float Alpha);