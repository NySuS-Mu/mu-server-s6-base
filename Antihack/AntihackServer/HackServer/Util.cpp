#include "stdafx.h"
#include "Util.h"
#include "ClientManager.h"

int gClientCount = 0;

void copy_to_clipboard(std::string text)
{
	EmptyClipboard(); //������� �����
	HGLOBAL hgBuffer = GlobalAlloc(GMEM_DDESHARE, 512);//�������� ������
	char* chBuffer = (char*)GlobalLock(hgBuffer); //��������� ������
	
	strcpy(chBuffer, text.c_str());
	GlobalUnlock(hgBuffer);//������������ ������
	SetClipboardData(CF_TEXT, hgBuffer);//�������� ����� � ����� ������
	CloseClipboard(); //��������� ����� ������
}

bool CheckListBox(HWND hDlg, int Item, char* text)
{
	SetClassLong(hDlg, GCL_HICON, (long)LoadIcon(nullptr, IDI_APPLICATION));
	HWND hlst = GetDlgItem(hDlg, Item);

	int count = SendMessage(hlst, LB_GETCOUNT, 0, 0);

	char buff[100];

	for (int i = 0; i < count; i++)
	{
		SendMessage(hlst, LB_GETTEXT, (WPARAM)i, (LPARAM)buff);

		const char* SEPARATORS = " ";
		char* ptr = 0;       //���������
		ptr = strtok(buff, SEPARATORS); //�������� ������ ����� �� ������
		ptr = strtok(0, SEPARATORS);   //��������� �����

		if (!strcmp(ptr, text))
		{
			return false;
		}
		ptr = nullptr;
	}

	return true;
}

int get_index_of_symbol(char* arr, char symbol)
{
	for (int i = 0; i < strlen(arr); i++)
	{
		if (arr[i] == symbol)
			return i;
	}

	return -1;
}

int get_count_hwid_by_ip(char* ip_addr)
{
	int counter = 0;

	for (int n = 0; n < MAX_CLIENT; n++)
	{
		if (gClientManager[n].CheckState() != 0)
		{
			if (!strcmp(ip_addr, gClientManager[n].m_IpAddr))
			{
				counter++;
			}
		}
	}

	return counter;
}

bool get_listbox_text(HWND control, char* row_text)
{
	char text[128];
	int selected_index = (int)SendMessage(control, LB_GETCURSEL, 0, 0);

	if (selected_index != LB_ERR)
	{
		SendMessage(control, LB_GETTEXT, selected_index, (LPARAM)text);

		strcpy(row_text, &text[get_index_of_symbol(text, ' ') + 1]);
		return true;
	}

	return false;
}

bool isNumber(const string& str)
{
	// `std::find_first_not_of` searches the string for the first character
	// that does not match any of the characters specified in its arguments
	return !str.empty() &&
		(str.find_first_not_of("[0123456789]") == std::string::npos);
}

// Function to split string `str` using a given delimiter
vector<string> split(const string& str, char delim)
{
	auto i = 0;
	vector<string> list;

	auto pos = str.find(delim);

	while (pos != string::npos)
	{
		list.push_back(str.substr(i, pos - i));
		i = ++pos;
		pos = str.find(delim, pos);
	}

	list.push_back(str.substr(i, str.length()));

	return list;
}

// Function to validate an IP address
bool validateIP(string ip)
{
	// split the string into tokens
	vector<string> list = split(ip, '.');

	// if the token size is not equal to four
	if (list.size() != 4) {
		return false;
	}

	// validate each token
   // for (string str: list)
	for (int i = 0; i < list.size(); i++)
	{
		// verify that the string is a number or not, and the numbers
		// are in the valid range
		if (!isNumber(list[i]) || stoi(list[i]) > 255 || stoi(list[i]) < 0) {
			return false;
		}
	}

	return true;
}

BOOL WINAPI AddListViewItems(HWND hWndLV, int colNum, int textMaxLen, char** item)
{
    int iLastIndex = ListView_GetItemCount(hWndLV);
 
    LVITEM lvi;
    lvi.mask = LVIF_TEXT;
    lvi.cchTextMax = textMaxLen;
    lvi.iItem = iLastIndex;
    lvi.pszText = item[0];
    lvi.iSubItem = 0;
 
    if (ListView_InsertItem(hWndLV, &lvi) == -1)
        return FALSE;
    for (int i = 1; i < colNum; i++)
        ListView_SetItemText(hWndLV, iLastIndex, i, item[i]);
 
    return TRUE;
}

void MsgBox(char* message,...) // OK
{
	char buff[256];

	memset(buff,0,sizeof(buff));

	va_list arg;
	va_start(arg,message);
	vsprintf_s(buff,message,arg);
	va_end(arg);

	MessageBox(0,buff,"Error",MB_OK | MB_ICONINFORMATION);
}

void ErrorMessageBox(char* message,...) // OK
{
	char buff[256];

	memset(buff,0,sizeof(buff));

	va_list arg;
	va_start(arg,message);
	vsprintf_s(buff,message,arg);
	va_end(arg);

	MessageBox(0,buff,"Error",MB_OK | MB_ICONERROR);

	while(true)
	{
		TerminateProcess(GetCurrentProcess(),0);
		CRASH_APPLICATION_MACRO
	}
}

void LogAdd(eLogColor color,char* text,...) // OK
{
	tm today;
	time_t ltime;
	time(&ltime);

	if(localtime_s(&today,&ltime) != 0)
	{
		return;
	}

	char time[32];

	if(asctime_s(time,sizeof(time),&today) != 0)
	{
		return;
	}

	char temp[1024];

	va_list arg;
	va_start(arg,text);
	vsprintf_s(temp,text,arg);
	va_end(arg);

	char log[1024];

	wsprintf(log,"%.8s %s",&time[11],temp);

	gServerDisplayer.LogAddText(color,log,strlen(log));
}

void TimeoutProc() // OK
{
	for(int n=0;n < MAX_CLIENT;n++)
	{
		if(gClientManager[n].CheckState() != 0)
		{
			if(gClientManager[n].CheckOnlineTime() == 0)
			{
				gSocketManager.Disconnect(n);
			}
		}
	}
}

int GetUserCount() // OK
{
	int count = 0;

	for(int n=0;n < MAX_CLIENT;n++)
	{
		if(gClientManager[n].CheckState() != 0)
		{
			count++;
		}
	}

	return count;
}

char* GetIpByIndex(int aIndex)
{
	for(int n=0;n < MAX_CLIENT;n++)
	{
		if(gClientManager[n].CheckState() != 0)
		{
			if (gClientManager[n].m_index == aIndex)
			{
				return gClientManager[n].m_IpAddr;
			}
		}
	}

	return nullptr;
}

char* GetHwidByIndex(int aIndex)
{
	for(int n=0;n < MAX_CLIENT;n++)
	{
		if(gClientManager[n].CheckState() != 0)
		{
			if (gClientManager[n].m_index == aIndex)
			{
				return gClientManager[n].m_HardwareId;
			}
		}
	}
	
	return nullptr;
}

int GetIndexByIpAndHwid(char* IP, char* HWID)
{
	for(int n=0;n < MAX_CLIENT;n++)
	{
		if(gClientManager[n].CheckState() != 0)
		{
			if (!strcmp(gClientManager[n].m_IpAddr,IP) && !strcmp(gClientManager[n].m_HardwareId,HWID))
			{
				return gClientManager[n].m_index;
			}
		}
	}

	return -1;
}

bool GetSelectedListBoxItem(HWND hDlg, int Item, char* text)
{
	//char text[64]={0};
	HWND hlst;
	SetClassLong(hDlg, GCL_HICON, (long)LoadIcon(0, IDI_APPLICATION));
	hlst = GetDlgItem(hDlg, Item);

	int count = SendMessage(hlst, LB_GETCOUNT, 0, 0);
	int iSelected = -1;

	for (int i = 0; i < count; i++)
	{
		if (SendMessage(hlst, LB_GETSEL, i, 0) > 0)
		{
			iSelected = i;
			break;
		}
	}

	if (iSelected != -1)
	{
		SendMessage(hlst, LB_GETTEXT, (WPARAM)iSelected , (LPARAM)text);

		return 1;
	}

	return 0;
}

int GetFreeClientIndex() // OK
{
	int index = -1;
	int count = gClientCount;

	if(SearchFreeClientIndex(&index,0,MAX_CLIENT,10000) != 0)
	{
		return index;
	}

	for(int n=0;n < MAX_CLIENT;n++)
	{
		if(gClientManager[count].CheckState() == 0)
		{
			return count;
		}
		else
		{
			count = (((++count)>=MAX_CLIENT)?0:count);
		}
	}

	return -1;
}

int SearchFreeClientIndex(int* index,int MinIndex,int MaxIndex,DWORD MinTime) // OK
{
	DWORD CurOnlineTime = 0;
	DWORD MaxOnlineTime = 0;

	for(int n=MinIndex;n < MaxIndex;n++)
	{
		if(gClientManager[n].CheckState() == 0 && gClientManager[n].CheckAlloc() != 0)
		{
			if((CurOnlineTime=(GetTickCount()-gClientManager[n].m_OnlineTime)) > MinTime && CurOnlineTime > MaxOnlineTime)
			{
				(*index) = n;
				MaxOnlineTime = CurOnlineTime;
			}
		}
	}

	return (((*index)==-1)?0:1);
}

void PacketDecryptData(BYTE* lpMsg,int size,BYTE key) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]+key)^0xA0;
	}
}

void PacketEncryptData(BYTE* lpMsg,int size,BYTE key) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]^0xA0)-key;
	}
}

void GetHardwareId(char* hid)  //OK
{
	DWORD VolumeSerialNumber;

	if(GetVolumeInformation("C:\\",0,0,&VolumeSerialNumber,0,0,0,0) == 0)
	{
		return;
	}

	UUID uuid;

	UuidCreateSequential(&uuid);

	SYSTEM_INFO SystemInfo;

	GetSystemInfo(&SystemInfo);

	DWORD ComputerHardwareId1 = VolumeSerialNumber ^ 0x12B586FE;

	DWORD ComputerHardwareId2 = *(DWORD*)(&uuid.Data4[2]) ^ 0x5D78A569;

	DWORD ComputerHardwareId3 = ((*(WORD*)(&uuid.Data4[6]) & 0xFFFF) | (SystemInfo.wProcessorArchitecture << 16)) ^ 0xF45BC123;

	DWORD ComputerHardwareId4 = ((SystemInfo.wProcessorLevel & 0xFFFF) | (SystemInfo.wProcessorRevision << 16)) ^ 0xB542D8E1;

	wsprintf(hid,"%08X-%08X-%08X-%08X",ComputerHardwareId1,ComputerHardwareId2,ComputerHardwareId3,ComputerHardwareId4);
}

DWORD GetCurrentVersion()
{
	char Temp[10];
	sprintf_s(Temp,"%s",HACKSERVER_VERSION);
	strcpy_s(Temp,RemoveCharacter(Temp,'.'));
	return atoi(Temp);
}

DWORD ConvertHackVersion(char* version)
{
	char Temp[10];
	sprintf_s(Temp,"%s",version);
	strcpy_s(Temp,RemoveCharacter(Temp,'.'));
	return atoi(Temp);
}

char* RemoveCharacter(char* Input, char Character) //OK
{
	for(DWORD i=0; i<=strlen(Input); i++)
	{
		if(Input[i] == Character)
		{
			for(DWORD n=i; n<=strlen(Input); n++)
			{
				Input[n] = Input[n+1];
			}
		}
	}
	return Input;
}

void AuthenticateError() //OK
{
	MessageBox(0,"Authorization failed.\n\nVisit: muemu.pl","Error",MB_ICONSTOP|MB_OK);

	while(true)
	{
		TerminateProcess(GetCurrentProcess(),0);
		CRASH_APPLICATION_MACRO
	}
}
