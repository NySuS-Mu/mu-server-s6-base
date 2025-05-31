#include "stdafx.h"
#include "CustomMonster.h"
#include "MemScript.h"

cCustomMonsters gMonsters;

cCustomMonsters::cCustomMonsters()
{
	this->Init();
}

cCustomMonsters::~cCustomMonsters()
{
	
}

void cCustomMonsters::Init()
{
	for (int n = 0; n < MAX_CUSTOMMONSTER; n++)
	{
		this->m_Monsters[n].Index = -1;
	}

	for (int n = 0; n < MAX_BOSSCLASS; n++)
	{
		this->m_BossClass[n].Index = -1;
	}
}

bool cCustomMonsters::Load(char * path)
{
	CMemScript* lpMemScript = new CMemScript;

	int Index = 0;
	int IndexBoss = 0;
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

			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOMMONSTER_DATA info;

					memset(&info,0,sizeof(info));

					info.Index = Index++;

					info.ID = lpMemScript->GetNumber();

					info.Type = lpMemScript->GetAsNumber();

					strcpy_s(info.Name,lpMemScript->GetAsString());

					strcpy_s(info.Dir,lpMemScript->GetAsString());

					strcpy_s(info.Folder,lpMemScript->GetAsString());

					strcpy_s(info.BMDFile,lpMemScript->GetAsString());

					info.Size = lpMemScript->GetAsFloatNumber();

					this->SetInfo(info);
				}
				else if(section == 2)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					BOSSCLASS_DATA info;

					memset(&info,0,sizeof(info));

					info.Index = IndexBoss++;

					info.ID = lpMemScript->GetNumber();

					info.Type = lpMemScript->GetAsNumber();

					strcpy_s(info.Name,lpMemScript->GetAsString());

					info.SetID = lpMemScript->GetAsNumber();

					info.IndexVK1 = GET_ITEM(lpMemScript->GetAsNumber(),lpMemScript->GetAsNumber());

					info.IndexVK2 = GET_ITEM(lpMemScript->GetAsNumber(),lpMemScript->GetAsNumber());

					info.IndexWing = GET_ITEM(lpMemScript->GetAsNumber(),lpMemScript->GetAsNumber());

					info.ItemLevel = lpMemScript->GetAsNumber();

					info.IsAncient = lpMemScript->GetAsNumber();

					info.IsExcellent = lpMemScript->GetAsNumber();

					info.AnimationID = lpMemScript->GetAsNumber();

					info.Size = lpMemScript->GetAsFloatNumber();

					this->SetInfoBossClass(info);
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
		printf(lpMemScript->GetLastError());
		return 0;
	}

	delete lpMemScript;

	return 1;
}

void cCustomMonsters::SetInfo(CUSTOMMONSTER_DATA info)
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOMMONSTER)
	{
		return;
	}

	this->m_Monsters[info.Index] = info;
}

void cCustomMonsters::SetInfoBossClass(BOSSCLASS_DATA info)
{
	if(info.Index < 0 || info.Index >= MAX_BOSSCLASS)
	{
		return;
	}

	this->m_BossClass[info.Index] = info;
}