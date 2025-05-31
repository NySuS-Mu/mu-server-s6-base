#pragma once

#define WD_81KARUTAN2		81
#define WD_ENDMAP			150
#define SERVER_LIST_SCENE   0
#define NON_SCENE			0
#define WEBZEN_SCENE		1
#define LOG_IN_SCENE		2
#define LOADING_SCENE		3
#define CHARACTER_SCENE		4
#define MAIN_SCENE			5
#define Hero				*(DWORD*)0x007BC4F04


#define SceneFlag				*(int*)0x0E609E8
#define PlayMp3					((void(__cdecl*)(const char *Name, BOOL bEnforce))0x004CF050)
#define StopMp3					((void(__cdecl*)(char *Name, BOOL bEnforce))0x004CF000)
#define MainScene				((void(__cdecl*)(HDC hDC))0x004D9CF0)

#define pGetMapName				((char*(__cdecl*)(int iMap)) 0x005D2C10)

#define World										*(DWORD*)0xE61E18
#define IsStrifeMap									((char(__cdecl*)( int a3)) 0x005D3030)
#define DeleteBitmap								((void(__cdecl*)(GLuint uiTextureIndex, bool bForce))0x007724E0)
#define LoadBitmapA									((int(__cdecl*)(char * Folder, int Code, int Arg3, int Arg4, int Arg5, int Arg6)) 0x00772330)
#define GlobalText									((char*(__thiscall*)(LPVOID thisa, int LineNumber)) 0x00402320)
#define GlobalLine									(LPVOID)0x008128ADC



typedef struct
{
	int world;
	int LineText;
	char MapName[30];
	char lpszMp3[30];
}PathMap;

typedef std::map<int, std::string> ImgPathMap;
typedef std::map<int, PathMap> listMap;

class CUIMapName
{
public:
	enum SHOW_STATE { HIDE, FADEIN, SHOW, FADEOUT };

	void Load();
	char* GetNameMap(int world);
	PathMap* GetMapInfo(int world);
	void OpenScritp(PathMap* thisa);

	static void __thiscall InitImgPathMap(int* thisa);
	static void __thiscall ShowMapName(int thisa);

	listMap MapPath;
};
extern CUIMapName g_pUIMapName;