// Camera.cpp: implementation of the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Camera.h"
#include "Import.h"
#include "Protect.h"
#include "Util.h"
#include "Offset.h"
#include "SmoothCamera.h"

CCamera gCamera;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamera::CCamera() // OK
{
	this->m_Enable = 0;

	this->m_IsMove = 0;

	this->m_CursorX = 0;

	this->m_CursorY = 0;

	this->m_Zoom.MinPercent = 50.0;

	this->m_Zoom.MaxPercent = 130.0;

	this->m_Zoom.Precision = 2.0;

	this->m_Address.Zoom = (float*)0x00D27BFC;

	this->m_Address.RotX = (float*)0x087933D8;

	this->m_Address.RotY = (float*)0x00D27B88;

	this->m_Address.PosZ = (double*)0x00D255A0;

	this->m_Address.ClipX[0] = (double*)0x00D2C848;

	this->m_Address.ClipX[1] = (double*)0x00D2C898;

	this->m_Address.ClipY[0] = (float*)0x00D2C894;

	this->m_Address.ClipY[1] = (float*)0x00D2C8A8;

	this->m_Address.ClipGL = (float*)0x00D2570C;

	this->m_Default.IsLoad = 0;

	this->LastPress = GetTickCount();

	SetCompleteHook(0xE9,0x0063764C,&RotateDamageAngle);
}

CCamera::~CCamera() // OK
{

}

void CCamera::Toggle() // OK
{
	if(*(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		pDrawMessage(pGetTextLine((1992+this->m_Enable)),1);

		this->m_Enable ^= 1;

		if(((this->m_Default.IsLoad==0)?(this->m_Default.IsLoad++):this->m_Default.IsLoad) == 0)
		{
			this->m_Default.Zoom = (*this->m_Address.Zoom);

			this->m_Default.RotX = (*this->m_Address.RotX);

			this->m_Default.RotY = (*this->m_Address.RotY);

			this->m_Default.PosZ = (*this->m_Address.PosZ);

			this->m_Default.ClipX[0] = (*this->m_Address.ClipX[0]);

			this->m_Default.ClipX[1] = (*this->m_Address.ClipX[1]);

			this->m_Default.ClipY[0] = (*this->m_Address.ClipY[0]);

			this->m_Default.ClipY[1] = (*this->m_Address.ClipY[1]);

			this->m_Default.ClipGL = (*this->m_Address.ClipGL);
		}
	}
}

void CCamera::Restore() // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->SetDefaultValue();
	}
}

void CCamera::SetIsMove(BOOL IsMove) // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_IsMove = IsMove;
	}
}

void CCamera::SetCursorX(LONG CursorX) // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_CursorX = CursorX;
	}
}

void CCamera::SetCursorY(LONG CursorY) // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_CursorY = CursorY;
	}
}

void CCamera::Zoom(MOUSEHOOKSTRUCTEX* lpMouse) // OK
{
	if(this->m_Enable == 0 || this->m_IsMove != 0 || *(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	this->m_Zoom.MinLimit = (this->m_Default.Zoom/100)*this->m_Zoom.MinPercent;

	this->m_Zoom.MaxLimit = (this->m_Default.Zoom/100)*this->m_Zoom.MaxPercent;

	if(((int)lpMouse->mouseData) > 0)
	{
		if((*this->m_Address.Zoom) >= this->m_Zoom.MinLimit)
		{
			SetFloat((DWORD)this->m_Address.Zoom,((*this->m_Address.Zoom)-this->m_Zoom.Precision));
		}
	}

	if(((int)lpMouse->mouseData) < 0)
	{
		if((*this->m_Address.Zoom) <= this->m_Zoom.MaxLimit)
		{
			SetFloat((DWORD)this->m_Address.Zoom,((*this->m_Address.Zoom)+this->m_Zoom.Precision));
		}
	}

	SmoothCamera.SetCurrentValue();
}

void CCamera::Move(MOUSEHOOKSTRUCTEX* lpMouse) // OK
{
	if(this->m_Enable == 0 || this->m_IsMove == 0 || *(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	if(this->m_CursorX < lpMouse->pt.x)
	{
		if((*this->m_Address.RotX) > 309.0f)
		{
			SetFloat((DWORD)this->m_Address.RotX,-45.0f);
		}
		else
		{
			SetFloat((DWORD)this->m_Address.RotX,((*this->m_Address.RotX)+6.0f));
		}
	}
	
	if(this->m_CursorX > lpMouse->pt.x)
	{
		if((*this->m_Address.RotX) < -417.0f)
		{
			SetFloat((DWORD)this->m_Address.RotX,-45.0f);
		}
		else
		{
			SetFloat((DWORD)this->m_Address.RotX,((*this->m_Address.RotX)-6.0f));
		}
	}

	if(this->m_CursorY < lpMouse->pt.y)
	{
		if((*this->m_Address.RotY) < -22.5f)
		{
			SetFloat((DWORD)this->m_Address.RotY,((*this->m_Address.RotY)+2.420f));
			SetDouble((DWORD)this->m_Address.PosZ,((*this->m_Address.PosZ)-44.0f));
		}
	}

	if(this->m_CursorY > lpMouse->pt.y)
	{
		if((*this->m_Address.RotY) > -90.0f)
		{
			SetFloat((DWORD)this->m_Address.RotY,((*this->m_Address.RotY)-2.420f));
			SetDouble((DWORD)this->m_Address.PosZ,((*this->m_Address.PosZ)+44.0f));
		}
	}

	this->m_CursorX = lpMouse->pt.x;

	this->m_CursorY = lpMouse->pt.y;

	SmoothCamera.SetCurrentValue();
}

void CCamera::SetCurrentValue() // OK
{
	SetDouble((DWORD)this->m_Address.ClipX[0],(4190.0f+(abs(((*this->m_Address.PosZ)-150.0f))*3.0f)));

	SetDouble((DWORD)this->m_Address.ClipX[1],(4190.0f+(abs(((*this->m_Address.PosZ)-150.0f))*3.0f)));

	SetFloat((DWORD)this->m_Address.ClipY[0],(5400.0f+(((float)abs(((*this->m_Address.PosZ)-150.0f)))*3.0f)));

	SetFloat((DWORD)this->m_Address.ClipY[1],(5400.0f+(((float)abs(((*this->m_Address.PosZ)-150.0f)))*3.0f)));

	SetFloat((DWORD)this->m_Address.ClipGL,(2100.0f+(((float)abs(((*this->m_Address.PosZ)-150.0f)))*3.0f)));
}

void CCamera::SetDefaultValue() // OK
{
	if(this->m_Default.IsLoad != 0)
	{
		SetFloat((DWORD)this->m_Address.Zoom,this->m_Default.Zoom);

		SetFloat((DWORD)this->m_Address.RotX,this->m_Default.RotX);

		SetFloat((DWORD)this->m_Address.RotY,this->m_Default.RotY);

		SetDouble((DWORD)this->m_Address.PosZ,this->m_Default.PosZ);

		SetDouble((DWORD)this->m_Address.ClipX[0],this->m_Default.ClipX[0]);

		SetDouble((DWORD)this->m_Address.ClipX[1],this->m_Default.ClipX[1]);

		SetFloat((DWORD)this->m_Address.ClipY[0],this->m_Default.ClipY[0]);

		SetFloat((DWORD)this->m_Address.ClipY[1],this->m_Default.ClipY[1]);

		SetFloat((DWORD)this->m_Address.ClipGL,this->m_Default.ClipGL);
	}

	pDrawMessage(pGetTextLine(1994),1);
}

void CCamera::CalcDamageAngle(float& X,float& Y,float D) // OK
{
	const float DamageAngle = 0.01745329f;

	float AngleX = cos(DamageAngle*(*gCamera.m_Address.RotX));
	float AngleY = sin(DamageAngle*(*gCamera.m_Address.RotX));

	X += D/0.7071067f*AngleX/2;
	Y -= D/0.7071067f*AngleY/2;
}

void __declspec(naked) CCamera::RotateDamageAngle() // OK
{
	static DWORD RotateDamageAngleAddress1 = 0x0063752D;

	_asm
	{
		Lea Eax,[Ebp-0x38]
		Lea Ecx,[Ebp-0x3C]
		Push Dword Ptr[Ebp+0x18]
		Push Eax
		Push Ecx
		Call CalcDamageAngle
		Add Esp,0xC
		Jmp[RotateDamageAngleAddress1]
	}
}