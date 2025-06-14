#include "stdafx.h"
#include "CustomPetGlow.h"
#include "MemScript.h"

cRenderMesh cRender;

cRenderMesh::cRenderMesh()
{
	this->Init();
}
cRenderMesh::~cRenderMesh()
{
}


void cRenderMesh::Init() // OK
{
	for(int n=0;n < MAX_PET_GLOW;n++)
	{
		this->m_RenderMeshPet[n].Index = -1;
	};
}

bool cRenderMesh::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return 0;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return 0;
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

			RENDER_MESH info;

			memset(&info,0,sizeof(info));

			static int CustomItemIndexCount = 0;

			info.Index = CustomItemIndexCount++;

			info.ItemIndex = lpMemScript->GetNumber();

			info.EffectIndex = lpMemScript->GetAsNumber();

			info.EffectType = lpMemScript->GetAsNumber();

			info.ColorR = lpMemScript->GetAsFloatNumber();
			
			info.ColorG = lpMemScript->GetAsFloatNumber();
			
			info.ColorB = lpMemScript->GetAsFloatNumber();
			
			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
		return 0;
	}

	delete lpMemScript;

	return 1;
}

void cRenderMesh::SetInfo(RENDER_MESH info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_PET_GLOW)
	{
		return;
	}

	this->m_RenderMeshPet[info.Index] = info;
}
