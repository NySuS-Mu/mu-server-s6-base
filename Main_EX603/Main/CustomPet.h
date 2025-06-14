#pragma once

struct CUSTOM_PET_INFO
{
	int Index;
	int ItemIndex;
	int IndexInventory;
	int PetType;
	char ModelName[50];
	int FenrrirEffect;
	float Scale_Inve;
	float Scale_Drop;
	float Scale_View;
};


class CCustomPet
{
public:
	CCustomPet();
	virtual ~CCustomPet();
	void Init();
	void Load(CUSTOM_PET_INFO* info);
	int GetInfoByItem(int ItemIndex);
	int GetInfoByItemInventory(int ItemIndex);
	int GetPetType(int ItemIndex); // OK
	int GetInfoPetType(int ItemIndex); // OK
	int GetInfoPetEffect(int ItemIndex); // OK
	float GetScaleInv(int ItemIndex);
	float GetScaleDrop(int ItemIndex);
	float GetScaleView(int ItemIndex);
	bool CheckCustomPetByItem(int ItemIndex);
public:
	std::map<int, CUSTOM_PET_INFO> m_CustomPetInfo;
};

extern CCustomPet g_CustomPet;