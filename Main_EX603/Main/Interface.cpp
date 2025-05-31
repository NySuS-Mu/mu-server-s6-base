#include "stdafx.h"
#include "Common.h"
#include "CustomPing.h"
#include "Interface.h"
#include "Import.h"
#include "Reconnect.h"
#include "TMemory.h"
#include "Defines.h"
#include "OffTrade.h"
#include "Protect.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "User.h"
#include "Util.h"
#include "Offset.h"
#include "EventInvasion.h"
#include "InterfaceElemental.h"
#include "CustomFont.h"
#include "SEASON3B.h"
#include "Warehouse.h"
#include "Item.h"
#include "MiniMap.h"
#include "CTimCheck.h"
#include "PKNotice.h"
#include "NPCRuud.h"
#include "CustomStatsAdvance.h"
#include "CustomQuickAddStats.h"
#include "CustomInterface.h"
#include "ShowInfoItemDrop.h"

Interface	gInterface;

float TransForX(float num)
{
	return (float) ( pWinWidthReal <= 1.25 ) ? num * pWinWidthReal : num * pWinHeightReal;
}

float TransForY(float num)
{
	return (float) num * pWinHeightReal;
}

float TransFor2X(float num)
{
	return (float) num * pWinWidthReal;
}

float ReturnX(float num)
{
	return (float) ( pWinWidthReal <= 1.25 ) ? num / pWinWidthReal : num / pWinHeightReal;
}

float Return2X(float num)
{
	return (float) num / pWinWidthReal;
}

float ReturnY(float num)
{
	return (float) num / pWinHeightReal;
}

bool CheckButtonPressed(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, w, h) && *(BYTE*)0x8793386;
}

bool CheckButtonPressedRMouse(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, w, h) && pIsKeyRelease(VK_MBUTTON);
}

void Interface::Load()
{
	
	if (gProtect.m_MainInfo.DisableAdvance == 0)
	{
		gInterface.BindObject(eADVANCE_STAT_INFO, 561020, 35, 30, -1, -1);
	}

	this->BindObject(eTIME, 0x787F, 131, 70, -1, -1);
	this->BindObject(eFlag01, 0x7880, 78, 78, -1, -1);
	this->BindObject(eFlag02, 0x7881, 78, 78, -1, -1);
	this->BindObject(eFlag03, 0x7882, 78, 78, -1, -1);
	this->BindObject(eFlag04, 0x7883, 78, 78, -1, -1);
	this->BindObject(eFlag05, 0x7884, 78, 78, -1, -1);
	this->BindObject(eFlag06, 0x7885, 78, 78, -1, -1);
	this->BindObject(eFlag07, 0x7886, 78, 78, -1, -1);
	this->BindObject(eFlag08, 0x7887, 78, 78, -1, -1);
	this->BindObject(eFlag09, 0x7888, 78, 78, -1, -1);
	this->BindObject(eFlag10, 0x7889, 78, 78, -1, -1);
	this->BindObject(eFlag11, 0x7890, 78, 78, -1, -1);
	this->BindObject(eFlag12, 0x7891, 78, 78, -1, -1);
	this->BindObject(eFlag13, 0x7892, 78, 78, -1, -1);
	this->BindObject(eFlag14, 0x7893, 78, 78, -1, -1);
	this->BindObject(eFlag15, 0x7894, 78, 78, -1, -1);
	this->BindObject(eFlag16, 0x7895, 78, 78, -1, -1);
	this->BindObject(eFlag17, 0x7896, 78, 78, -1, -1);
	this->BindObject(eFlag18, 0x7897, 78, 78, -1, -1);
	this->BindObject(eFlag19, 0x7898, 78, 78, -1, -1);
	this->BindObject(eFlag20, 0x7899, 78, 78, -1, -1);
	this->BindObject(eFlag21, 0x7900, 78, 78, -1, -1);
	this->BindObject(eFlag22, 0x7901, 78, 78, -1, -1);
	this->BindObject(eSAMPLEBUTTON, 0x7903, 25, 40, -1, -1);
	this->BindObject(eSAMPLEBUTTON2, 0x7904, 25, 40, -1, -1);

	this->BindObject(eCONFIRM_MAIN, 0x7A5A, 222, 120, -1, -1);
	this->BindObject(eCONFIRM_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eCONFIRM_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eCONFIRM_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eCONFIRM_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eCONFIRM_BTN_OK, 0x7A5B, 54, 30, -1, -1);
	this->BindObject(eCONFIRM_BTN_CANCEL, 0x7A5C, 54, 30, -1, -1);

	this->BindObject(eLogo, 0x7905, 150, 114, -1, -1);

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		this->BindObject(eOFFTRADE_JoB, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_JoS, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_JoC, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_WCC, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_WCP, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_WCG, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_OPEN, 51522, 108, 30, -1, -1);
		this->BindObject(eSTORE_CLOSE, 51522, 108, 30, -1, -1);
	}
	else
	{
		//Custom Store
		this->BindObject(eOFFTRADE_JoB, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_JoS, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_JoC, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_WCC, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_WCP, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_WCG, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_OPEN, 0x7BFD, 108, 30, -1, -1);
		this->BindObject(eSTORE_CLOSE, 0x7BFD, 108, 30, -1, -1);
	}

	

	this->BindObject(eNextEvent, 0x7903, 25, 40, -1, -1);
	this->BindObject(ePrevEvent, 0x7904, 25, 40, -1, -1);

	this->BindObject(eWAREHOUSE_LEFT, 32345, 22, 20, -1, -1);
	this->BindObject(eWAREHOUSE_RIGHT, 32346, 22, 20, -1, -1);

	this->BindObject(eSTATSADD_TEXTBOX01, 0x9307, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX01, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX02, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX03, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX04, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX05, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_BTN_OK, 0x7A5B, 54, 30, -1, -1);

	if (gProtect.m_MainInfo.InventoryUpgrade == 1)
	{
		this->BindObject(eMoney1, 0x99090, 170, 26, -1, -1);
	}

	if (gProtect.m_MainInfo.InventoryUpgrade == 1)
	{
		SetRange((LPVOID)0x00835116, 5, ASM::NOP);
		SetOp((LPVOID)0x00835116, this->InventoryUpgrade, ASM::CALL);
	}


	SetOp((LPVOID)oLoadSomeForm_Call, this->LoadImages, ASM::CALL);

	SetOp((LPVOID)oDrawInterface_Call, this->Work, ASM::CALL);

	SetCompleteHook(0xFF, 0x00633FFB, &this->LoadModels);

	//==========================================
	// - Remove Texts PShop
	//==========================================
	SetRange((LPVOID)0x00842086, 5, ASM::NOP);
	SetRange((LPVOID)0x0084234F, 5, ASM::NOP);
	SetRange((LPVOID)0x008423C3, 5, ASM::NOP);

	this->item_post_ = nullptr;

	#if(INFO_EVENTINVASION)
	gEventInvasion.BinObeject();
	#endif
}

InterfaceElement* Interface::GetInfo(short ObjectID)
{
	return &this->Data[ObjectID];
}


void Interface::LoadModels()
{
	pLoadModel(406, "Data\\Custom\\Bmd\\VIP1\\", "musign", -1);
	pLoadTexture(406, "Custom\\Bmd\\VIP1\\", 0x2901, 0x2600, 1);
	pLoadModel(407, "Data\\Custom\\Bmd\\VIP2\\", "musign", -1);
	pLoadTexture(407, "Custom\\Bmd\\VIP2\\", 0x2901, 0x2600, 1);
	pLoadModel(408, "Data\\Custom\\Bmd\\VIP3\\", "musign", -1);
	pLoadTexture(408, "Custom\\Bmd\\VIP3\\", 0x2901, 0x2600, 1);

	// ----
	pInitModelData2();
}

void Interface::LoadImages()
{
	
	if (gProtect.m_MainInfo.InventoryUpgrade == 1)
	{
		pLoadImage("Custom\\Interface\\item_money.tga", 0x99090, GL_LINEAR, GL_CLAMP, 1, 0);
	}

	LoadBitmapA("Interface\\newui_number1.tga", 31337, 9729, 10496, 1, 0);

	pLoadImage("Custom\\Interface\\TimeBar.tga", 0x787F, 0x2601, 0x2901, 1, 0);

	pLoadImage("Custom\\Interface\\Rank01.tga", 0x7880, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank02.tga", 0x7881, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank03.tga", 0x7882, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank04.tga", 0x7883, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank05.tga", 0x7884, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank06.tga", 0x7885, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank07.tga", 0x7886, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank08.tga", 0x7887, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank09.tga", 0x7888, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank10.tga", 0x7889, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank11.tga", 0x7890, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank12.tga", 0x7891, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank13.tga", 0x7892, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank14.tga", 0x7893, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank15.tga", 0x7894, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank16.tga", 0x7895, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank17.tga", 0x7896, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank18.tga", 0x7897, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank19.tga", 0x7898, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank20.tga", 0x7899, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank21.tga", 0x7900, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank22.tga", 0x7901, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Next.tga", 0x7903, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Previous.tga", 0x7904, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\MU-logo.tga", 0x7905, 0x2601, 0x2901, 1, 0);

	pLoadImage("Custom\\Interface\\Button.tga", 0x7908, 0x2601, 0x2900,1,0);

#if(REGISTER_ACCOUNT)
	LoadBitmapA("Custom\\Interface\\CustomRegister\\login_back.tga", 71631, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Custom\\Interface\\CustomRegister\\newui_btn_empty_very_small2.tga", 71619, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Custom\\Interface\\CustomRegister\\newui_button_register.tga", 71620, GL_LINEAR, GL_CLAMP, 1, 0);
#endif
	pLoadImage("Custom\\Interface\\none.tga", 31461, 0x2601, 0x2900, 1, 0);

	pLoadImage("Logo\\Mu-logo.tga", 531018, GL_LINEAR, GL_REPEAT, 1, 0);
	pLoadImage("Logo\\Mu-logo_g.jpg", 531019, GL_LINEAR, GL_REPEAT, 1, 0);

	pLoadImage("Custom\\Maps\\mini_map_ui_party.tga", 61520, 0x2601, 0x2901, 1, 0);

	pLoadImage("Custom\\Interface\\Title.tga", 0x8916, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\InfoBlock.tga", 0x8917, 0x2601, 0x2900, 1, 0);

	LoadBitmapA("Custom\\Interface\\GFx\\Render_buttom_1.tga", 71521, 0x2601, 0x2901, 1, 0);
	LoadBitmapA("Custom\\Interface\\GFx\\InventoryFrame_RuudShop.tga", 61560, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Custom\\Interface\\GFx\\Menu_RuudShopFrame.tga", 61561, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Custom\\Interface\\GFx\\Menu_Button03.tga", 61562, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Custom\\Interface\\GFx\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);

	switch (gProtect.m_MainInfo.CustomInterfaceType)
	{
	case Classic:
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\Decor.tga", 87968, 0x2601, 0x2900, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\InterfaceBar.tga", 87969, 0x2601, 0x2900, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\Main_Skillbox.tga", 51500, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\newui_skillbox2.jpg", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\item_pbtnbg.tga", 61547, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\skill_render.tga", 61546, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\popup_line_s.tga", 71520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
		break;
	case Ex700:
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Main_Skillbox.tga", 51500, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\newui_skillbox2.jpg", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\item_pbtnbg.tga", 61547, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\skill_render.tga", 61546, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\popup_line_s.tga", 71520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
		//--
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Main_IE.tga", 31293, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Main_IE_Exp.tga", 59000, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Main_I1.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Main_I4.jpg", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Main_I5.jpg", 31299, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\newui_skillbox2.tga", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\newui_skillbox.tga", 31312, GL_LINEAR, GL_CLAMP, 1, 0);
		//-- Atributos de personaje
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\guege_mp.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\guege_mp_1.tga", 51501, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\guege_hp_green.tga", 31297, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\guege_hp.tga", 31298, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\guege_hp_1.tga", 51502, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Main_IE_Buttons.tga", 0x901, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_scrollbar_buttom_up.tga", 51552, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_scrollbar_buttom_down.tga", 51551, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\chat_bg03.tga", 51545, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_scrollbar_up.tga", 31270, 9729, 10496, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_scrollbar_m.tga", 31271, 9729, 10496, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_scrollbar_down.tga", 31272, 9729, 10496, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_Scrollbar_stretch.tga", 31275, 9729, 10496, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_Main01.tga", 51529, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_Main02.tga", 51541, GL_LINEAR, GL_CLAMP, 1, 0);
		for (int i = 51530; i < 51534; ++i) {
			LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_Button.tga", i, GL_LINEAR, GL_CLAMP, 1, 0);
		}
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonWBack.tga", 51538, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonSize.tga", 51539, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonTransparencyA.tga", 51540, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonHide01.tga", 51542, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonHide02.tga", 51543, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonHide03.tga", 51544, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\chat_bg01.tga", 61550, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\chat_bg02.tga", 61551, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\chat_bg03.tga", 61534, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_I5.tga", 61548, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_chat_back.tga", 61549, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\RuudShop\\Render_buttom_1.tga", 71521, 0x2601, 0x2901, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\RuudShop\\InventoryFrame_RuudShop.tga", 61560, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\RuudShop\\Menu_RuudShopFrame.tga", 61561, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\RuudShop\\Menu_Button03.tga", 61562, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\RuudShop\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);

		//AdvancedUI
		// 
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\InventoryFrame_I1.tga", 61522, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\InventoryFrame_I2.tga", 61523, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\InventoryFrame_I3.tga", 61524, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\Frame_I3.tga", 61526, GL_LINEAR, GL_CLAMP, 1, 0); //-- All Window
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\InventoryFrame_I4.tga", 61527, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\Draw_money.tga", 61528, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\button_close.tga", 61529, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\CharacterInfoFrame_I1.tga", 61532, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\newui_chainfo_btn_level.tga", 61533, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\ButtonCharacterInfo.tga", 61535, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\CharacterInfoFrame_I2.tga", 61538, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\BaulFrame_I1.tga", 61539, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\BaulFrame_I2.tga", 61540, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\ShopFrame_I1.tga", 61541, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\ShopFrame_I2.tga", 61543, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\StoreFrame_I1.tga", 61544, GL_LINEAR, GL_CLAMP, 1, 0);

		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\Render_buttom_3.tga", 71524, 0x2601, 0x2901, 1, 0); //esquina abajo derecha

		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\UI\\winPet_I1.tga", 61545, GL_LINEAR, GL_CLAMP, 1, 0);

		//-- Botones del Main
		pLoadImage("Custom\\Interface\\none.tga", 31461, 0x2601, 0x2900, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31303, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31304, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31305, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31306, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31307, GL_LINEAR, GL_CLAMP, 1, 0);
		
		LoadBitmapA("Custom\\Interface\\none.tga", 51522, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31294, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31295, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31292, GL_LINEAR, GL_CLAMP, 1, 0);

		//-- Folder MacroUI
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_Main.tga", 51550, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_BSetup.tga", 51546, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_BStart.tga", 51547, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_Stop.tga", 51548, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_Bar.jpg", 51549, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_Menu.tga", 120111, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Party\\PartyFrame_I3.tga", 81525, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_hpbar.tga", 81526, 0x2601, 0x2901, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_mpbar.tga", 81527, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_crown.tga", 81528, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_bg.tga", 81529, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_xbtn01_1.tga", 81530, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_bg01.tga", 81531, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_xbtn02_1.tga", 81532, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		break;
	}

	if (gProtect.m_MainInfo.ItemTooltipUpgrade == 1)
	{
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg01.tga", 61511, 0x2601, 0x2901, 1, 0); //esquina arriba izquierda
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg02.tga", 61512, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg03.tga", 61513, 0x2601, 0x2901, 1, 0); //esquina arriba derecha
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg04.tga", 61514, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg06.tga", 61515, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg07.tga", 61516, 0x2601, 0x2901, 1, 0); //esquina abajo izquierda
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg08.tga", 61517, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg09.tga", 61518, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	}

	if(gProtect.m_MainInfo.DisableCustomCloack == 0)
	{
		gCloak.LoadTexture();
	}

	nInterface.Load();

	// ----
	pLoadSomeForm();
}

void Interface::BindObject(short MonsterID, DWORD ModelID, float Width, float Height, float X, float Y)
{
	this->Data[MonsterID].EventTick	= 0;
	this->Data[MonsterID].OnClick	= false;
	this->Data[MonsterID].OnShow	= false;
	this->Data[MonsterID].ModelID	= ModelID;
	this->Data[MonsterID].Width		= Width;
	this->Data[MonsterID].Height	= Height;
	this->Data[MonsterID].X			= X;
	this->Data[MonsterID].Y			= Y;
	this->Data[MonsterID].MaxX		= X + Width;
	this->Data[MonsterID].MaxY		= Y + Height;
	this->Data[MonsterID].Attribute	= 0;
}

void Interface::DrawGUI(short ObjectID, float PosX, float PosY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= PosX;
		this->Data[ObjectID].Y		= PosY;
		this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	}

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawIMG(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= PosX;
		this->Data[ObjectID].Y		= PosY;
		this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	}

	pDrawImage(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height,0,0,ScaleX,ScaleY,1,1,0);
}

void Interface::ResetDrawIMG(short ObjectID)
{
	if( this->Data[ObjectID].X != -1 || this->Data[ObjectID].Y != -1 )
	{
		this->Data[ObjectID].X		= -1;
		this->Data[ObjectID].Y		= -1;
		this->Data[ObjectID].MaxX	= -1;
		this->Data[ObjectID].MaxY	= -1;
	}
}


void Interface::Work()
{
	gObjUser.Refresh();
	gInterface.DrawTimeUI();
	ReconnectMainProc();
	gInterface.DrawConfirmOpen();
	gWarehouse.ButtonsDraw();

	gQuickAddStats.Draw();
	gQuickAddStats.DrawStatsAddWindow_STR();
	gQuickAddStats.DrawStatsAddWindow_AGI();
	gQuickAddStats.DrawStatsAddWindow_VIT();
	gQuickAddStats.DrawStatsAddWindow_ENE();
	gQuickAddStats.DrawStatsAddWindow_CMD();

	gRenderMap.AutoSendMove();

	if(gProtect.m_MainInfo.ShowInfoWindowedMode)
	{
		gInterface.WindowedModeName();
	}

	if(DisablePing == 0)
	{
		gCustomPing.ShowPing();
	}

	 if(pPlayerState == 5)
	 {
		gCustomPing.StartPing();
	 }

	#if(INFO_EVENTINVASION)
	if(gProtect.m_MainInfo.ActiveInvasion == 1)
	{
		gEventInvasion.OpenMain();
		gEventInvasion.Draw();
	}
	#endif


	#if(MAP_USAGE)
	gInterface.DrawTimeUseMap();
	#endif

	gPKNotice.DrawNoticePKSystem();

	if (GetKeyState(VK_SNAPSHOT) < 0) 
	{
		gInterface.DrawLogo(1); 
	}

	if (gElemental.LockMouse != 0)
	{
		if (gElemental.LockMouse > GetTickCount())
		{
			pSetCursorFocus = true;
		}
		else
		{
			gElemental.LockMouse = 0;
			pSetCursorFocus = false;
		}
	}
	if (nInterface.ActiveLockMouse != 0)
	{
		if (nInterface.ActiveLockMouse > GetTickCount())
		{
			pSetCursorFocus = true;
		}
		else
		{
			nInterface.ActiveLockMouse = 0;
			pSetCursorFocus = false;
		}
	}

	jCRenderRuud.CheckOpen();

	if (gProtect.m_MainInfo.DisableAdvance == 0)
	{
		g_StatsAdvance.DrawInfo();
	}

	gInterface.DrawLogo(0);
	
	pDrawInterface();
}

void Interface::InventoryUpgrade(int a1, int a2, int a3, int a4)
{
	int v10;
	int v11;
	DWORD v23;
	v10 = *(DWORD*)(a1 + 40);
	v11 = *(DWORD*)(a1 + 36);
	v23 = *(DWORD*)(*(DWORD*)0x8128AC4 + 5956);

	char MoneyBuff1[256], MoneyBuff2[256];
	ZeroMemory(MoneyBuff1, sizeof(MoneyBuff1));
	ZeroMemory(MoneyBuff2, sizeof(MoneyBuff2));

	pGetMoneyFormat(v23, MoneyBuff1, 0);
	pGetMoneyFormat(Ruud, MoneyBuff2, 0);

	DWORD Color = eWhite;
	DWORD Color2 = eWhite;;

	if (v23 >= 0 && v23 <= 99999)
	{
		Color = eWhite;
	}
	else if (v23 >= 100000 && v23 <= 999999)
	{
		Color = eShinyGreen;
	}
	else if (v23 >= 1000000 && v23 <= 9999999)
	{
		Color = eGold;
	}
	else if (v23 >= 10000000 && v23 <= 99999999)
	{
		Color = eOrange;
	}
	else if (v23 >= 100000000 && v23 <= 2000000000)
	{
		Color = eRed;
	}

	if (Ruud >= 0 && Ruud <= 99999)
	{
		Color2 = eWhite;
	}
	else if (Ruud >= 100000 && Ruud <= 999999)
	{
		Color2 = eShinyGreen;
	}
	else if (Ruud >= 1000000 && Ruud <= 9999999)
	{
		Color2 = eGold;
	}
	else if (Ruud >= 10000000 && Ruud <= 99999999)
	{
		Color2 = eOrange;
	}
	else if (Ruud >= 100000000 && Ruud <= 2000000000)
	{
		Color2 = eRed;
	}

	//--
	gInterface.DrawGUI(eMoney1, v11+10, v10 + 364);
	
	CustomFont.Draw((HFONT)pFontNormal, v11 + 48, v10 + 371, Color, 0x0, 50, 0, 1, "%s", MoneyBuff1);

	CustomFont.Draw((HFONT)pFontNormal, v11 + 120, v10 + 371, Color2, 0x0, 50, 0, 1, "%s", MoneyBuff2);

}

void Interface::WindowedModeName()
{		
	char interaltas[600];

	DWORD elapsed2 = GetTickCount()-gCustomPing.TickCount2;

    gCustomPing.m_fpscount2++;

    // one second elapsed? (= 1000 milliseconds)
    if (elapsed2 > 1000)
    {
		// save the current counter value to m_fps
		gCustomPing.m_fps2 = gCustomPing.m_fpscount2;
		// reset the counter and the interval
		gCustomPing.m_fpscount2 = 0;
		// set tick count
		gCustomPing.TickCount2 = GetTickCount();
    }

	time_t TimeServer;
	struct tm * ServerT;
	time(&TimeServer);
	ServerT = gmtime(&TimeServer);

	if(gProtect.m_MainInfo.ShowInfoWindowedModeType == 1)
	{
		sprintf_s(interaltas, sizeof(interaltas), "%s [Player: %s] [Ping: %dms] [FPS: %d] [Server Time: %2d:%02d:%02d]", gProtect.m_MainInfo.WindowName, gObjUser.lpPlayer->Name,gCustomPing.PingDelayRecv,gCustomPing.m_fps2,(ServerT->tm_hour + GMT) % 24, ServerT->tm_min, ServerT->tm_sec);
	}
	else if (gProtect.m_MainInfo.ShowInfoWindowedModeType == 2)
	{
		sprintf_s(interaltas, sizeof(interaltas), "%s [Player: %s] [Ping: %dms] [FPS: %d]", gProtect.m_MainInfo.WindowName, gObjUser.lpPlayer->Name,gCustomPing.PingDelayRecv,gCustomPing.m_fps2);
	}
	else if (gProtect.m_MainInfo.ShowInfoWindowedModeType == 3)
	{
		sprintf_s(interaltas, sizeof(interaltas), "%s [Player: %s] [Server Time: %2d:%02d:%02d]", gProtect.m_MainInfo.WindowName, gObjUser.lpPlayer->Name,(ServerT->tm_hour + GMT) % 24, ServerT->tm_min, ServerT->tm_sec);
	}
	else if (gProtect.m_MainInfo.ShowInfoWindowedModeType == 4)
	{
		sprintf_s(interaltas, sizeof(interaltas), "%s [Player: %s]", gProtect.m_MainInfo.WindowName, gObjUser.lpPlayer->Name);
	}

	SetWindowText(pGameWindow, interaltas);
	
}

void Interface::DrawTimeUI()
{
	if (!TimerBar)
	{
		return;
	}

	if (this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::FullMap) || this->CheckWindow(ObjWindow::ChatWindow) || this->CheckWindow(ObjWindow::SkillTree)
		|| this->CheckWindow(ObjWindow::MoveList))
	{
		return;
	}
	// -----
	time_t TimeServer, TimeLocal;
	struct tm * ServerT, *LocalT;
	time(&TimeServer);
	time(&TimeLocal);
	// ----
	ServerT = gmtime(&TimeServer);
	char ServerTimeName[25] = "Server:";
	char ServerTime[30];
	sprintf(ServerTime, "%2d:%02d:%02d", (ServerT->tm_hour + GMT) % 24, ServerT->tm_min, ServerT->tm_sec);

	LocalT = localtime(&TimeLocal);
	char LocalTimeName[25] = "Local:";
	char LocalTime[30];
	sprintf(LocalTime, "%2d:%02d:%02d", LocalT->tm_hour, LocalT->tm_min, LocalT->tm_sec);

	this->DrawGUI(eTIME, -10, 360);
	this->DrawFormat(eGold, 5, 390, 0, 1, ServerTimeName);
	this->DrawFormat(eWhite, 45, 390, 50, 1, ServerTime);
	this->DrawGUI(eTIME, -10, 380);
	this->DrawFormat(eGold, 5, 412, 0, 1, LocalTimeName);
	this->DrawFormat(eWhite, 45, 412, 50, 1, LocalTime);

}

int Interface::DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	int LineCount = 0;
	
	char * Line = strtok(Buff, "\n");
	
	while( Line != NULL )
	{
		pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
	
	return PosY;
}

bool Interface::CheckWindow(int WindowID)
{
	return pCheckWindow(pWindowThis(), WindowID);
}
int Interface::CloseWindow(int WindowID)
{
	return pCloseWindow(pWindowThis(), WindowID);
}
int Interface::OpenWindow(int WindowID)
{
	return pOpenWindow(pWindowThis(), WindowID);
}

bool Interface::IsWorkZone(short ObjectID)
{
	if( (gObjUser.m_CursorX < this->Data[ObjectID].X || gObjUser.m_CursorX > this->Data[ObjectID].MaxX) || (gObjUser.m_CursorY < this->Data[ObjectID].Y || gObjUser.m_CursorY > this->Data[ObjectID].MaxY) )
		return false;

	return true;
}

bool Interface::IsWorkZone(float X, float Y, float MaxX, float MaxY, bool a5)
{
	if (a5)
	{
		if ((pCursorX < X || pCursorX > X + MaxX) || (pCursorY < Y || pCursorY > Y + MaxY))
			return false;
		return true;
	}
	if ((pCursorX < X || pCursorX > MaxX) || (pCursorY < Y || pCursorY > MaxY))
		return false;
	return true;
}

bool Interface::IsWorkZone2(short ObjectID)
{
	float PosX = this->Data[ObjectID].X;
	float MaxX = PosX + this->Data[ObjectID].Width;

	if (((float)pCursorX < PosX || (float)pCursorX > MaxX) || ((float)pCursorY < this->Data[ObjectID].Y || (float)pCursorY > this->Data[ObjectID].MaxY))
	{
		return false;
	}

	return true;
}

bool Interface::IsWorkZone4(float x, float y, float x2, float y2)
{
	bool result = GetForegroundWindow() == pGameWindow && pCursorX >= x && pCursorX <= x + x2 && pCursorY >= y && pCursorY <= y + y2;
	return result;
}

float Interface::GetResizeX(short ObjectID)
{
	if( pWinWidth == 800 )
	{
		return this->Data[ObjectID].X + 16.0;
	}
	else if( pWinWidth != 1024 )
	{
		return this->Data[ObjectID].X - 16.0;
	}
	
	return this->Data[ObjectID].X;
}

int Interface::DrawToolTip(int X, int Y, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	return pDrawToolTip(X, Y, Buff);
}

int Interface::DrawMessage(int Mode, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	return pDrawMessage(Buff, Mode);
}


float Interface::DrawRepeatGUI(short MonsterID, float X, float Y, int Count)
{
	float StartY = Y;
	// ----
	for( int i = 0; i < Count; i++ )
	{
		pDrawGUI(this->Data[MonsterID].ModelID, X, StartY,
			this->Data[MonsterID].Width, this->Data[MonsterID].Height);
		// ----
		StartY += this->Data[MonsterID].Height;
	}
	// ----
	return StartY;
}

void Interface::DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}


void Interface::DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= X;
		this->Data[ObjectID].Y		= Y;
		this->Data[ObjectID].MaxX	= X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= Y + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y, 
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawLogo(bool active)
{
	if (gProtect.m_MainInfo.PrintLogo != 0)
	{
		if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			if (active == 1)
			{
				this->Data[eLogo].EventTick = GetTickCount() + 1500;
			}

			if (gInterface.Data[eLogo].EventTick > GetTickCount())
			{
				if (gProtect.m_MainInfo.PrintLogo == 1)
				{
					this->DrawGUI(eLogo, 10, 10);
				}

				if (gProtect.m_MainInfo.PrintLogo == 2)
				{
					this->DrawGUI(eLogo, MAX_WIN_WIDTH - 160, 10);

				}

				if (gProtect.m_MainInfo.PrintLogo == 3)
				{
					this->DrawGUI(eLogo, 10, MAX_WIN_HEIGHT - 144);
				}

				if (gProtect.m_MainInfo.PrintLogo == 4)
				{
					this->DrawGUI(eLogo, MAX_WIN_WIDTH - 160, MAX_WIN_HEIGHT - 144);
				}

				if (gProtect.m_MainInfo.PrintLogo == 5)
				{
					this->DrawGUI(eLogo, (MAX_WIN_WIDTH / 2) - (150 / 2), (MAX_WIN_HEIGHT / 2) - (114 / 2));
				}
			}
		}
		else
		{
			if (active == 1)
			{
				this->Data[eLogo].EventTick = GetTickCount() + 1500;
			}

			if (gInterface.Data[eLogo].EventTick > GetTickCount())
			{
				if (gProtect.m_MainInfo.PrintLogo == 1)
				{
					this->DrawGUI(eLogo, 10, 10);
				}

				if (gProtect.m_MainInfo.PrintLogo == 2)
				{
					this->DrawGUI(eLogo, 640 - 160, 10);

				}

				if (gProtect.m_MainInfo.PrintLogo == 3)
				{
					this->DrawGUI(eLogo, 10, 480 - 144);
				}

				if (gProtect.m_MainInfo.PrintLogo == 4)
				{
					this->DrawGUI(eLogo, 640 - 160, 480 - 144);
				}

				if (gProtect.m_MainInfo.PrintLogo == 5)
				{
					this->DrawGUI(eLogo, (640 / 2) - (150 / 2), (480 / 2) - (114 / 2));
				}
			}
		}
	}
}

bool Interface::MiniMapCheck()
{
	if (this->CheckWindow(Inventory) ||
		this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(Character) ||
		this->CheckWindow(CommandWindow) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(GensInfo) ||
		this->CheckWindow(Guild) ||
		this->CheckWindow(NPC_Dialog) ||
		this->CheckWindow(NPC_Julia) ||
		this->CheckWindow(NPC_Titus) ||
		this->CheckWindow(OtherStore) ||
		this->CheckWindow(Party) ||
		this->CheckWindow(PetInfo) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Store) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(FriendList) ||
		this->CheckWindow(FastMenu) ||
		this->CheckWindow(MuHelper) ||
		this->CheckWindow(Quest) ||
		this->CheckWindow(Lugard) ||
		this->CheckWindow(Jerint) ||
		this->CheckWindow(GoldenArcher1) ||
		this->CheckWindow(GoldenArcher2) ||
		this->CheckWindow(LuckyCoin1) ||
		this->CheckWindow(LuckyCoin2) ||
		this->CheckWindow(NPC_Duel) ||
		this->CheckWindow(NPC_Devin) ||
		this->CheckWindow(GuardNPC) ||
		this->CheckWindow(SeniorNPC) ||
		this->CheckWindow(GuardNPC2) ||
		this->CheckWindow(CastleGateSwitch) ||
		this->CheckWindow(CatapultNPC) ||
		this->CheckWindow(DuelScore) ||
		this->CheckWindow(CreateGuild) ||
		this->CheckWindow(Warehouse)) 
	{
		return true;
	}
	return false;
}

bool Interface::CombinedChecks()
{
	if ((this->CheckWindow(Inventory)
		&& this->CheckWindow(ExpandInventory)
		&& this->CheckWindow(Store)) ||
		(this->CheckWindow(Inventory)
		&& this->CheckWindow(Warehouse)
		&& this->CheckWindow(ExpandWarehouse)) ||
		(this->CheckWindow(Inventory)
		&& this->CheckWindow(Character)
		&& this->CheckWindow(Store)))
		return true;
	return false;
}

bool Interface::CheckMap()
{
	switch(gObjUser.m_MapNumber)
	{
		case eMapNumber::Lorencia:
			return false;
			break;
		case eMapNumber::Dungeon:
			return false;
			break;
		case eMapNumber::Devias:
			return false;
			break;
		case eMapNumber::Noria:
			return false;
			break;
		case eMapNumber::LostTower:
			return false;
			break;
		case eMapNumber::Atlans:
			return false;
			break;
		case eMapNumber::Tarkan:
			return false;
			break;
		case eMapNumber::Elbeland:
			return false;
			break;
		case eMapNumber::Icarus:
			return false;
			break;
		case eMapNumber::Trials:
			return false;
			break;
		case eMapNumber::Aida:
			return false;
			break;
		case eMapNumber::Crywolf:
			return false;
			break;
		case eMapNumber::Kanturu1:
			return false;
			break;
		case eMapNumber::Kanturu3:
			return false;
			break;
		case eMapNumber::Barracks:
			return false;
			break;
		case eMapNumber::Calmness:
			return false;
			break;
		case eMapNumber::Raklion:
			return false;
			break;
		case eMapNumber::Vulcanus:
			return false;
			break;
		case eMapNumber::Karutan1:
			return false;
			break;
		case eMapNumber::Karutan2:
			return false;
			break;
		default:
			return true;
			break;
	}
}

void Interface::CloseCustomWindow()
{
	pSetCursorFocus = false;
}

void Interface::DrawItem(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse)
{

	if (this->CheckWindow(ObjWindow::MoveList) || this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::SkillTree) || this->CheckWindow(ObjWindow::FullMap)
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Store)) 
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(Warehouse) 
		&& this->CheckWindow(ExpandWarehouse)) )
	{
		return;
	}

	pSetBlend(true);
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();

	sub_6363D0_Addr(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);

	float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;

	if (ItemID == 406)
	{
		sub_6358A0_Addr(0.4, v2, *(float*)0xE61E38, *(float*)0xE61E3C); //tamanho do bmd
	}
	else if (ItemID == 407)
	{
		sub_6358A0_Addr(0.5, v2, *(float*)0xE61E38, *(float*)0xE61E3C); //tamanho do bmd
	}
	else
	{
		sub_6358A0_Addr(0.7, v2, *(float*)0xE61E38, *(float*)0xE61E3C); //tamanho do bmd
	}

	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();

	sub_635830_Addr((LPVOID)0x87933A0); 
	sub_635DE0_Addr();
	sub_635E40_Addr();

	//posX 
	//posY
	//Width
	//Height
	//unk
	// 1 - Excellent Effect
	// 1 - Aura +7
	// 1 - original size
	glClear(0x100);

	//pDrawItemModel(PosX, PosY, Width, Height, ItemID, Level, Excl, Anc, OnMouse);

	 // int v31 = pTest((double)PosY);
	  //int v32 = pTest((double)PosX);

	VAngle v45;

	unsigned __int8 v44 = 1; //0 = parado / 1 = girando

	sub_6359B0_Addr(PosX, PosY, (int)&v45, 0); //posição do bmd
	sub_5CA0D0_Addr(ItemID, Level, Excl, Anc, (int)&v45, v44, 0); //funão que mostra o BMD
	
	sub_636720_Addr();

	glMatrixMode(0x1700);
	glPopMatrix();
	glMatrixMode(0x1701);
	glPopMatrix();

	sub_637770_Addr();

	glColor3f(1,1,1);
	pSetBlend(false);
}

void Interface::DrawConfirmOpen()
{
	if(!this->CheckWindow(Shop) && this->Data[eCONFIRM_MAIN].OnShow == true)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
		pSetCursorFocus = false;
	}

	if ((GetTickCount() - this->Data[eCONFIRM_BTN_OK].EventTick) < 100)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
		pSetCursorFocus = false;
	}

	if ((GetTickCount() - this->Data[eCONFIRM_BTN_CANCEL].EventTick) < 100)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
		pSetCursorFocus = false;
	}

	if( !this->Data[eCONFIRM_MAIN].OnShow )
	{
		return;
	}

	//this->Data[eCONFIRM_MAIN].EventTick = GetTickCount();

	float MainWidth			= 230.0;
	float MainHeight		= 130.0;
	float StartBody			= 90.0;
	float StartY			= 90.0;
	float StartX			= 25;
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (float)(29.0 / 2);

	pSetCursorFocus = true;

	gInterface.DrawGUI(eCONFIRM_MAIN, StartX, StartY + (float)2.0);
	gInterface.DrawGUI(eCONFIRM_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eCONFIRM_FRAME, StartX, StartY + (float)5.0, 5);
	gInterface.DrawGUI(eCONFIRM_FOOTER, StartX, StartY);

		this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 10, 210, 3, gCustomMessage.GetMessage(66));

		this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 40, 210, 3, gCustomMessage.GetMessage(67));

		this->DrawButton(eCONFIRM_BTN_OK, (int)StartX+40, (int)StartBody + 70, 0, 0);

		if( this->IsWorkZone(eCONFIRM_BTN_OK) )
		{
			int ScaleY = 30;
			// ----
			if( this->Data[eCONFIRM_BTN_OK].OnClick )
			{
				ScaleY = 60;
			}
			// ----
			this->DrawButton(eCONFIRM_BTN_OK, (int)StartX+40, (int)StartBody + 70, 0, ScaleY);
		}

		this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX+140, (int)StartBody + 70, 0, 0);

		if( this->IsWorkZone(eCONFIRM_BTN_CANCEL) )
		{
			int ScaleY = 30;
			// ----
			if( this->Data[eCONFIRM_BTN_CANCEL].OnClick )
			{
				ScaleY = 60;
			}
			// ----
			this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX+140, (int)StartBody + 70, 0, ScaleY);
		}

}

bool Interface::EventConfirm_OK(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eCONFIRM_BTN_OK].EventTick);
	// ----
	if (!this->Data[eCONFIRM_MAIN].OnShow || !IsWorkZone(eCONFIRM_BTN_OK))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eCONFIRM_BTN_OK].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCONFIRM_BTN_OK].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eCONFIRM_BTN_OK].EventTick = GetTickCount();

	PMSG_ITEM_BUY_RECV pMsg;

	pMsg.header.set(0xF3, 0xED,sizeof(pMsg));

	pMsg.slot = this->ConfirmSlot;

	DataSend((BYTE*)&pMsg,pMsg.header.size);

	this->Data[eCONFIRM_MAIN].OnShow = false;
	pSetCursorFocus = false;
	// ----
	return false;
}

bool Interface::EventConfirm_CANCEL(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eCONFIRM_BTN_CANCEL].EventTick);
	// ----
	if (!this->Data[eCONFIRM_MAIN].OnShow || !IsWorkZone(eCONFIRM_BTN_CANCEL))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eCONFIRM_BTN_CANCEL].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCONFIRM_BTN_CANCEL].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eCONFIRM_BTN_CANCEL].EventTick = GetTickCount();

	this->Data[eCONFIRM_MAIN].OnShow = false;
	pSetCursorFocus = false;
	// ----
	return false;
}

void Interface::DrawItemIMG(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse) // code hien thi item
{
	float x = PosX;
	float y = PosY;

	if(ItemID >= ITEM(0,0) && ItemID < ITEM(1,0))
	{
		x = PosX - 5;
		if(ItemID == ITEM(0,16) || ItemID == ITEM(0,19)) { y = PosY + 30; }
		else if((ItemID >= ITEM(0,32) && ItemID <= ITEM(0,35)) || gCustomBattleGloves.CheckGloves(ItemID) == true) { y = PosY + 15; }
		else if(ItemID >= ITEM(0,15) && ItemID < ITEM(0,32)) { y = PosY + 25; }
		else if(ItemID > ITEM(0,35)) { y = PosY + 20; }
		else if(ItemID == ITEM(0,0)) { y = PosY + 30; }
		else { y = PosY + 20; }
	}
	else if(ItemID >= ITEM(3,0) && ItemID < ITEM(4,0))
	{ y = PosY + 30; }
	else if(ItemID >= ITEM(7,0) && ItemID < ITEM(8,0)) { y = PosY + 25; }
	else if(ItemID >= ITEM(8,0) && ItemID < ITEM(9,0))
	{
		if((ItemID >= ITEM(8,2) && ItemID <= ITEM(8,4)) 
			|| ItemID == ITEM(8,7) || ItemID == ITEM(8,8)
			|| ItemID == ITEM(8,15))
		{
			y = PosY + 20;
		}
		else if(ItemID == ITEM(8,34) || ItemID == ITEM(8,35)) { y = PosY + 25; }
		else if(ItemID <= ITEM(8,73)) { y = PosY + 25; }
		else if(ItemID > ITEM(8,73)) { y = PosY + 35;}
	}
	else if(ItemID >= ITEM(9,0) && ItemID < ITEM(12,0)){ y = PosY + 25; }
	else if(ItemID >= 2048)
	{
		y = PosY + 25;

		if(ItemID ==ITEM(12,40)) { y = PosY + 10; }
	}
	else { y = PosY + 20; }

	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();

	sub_6363D0_Addr( 0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y );
	float v2 = *(float*) MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;

	sub_6358A0_Addr( 1.6, v2, *(float*)0xE61E38, *(float*)0xE61E3C );
	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();
	sub_635830_Addr((LPVOID) 0x87933A0);
	sub_635DE0_Addr();
	sub_635E40_Addr();
	pDrawItemModel(x, y, Width, Height, ItemID, Level, Excl, Anc, OnMouse); 
	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();
	glColor4f((GLfloat) 1.0, (GLfloat) 1.0, (GLfloat) 1.0,(GLfloat) 1.0);
	pSetBlend(false);
}

void Interface::DrawItemToolTipText ( void * item, int x, int y )
{
	static DWORD mem = 0;
	_asm 
	{
		PUSH 0
		PUSH 0
		PUSH 0
		PUSH item
		PUSH y
		PUSH x
		MOV mem,0x00861110
		CALL mem
		MOV ECX, EAX
		MOV mem,0x00861AA0
		CALL mem
		MOV ECX, EAX
		MOV mem,0x007E3E30
		CALL mem
	}
}

void Interface::DrawButtonRender(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

#if(MAP_USAGE)
int GetTimeGMT()
{
	time_t rawTime;
	struct tm* timeInfo;

	time(&rawTime);
	timeInfo = gmtime(&rawTime);

	timeInfo->tm_hour += (gProtect.m_MainInfo.ServerTime);
	//timeInfo->tm_hour += +1;
	return mktime(timeInfo);


}
float fAlpha = 0.1f;
void BRenderTimeCountDown(float x, float y,float w, int MatchTime)
{
	char lpszStr[256];
	char lpszStrS[10];
	int iMinute = MatchTime / 60;
	DWORD ColorText = 0xE6FCF7FF;
	wsprintf(lpszStr, " %.2d :", iMinute);

	int iSecondTime = MatchTime - (iMinute * 60);
	if (iSecondTime >= 0)
	{
		wsprintf(lpszStrS, " %.2d", iSecondTime);
		strcat(lpszStr, lpszStrS);
	}

	if (iMinute < 5)
	{
		ColorText = 0xFF2121FF;
	}
	if (iMinute < 15)
	{
		wsprintf(lpszStrS, ": %.2d", ((int)WorldTime % 60));
		strcat(lpszStr, lpszStrS);
	}
	//HFONT FontTextTime = CreateFontA(14, 700, 0, 0, 700, 0, 0, 0, 0x1, 0, 0, 3, 0, "Tahoma");
	CustomFont.Draw((HFONT)pFontNormal, x, y, 0xE6FCF7FF, 0x0, w, 0, 3, lpszStr); //Buoc Vao
	//DeleteObject(FontTextTime);

}


void Interface::DrawTimeUseMap()
{
	if ((gInterface.CheckWindow(ObjWindow::CashShop) || gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::ChatWindow) || gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::MoveList)))
	{
		return;
	}
	if (mMapUsageData.Map != pMapNumber)
	{
		return;
	}
	if ((mMapUsageData.Time - GetTimeGMT() < 1))
	{
		mMapUsageData.Time = 0;
		mMapUsageData.Map = 255;
		return;
	}
	float InfoW = 120;
	float InfoH = 30;
	float InfoX = 5;
	float InfoY = MAX_WIN_HEIGHT - (InfoH + 65);
	gElemental.gInfoBox(InfoX, InfoY, InfoW, InfoH, 0x00000096, 0, 0); //1vs3
	//HFONT FontTextTime = CreateFontA(16, 700, 0, 0, 700, 0, 0, 0, 0x1, 0, 0, 3, 0, "Tahoma");
	CustomFont.Draw((HFONT)pFontNormal, InfoX, InfoY+5, 0xFFAA00FF, 0x0, InfoW + 10, 0, 3, "Map Usage Time"); //Buoc Vao
	//DeleteObject(FontTextTime);
	BRenderTimeCountDown(InfoX, (InfoY + InfoH) - 7, InfoW + 10, mMapUsageData.Time - GetTimeGMT());
}

#endif

void Interface::DrawItem3D(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int ExtOption, int Ancient, bool PickUp, float Scale, bool Center)
{
	float x = PosX;
	float y = PosY;

	if (ItemID >= ITEM(0, 0) && ItemID < ITEM(1, 0))
	{
		x = PosX - 10;
		if (ItemID == ITEM(0, 16) || ItemID == ITEM(0, 19)) {
			y = PosY + 30;
			//g_Console.AddMessage(1, "DrawItem3D %d", ItemID);
		}
		else if ((ItemID >= ITEM(0, 32) && ItemID <= ITEM(0, 35)) || gCustomBattleGloves.CheckGloves(ItemID) == true) { y = PosY + 15; }
		else if (ItemID >= ITEM(0, 15) && ItemID < ITEM(0, 32)) { y = PosY + 25; }
		else if (ItemID > ITEM(0, 35)) { y = PosY + 20; }
		else if (ItemID == ITEM(0, 0)) { y = PosY + 30; }
		else { y = PosY + 20; }
	}
	else if (ItemID >= ITEM(3, 0) && ItemID < ITEM(4, 0))
	{
		y = PosY + 30;
	}
	else if (ItemID >= ITEM(7, 0) && ItemID < ITEM(8, 0)) { y = PosY + 25; }
	else if (ItemID >= ITEM(8, 0) && ItemID < ITEM(9, 0))
	{
		if ((ItemID >= ITEM(8, 2) && ItemID <= ITEM(8, 4))
			|| ItemID == ITEM(8, 7) || ItemID == ITEM(8, 8)
			|| ItemID == ITEM(8, 15))
		{
			y = PosY + 20;
		}
		else if (ItemID == ITEM(8, 34) || ItemID == ITEM(8, 35)) { y = PosY + 25; }
		else if (ItemID <= ITEM(8, 73)) { y = PosY + 25; }
		else if (ItemID > ITEM(8, 73)) { y = PosY + 35; }
	}
	else if (ItemID >= ITEM(9, 0) && ItemID < ITEM(12, 0)) { y = PosY + 25; }
	else if (ItemID >= 2048)
	{
		y = PosY + 25;

		if (ItemID == ITEM(12, 40)) { y = PosY + 10; }
	}
	else { y = PosY + 20; }
	PosX = x;
	PosY = y - 25;
	pSetBlend(true);
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();
	sub_6363D0_Addr(0, 0, *(GLsizei*)0x00E61E58, *(GLsizei*)0x00E61E5C);
	float v2 = *(float*)0x00E61E58 / *(float*)0x00E61E5C;
	sub_6358A0_Addr(Scale, v2, *(float*)0xE61E38, *(float*)0xE61E3C);
	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();
	sub_635830_Addr((LPVOID)0x87933A0);
	sub_635DE0_Addr();
	sub_635E40_Addr();
	glClear(0x100);


	pDrawItemModel(PosX, PosY, Width, Height, ItemID, Level, ExtOption, Ancient, PickUp);

	sub_636720_Addr();
	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();
	glColor3f(1, 1, 1);
	pSetBlend(false);
	return;
}


bool Interface::RenderCheckBox(float PosX, float PosY, DWORD TextColor, bool Checkis, LPCSTR Text, ...)
{
	bool mreturn = false;
	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	if (Checkis)
	{
		pDrawButton(31593, PosX, PosY, 15.0, 15.0, 0.0, 0.0);
	}
	else
	{
		pDrawButton(31593, PosX, PosY, 15.0, 15.0, 0.0, 15.0);
	}
	gElemental.DrawText((HFONT)pFontBold, PosX + 22, PosY + 3, TextColor, 0x0, 0, 0, 1, Text);

	if (pCheckMouseOver(PosX, PosY, 15, 15) == 1)
	{
		if ((GetKeyState(VK_LBUTTON) & 0x8000) && GetTickCount() - gInterface.Data[eWindowClick].EventTick > 500)
		{
			gInterface.Data[eWindowClick].EventTick = GetTickCount();
			PlayBuffer(25, 0, 0);
			gElemental.LockMouse = GetTickCount() + 500;
			mreturn = true;
			//gInterface.DrawMessage(1, "CCC");
		}
	}
	return mreturn;
}

void Interface::DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float ScaleW, float ScaleH, bool ScaleUp) 
{
    float v1, v2;

    if (W) {
        W /= ScaleW;
        v1 = ScaleW / (SourceW / W);
    }
    else {
        v1 = ScaleW;
    }

    if (H) {
        H /= ScaleH;
        v2 = ScaleH / (SourceH / H);
    }
    else {
        v2 = ScaleH;
    }
    RenderBitmap(ModelID, X, Y, W, H, SourceX / SourceW, SourceY / SourceH, v1, v2, ScaleUp, 1, 0.0);
}

void Interface::DrawFrameAlpha(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float ScaleW, float ScaleH, bool ScaleUp) 
{
    float v1, v2;

    if (W) {
        W /= ScaleW;
        v1 = ScaleW / (SourceW / W);
    }
    else {
        v1 = ScaleW;
    }

    if (H) {
        H /= ScaleH;
        v2 = ScaleH / (SourceH / H);
    }
    else {
        v2 = ScaleH;
    }
    RenderBitmap(ModelID, X, Y, W, H, SourceX / SourceW, SourceY / SourceH, v1, v2, ScaleUp, 1, 0.8);
}

void Interface::NewModelRender3D(float x, float y, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse) // code hien thi item
{
	glMatrixMode(0x1701);
	glPushMatrix( );
	glLoadIdentity( );

	glViewport2( 0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y );
	float v2 = *(float*) MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;

	gluPerspective2(1.0, v2, *(float*)0xE61E38, *(float*)0xE61E3C );
	glMatrixMode(0x1700u);
	glPushMatrix( );
	glLoadIdentity( );
	GetOpenGLMatrix(0x87933A0);
	EnableDepthTest( );
	EnableDepthMask( );

	RenderItem3D(x, y, Width, Height, ItemID, Level, Excl, Anc, OnMouse);

	glMatrixMode(0x1700u);
	glPopMatrix( );
	glMatrixMode(0x1701u);
	glPopMatrix( );

	glColor4f((GLfloat) 1.0, (GLfloat) 1.0, (GLfloat) 1.0,(GLfloat) 1.0);
	pSetBlend(false);
}

bool Interface::IsWorkZone5(float X, float Y, float MaxX, float MaxY)
{
	if ((gObjUser.m_CursorX < X || gObjUser.m_CursorX > MaxX)
		|| (gObjUser.m_CursorY < Y || gObjUser.m_CursorY > MaxY))
	{
		return false;
	}
	// ----
	return true;
}

int Interface::DrawToolTipEx(DWORD Color, int PosX, int PosY, int Width, int Height, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	char Buff2[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----

	int LineCount = 0;

	strcpy(Buff2,Buff);

	char * Line = strtok(Buff2, "\n");
	// ----
	while( Line != NULL )
	{
		LineCount++;
		Line = strtok(NULL, "\n");
	}

	pSetBlend(1);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	pDrawBarForm(PosX, PosY, Width, LineCount*10, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();

	glColor3f(1.0, 1.0, 1.0);

	this->DrawFormat(eWhite, PosX, PosY, Width, Align, Buff);

	pSetBlend(0);
	return 0;
}

void Interface::DrawColoredButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY, DWORD Color)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY, Color);
}

bool Interface::gDrawButtonGUI(int IDGUID, float PosX, float PosY, float SizeW, float SizeH, int TypeButton)
{
	bool mreturn = false;
	//=====================Button 1

	if (TypeButton == 3)
	{
		if (pCheckMouseOver(PosX, PosY, SizeW, SizeH) == 1)
		{
			gElemental.LockMouse = GetTickCount() + 500;

			if ((GetKeyState(VK_LBUTTON) & 0x8000) && GetTickCount() - gInterface.Data[eWindowClick].EventTick > 500 && !gElemental.LockButtonHover)
			{
				gInterface.Data[eWindowClick].EventTick = GetTickCount();
				PlayBuffer(25, 0, 0);
				mreturn = true;
				pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, SizeH * 2);
			}
			else {
				pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, SizeH * 1);
			}

		}
		else {
			pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, 0.0);
		}
	}
	else if (TypeButton == 2)
	{
		if (pCheckMouseOver(PosX, PosY, SizeW, SizeH) == 1)
		{
			gElemental.LockMouse = GetTickCount() + 500;

			if ((GetKeyState(VK_LBUTTON) & 0x8000) && GetTickCount() - gInterface.Data[eWindowClick].EventTick > 500 && !gElemental.LockButtonHover)
			{
				gInterface.Data[eWindowClick].EventTick = GetTickCount();
				PlayBuffer(25, 0, 0);
				mreturn = true;
				pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, SizeH * 1);
			}
			else {
				pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, 0.0);
			}

		}
		else {
			pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, 0.0);
		}
	}

	else
	{
		if (pCheckMouseOver(PosX, PosY, SizeW, SizeH) == 1)
		{
			gElemental.LockMouse = GetTickCount() + 500;
			if (GetTickCount() - gInterface.Data[eWindowClick].EventTick > 500 && !gElemental.LockButtonHover) //Click
			{
				if ((GetKeyState(VK_LBUTTON) & 0x8000))
				{
					gInterface.Data[eWindowClick].EventTick = GetTickCount();
					PlayBuffer(25, 0, 0);
					mreturn = true;
				}
			}
			pDrawColorButton(IDGUID, PosX, PosY, SizeW, SizeH, 0, 0, pMakeColor(255, 204, 20, 130));
		}
		else
		{
			pDrawGUI(IDGUID, PosX, PosY, SizeW, SizeH);
		}
	}

	return mreturn;
}

void Interface::DrawBarForm(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	pSetBlend(true);
	glColor4f((GLfloat)red, (GLfloat)green, (GLfloat)blue, (GLfloat)alpha);
	pDrawBarForm(PosX, PosY, Width, Height, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}

void Interface::DrawBarForm2(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	pSetBlend(true);
	glColor4f(red, green, blue, alpha);
	pDrawBarForm(PosX, PosY, Width, Height, 0.0f, 0);
	//DrawTest(PosX,PosY,Width,Height,0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}


void Interface::DrawAnimatedGUI(short ObjectID, float PosX, float PosY)
{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	// ----
	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

bool Interface::ControlTextBox(KBDLLHOOKSTRUCT Hook)
{
	if (gInterface.Data[eSTATSADD_MAIN_STR].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 1;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 1;
		}

		int SelectedIndex = 0;

		if (Hook.vkCode == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Hook.vkCode == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Hook.vkCode == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Hook.vkCode >= 0x30 && Hook.vkCode <= 0x39) || (Hook.vkCode >= 0x60 && Hook.vkCode <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Hook.vkCode);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[1] =
		{
			eSTATSADD_STATBOX01,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	else if (gInterface.Data[eSTATSADD_MAIN_AGI].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 1;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 1;
		}

		int SelectedIndex = 0;

		if (Hook.vkCode == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Hook.vkCode == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Hook.vkCode == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Hook.vkCode >= 0x30 && Hook.vkCode <= 0x39) || (Hook.vkCode >= 0x60 && Hook.vkCode <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Hook.vkCode);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[1] =
		{
			eSTATSADD_STATBOX02,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	else if (gInterface.Data[eSTATSADD_MAIN_VIT].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 1;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 1;
		}

		int SelectedIndex = 0;

		if (Hook.vkCode == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Hook.vkCode == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Hook.vkCode == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Hook.vkCode >= 0x30 && Hook.vkCode <= 0x39) || (Hook.vkCode >= 0x60 && Hook.vkCode <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Hook.vkCode);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[1] =
		{
			eSTATSADD_STATBOX03,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	else if (gInterface.Data[eSTATSADD_MAIN_ENE].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 1;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 1;
		}

		int SelectedIndex = 0;

		if (Hook.vkCode == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Hook.vkCode == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Hook.vkCode == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Hook.vkCode >= 0x30 && Hook.vkCode <= 0x39) || (Hook.vkCode >= 0x60 && Hook.vkCode <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Hook.vkCode);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[1] =
		{
			eSTATSADD_STATBOX04,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	else if (gInterface.Data[eSTATSADD_MAIN_CMD].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 1;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 1;
		}

		int SelectedIndex = 0;

		if (Hook.vkCode == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Hook.vkCode == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Hook.vkCode == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Hook.vkCode >= 0x30 && Hook.vkCode <= 0x39) || (Hook.vkCode >= 0x60 && Hook.vkCode <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Hook.vkCode);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[1] =
		{
			eSTATSADD_STATBOX05,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	else
	{
		return false;
	}

	return false;
}

void Interface::DrawColoredAnimatedGUI(short ObjectID, float X, float Y, DWORD Color)
{
	//if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	//{
	this->Data[ObjectID].X = X;
	this->Data[ObjectID].Y = Y;
	this->Data[ObjectID].MaxX = X + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = Y + this->Data[ObjectID].Height;
	//}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawAnimatedButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	//if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	//{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	//}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

void Interface::draw_chat_message(int mode, char* name, char* text)
{
	CharTest char_text;
	CharTest char_name;
	sub_409A50_addr(&char_text, (int)text);
	sub_409A50_addr(&char_name, (int)name);
	char* this_ = (char*)pChatBoxThis((DWORD*)pWindowThis());
	sub_7894E0_Addr(this_, (int)&char_name, (int)&char_text, mode, 0);
	sub_409AD0_Addr((void*)&char_name);
	sub_409AD0_Addr((void*)&char_text);
}

bool Interface::IsWorkZone7(int Index, int add_points)
{
	if (pCursorX < this->m_Data[Index].X - add_points || pCursorX > this->m_Data[Index].MaxX + add_points ||
		pCursorY < this->m_Data[Index].Y - add_points || pCursorY > this->m_Data[Index].MaxY + add_points)
	{
		return false;
	}
	return true;
}

void Interface::TextDraw(int PosX, int PosY, int box_width, int Arg5, int Color, int Arg7, int Align, HGDIOBJ Font, LPCTSTR Format, ...)
{
	char TextBuff[1024] = { 0 };
	va_list va;
	va_start(va, Format);
	vsprintf_s(TextBuff, Format, va);
	va_end(va);

	pSetFont(pTextThis(), (int)Font);
	int v13 = sub_41FFE0_Addr(pTextThis());
	int v15 = sub_420010_Addr(pTextThis());
	pSetTextColor2(pTextThis(), Color);
	pSetBgColor(pTextThis(), Arg7);
	pSetBkColor(pTextThis(), 255, 255, 255, 0);

	char* line = strtok(TextBuff, "\n");
	// ----

	int rect[4];
	bool on = glIsEnabled(GL_SCISSOR_TEST);
	glGetIntegerv(GL_SCISSOR_BOX, rect);

	while (line != nullptr)
	{
		int line_height = GetTextHeight(line, Font);
		int line_width = GetTextWidth(line, Font);

		if (box_width > 0)
		{
			int start_x_real = pGetRealX(PosX);
			int start_y_real = pGetRealY(MAX_WIN_HEIGHT - PosY - line_height);
			int width_real = pGetRealX(box_width);
			int height_real = pGetRealY(line_height);

			if (on)
			{
				if (start_y_real < rect[1])
					start_y_real = rect[1];

				if (start_y_real + height_real > rect[1] + rect[3])
					height_real = rect[1] + rect[3] - start_y_real;
			}

			glEnable(GL_SCISSOR_TEST);
			glScissor(start_x_real, start_y_real, width_real, height_real);
		}

		//if (Interface::IsWorkZone(PosX, PosY, PosX + box_width, PosY + line_height + 6))
		if (pIsWorkZone(PosX, PosY, box_width, line_height + 2))
		{
			if (box_width > 0 && line_width > box_width)
			{
				pDrawText(pTextThis(), PosX - this->scrollable_counter, PosY, line, 0, Arg5, (int*)Align, 0);

				int x = line_width - box_width / 2;

				if (this->scrollable_counter >= x)
				{
					pDrawText(pTextThis(), PosX + box_width - (this->scrollable_counter - x), PosY, line, 0, Arg5, (int*)Align, 0);

					if (PosX + box_width - (this->scrollable_counter - x) == PosX)
						this->scrollable_counter = 0;
				}

				if (strcmp(this->scrollable_buffer, line) != 0)
				{
					strcpy_s(this->scrollable_buffer, line/*, strlen(line)*/);
					this->scrollable_counter = 0;
				}

				this->scrollable_counter++;
			}
			else
			{
				//this->scrollable_counter = 0;
				pDrawText(pTextThis(), PosX, PosY, line, box_width, Arg5, (int*)Align, 0);
			}

			PosY += 10;
			line = strtok(nullptr, "\n");
		}
		else
		{
			if (!strcmp(this->scrollable_buffer, line))
				this->scrollable_counter = 0;

			pDrawText(pTextThis(), PosX, PosY, line, box_width, Arg5, (int*)Align, 0);
			PosY += 10;
			line = strtok(nullptr, "\n");
		}

		if (box_width > 0)
			glDisable(GL_SCISSOR_TEST);
	}

	glScissor(rect[0], rect[1], rect[2], rect[3]);

	if (on)
		glEnable(GL_SCISSOR_TEST);

	pSetTextColor2(pTextThis(), v13);
	pSetBgColor(pTextThis(), v15);
}

void Interface::DrawButton7(int Index, float PosX, float PosY, float Width, float Height, MU_4float* Base, MU_4float* OnClick, MU_4float* Hover, LPCTSTR Text/*, ...*/)
{
	if (Index != -1)
	{
		m_Data[Index].Width = Width;
		m_Data[Index].Height = Height;
		m_Data[Index].X = PosX;
		m_Data[Index].Y = PosY;
		m_Data[Index].MaxX = PosX + Width;
		m_Data[Index].MaxY = PosY + Height;
		m_Data[Index].Type = objButton;

		/*if (pIsKeyRepeat(VK_LBUTTON))
		{
			DrawBarForm(PosX,PosY,Width,Height,OnClick->Red,OnClick->Green,OnClick->Blue,OnClick->Alpha);
		}
		else */
		if (this->IsWorkZone7(Index))
		{
			DrawBarForm2(PosX - 0.4, PosY - 0.4, Width + 0.8, Height + 0.8, 1.0, 1.0, 1.0, 0.8);

			if (IsRepeatKey(VK_LBUTTON))
				DrawBarForm2(PosX, PosY, Width, Height, OnClick->Red, OnClick->Green, OnClick->Blue, OnClick->Alpha);
			else
			{
				DrawBarForm2(PosX, PosY, Width, Height, Hover->Red, Hover->Green, Hover->Blue, Hover->Alpha);
			}
		}
		else
		{
			DrawBarForm2(PosX, PosY, Width, Height, Base->Red, Base->Green, Base->Blue, Base->Alpha);
		}
	}
	else
	{
		DrawBarForm2(PosX, PosY, Width, Height, Base->Red, Base->Green, Base->Blue, Base->Alpha);
	}


	if (Text != nullptr)
	{
		int text_width = GetTextWidth(const_cast<char*>(Text), pFontNormal);
		int text_height = GetTextHeight(const_cast<char*>(Text), pFontNormal);

		if (text_width > Width - 10)
			this->TextDraw(PosX + 5, PosY + (Height - text_height) / 2, Width - 10, 1, eGold, 0, eLeftToRightBoxSize, pFontNormal, Text);
		else
			this->TextDraw(PosX + Width / 2, PosY + (Height - text_height) / 2, 0, 1, eGold, 0, 8, pFontNormal, Text);
	}
}

GLvoid GetDrawCircle(int ID, float X, float Y, float W, float CurrenX, float CurrenY, float SetScale, int ScaleSize, int ScalePosicion, float Alpha)
{
	float v14; // ST1C_4@1
	float v15; // ST18_4@1
	GLuint vertexcount; // ST1C_4@5
	float v33; // ST1C_4@5
	GLfloat angle; // ST1C_4@5
	GLfloat texturecoord[2]; // [sp+2Ch] [bp-40h]@5
	GLfloat VertexCoord[4]; // [sp+4Ch] [bp-20h]@5

	SetScale = SetScale / 2;
	//--
	W = W / 2;
	X = X + W;
	Y = Y + W;

	if (ScalePosicion)
	{
		X = ((double(__cdecl*)(float a1)) 0x00636420)(X);
		Y = ((double(__cdecl*)(float a1)) 0x00636450)(Y);
	}

	if (ScaleSize)
	{
		W = ((double(__cdecl*)(float a1)) 0x00636420)(W);
	}

	v33 = (double)pWinHeight - Y;

	vertexcount = 30;

	((bool(__cdecl*)(int a1)) 0x00635CF0)(ID);

	glBegin(GL_TRIANGLE_FAN);

	angle = 2.0 * 3.1415926 / vertexcount;
	//--
	if (Alpha > 0.0)
		glColor4f(1.0, 1.0, 1.0, Alpha);
	texturecoord[0] = CurrenX;
	texturecoord[1] = CurrenY;
	glTexCoord2fv(texturecoord);
	//--
	VertexCoord[0] = X;
	VertexCoord[1] = v33;
	VertexCoord[2] = 0.0;
	VertexCoord[3] = 1.0;
	glVertex4fv(VertexCoord);

	for (int i = 0; i < vertexcount; i++)
	{
		texturecoord[0] = (std::cos(angle * i) * SetScale) + CurrenX;
		texturecoord[1] = (std::sin(angle * i) * SetScale) + CurrenY;
		glTexCoord2fv(texturecoord);
		VertexCoord[0] = (std::cos(angle * i) * W) + X;
		VertexCoord[1] = (std::sin(angle * i) * -W) + v33;
		VertexCoord[2] = 0.0;
		VertexCoord[3] = 1.0;
		glVertex4fv(VertexCoord);
	}
	//--
	texturecoord[0] = (1.0 * SetScale) + CurrenX;
	texturecoord[1] = (0.0 * SetScale) + CurrenY;
	glTexCoord2fv(texturecoord);
	//--
	VertexCoord[0] = (1.0 * W) + X;
	VertexCoord[1] = (0.0 * -W) + v33;
	VertexCoord[2] = 0.0;
	VertexCoord[3] = 1.0;
	glVertex4fv(VertexCoord);
	//--
	if (Alpha > 0.0)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	//--
	glEnd();
}