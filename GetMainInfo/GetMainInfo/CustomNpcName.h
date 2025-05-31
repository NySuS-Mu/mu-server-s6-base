#pragma once

struct NPCNAME_DATA
{
	int Index;
	int NPCId;
	int Map;
	int X;
	int Y;
	char Name[25];
};

class cNPCName
{
public:
	cNPCName();
	virtual ~cNPCName();
	void Init();
	bool Load(char * path);
	void SetInfo(NPCNAME_DATA info);
public:
	NPCNAME_DATA m_CustomNpcName[MAX_CUSTOM_NPCNAME];
}; extern cNPCName gNPCName;