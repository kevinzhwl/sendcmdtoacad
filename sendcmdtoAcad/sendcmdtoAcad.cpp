// sendcmdtoAcad.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <tchar.h>
#include <Windows.h>
#include <atlstr.h>
#include <assert.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    COPYDATASTRUCT* pCmdMsg = (COPYDATASTRUCT*)lParam;

    const int MAX_LEN = 256;
    TCHAR caption[MAX_LEN];
    
	//ASSERT(hwnd!=NULL);
    
	::GetWindowText(hwnd,caption,MAX_LEN);
	caption[7] = TEXT('\0');
    if (!_tcscmp(caption,_T("AutoCAD")))
    {
        ::SendMessage(hwnd, WM_COPYDATA, NULL, (LPARAM)pCmdMsg);
    }
    return TRUE;
}

void SendCmdToAcad(LPCTSTR cmd)
{
    COPYDATASTRUCT cmdMsg;
    cmdMsg.dwData = (DWORD)1;
    cmdMsg.cbData = (DWORD)(_tcslen(cmd) + 1) * sizeof(TCHAR);
    cmdMsg.lpData = (PVOID)cmd;
    ::EnumDesktopWindows(NULL,EnumWindowsProc,(LPARAM)&cmdMsg);
}

void printUsage()
{
    const TCHAR  cmd_usage[]=
    TEXT("\n")\
    TEXT("=================================================\n")\
    TEXT("| sendcmdtoacad \n")\
    TEXT("| : is send acad-cmd to Acad Application to execute\n")\
    TEXT("| example:\n")\
    TEXT("| sendcmdtoacad \"arx l demo.arx\"\n")\
    TEXT("| sendcmdtoacad \"arx u demo.arx\"\n")\
    TEXT("| sendcmdtoacad \"hxtunload c:\\demo.arx\"\n")\
    TEXT("=================================================\n")\
    TEXT("\n");

    _tprintf(TEXT("%s"),cmd_usage);
}


int _tmain(int argc, TCHAR* argv[])
{
    if (argc>1)
    {
		const int MAX_CMD_LENTH = 2 * _MAX_PATH;
		TCHAR acadCmd[MAX_CMD_LENTH] = {'\0'};
		_tcscpy_s(acadCmd,MAX_CMD_LENTH,argv[1]);
		_tcscat_s(acadCmd,_T("\r"));
        
		SendCmdToAcad(acadCmd);
		_tprintf(TEXT("%s"),TEXT("Acad-cmd is sent."));
    }
	else
	{
		printUsage();
	}

    return 0;
}

