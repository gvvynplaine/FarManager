/*
plist.cpp

���᮪ ����ᮢ (Ctrl-W)

*/

/* Revision: 1.00 25.06.2000 $ */

/*
Modify:
  25.06.2000 SVS
    ! �����⮢�� Master Copy
    ! �뤥����� � ����⢥ ᠬ����⥫쭮�� �����
*/

#define STRICT

#if !defined(_INC_WINDOWS) && !defined(_WINDOWS_)
#include <windows.h>
#endif
#ifndef __DOS_H
#include <dos.h>	// FA_*
#endif
#ifndef __DIR_H
#include <dir.h>	// chdir
#endif

#ifndef __FARCONST_HPP__
#include "farconst.hpp"
#endif
#ifndef __FARLANG_HPP__
#include "lang.hpp"
#endif
#ifndef __KEYS_HPP__
#include "keys.hpp"
#endif
#ifndef __COLOROS_HPP__
#include "colors.hpp"
#endif
#ifndef __FARSTRUCT_HPP__
#include "struct.hpp"
#endif
#ifndef __PLUGIN_HPP__
#include "plugin.hpp"
#endif
#ifndef __CLASSES_HPP__
#include "classes.hpp"
#endif
#ifndef __FARFUNC_HPP__
#include "fn.hpp"
#endif
#ifndef __FARGLOBAL_HPP__
#include "global.hpp"
#endif



static BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam);
static BOOL KillProcess(DWORD dwPID);

void ShowProcessList()
{
  VMenu ProcList(MSG(MProcessListTitle),NULL,0,ScrY-4);
  ProcList.SetFlags(0);
  ProcList.SetHelp("TaskList");
  ProcList.SetPosition(-1,-1,0,0);
  if (!EnumWindows(EnumWindowsProc,(LPARAM)&ProcList))
    return;
  ProcList.AssignHighlights(FALSE);
  ProcList.Show();

  while (!ProcList.Done())
  {
    int Key=ProcList.ReadInput();
    switch(Key)
    {
      case KEY_DEL:
        {
          char HwndText[30];
          if (ProcList.GetUserData(HwndText,sizeof(HwndText)))
          {
            HWND ProcWnd=(HWND)atoi(HwndText);
            if (ProcWnd!=NULL)
            {
              char WinTitle[512];
              GetWindowText(ProcWnd,WinTitle,sizeof(WinTitle));
              CharToOem(WinTitle,WinTitle);
              DWORD ProcID;
              GetWindowThreadProcessId(ProcWnd,&ProcID);
              if (Message(MSG_WARNING,2,MSG(MKillProcessTitle),MSG(MAskKillProcess),
                          WinTitle,MSG(MKillProcessWarning),MSG(MKillProcessKill),MSG(MCancel))==0)
                if (KillProcess(ProcID))
                {
                  Sleep(500);
                  ProcList.Hide();
                  ShowProcessList();
                  return;
                }
                else
                  Message(MSG_WARNING|MSG_ERRORTYPE,1,MSG(MKillProcessTitle),MSG(MCannotKillProcess),MSG(MOk));
            }
          }
        }
        break;
      default:
        ProcList.ProcessInput();
        break;
    }
  }
  if (ProcList.GetExitCode()>=0)
  {
    char HwndText[30];
    if (ProcList.GetUserData(HwndText,sizeof(HwndText)))
    {
      HWND ProcWnd=(HWND)atoi(HwndText);
      if (ProcWnd!=NULL)
      {
        SetForegroundWindow(ProcWnd);

        WINDOWPLACEMENT wp;
        wp.length=sizeof(wp);
        if (!GetWindowPlacement(ProcWnd,&wp) || wp.showCmd!=SW_SHOWMAXIMIZED)
          ShowWindowAsync(ProcWnd,SW_RESTORE);
      }
    }
  }
}


BOOL KillProcess(DWORD dwPID)
{
  HANDLE hProcess;
  BOOL bRet;
  hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,dwPID);
  if (hProcess!=NULL)
  {
    bRet=TerminateProcess(hProcess,0xFFFFFFFF);
    if (bRet)
      WaitForSingleObject(hProcess,5000);
    CloseHandle(hProcess);
  }
  else
    bRet=FALSE;
  return(bRet);
}


BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam)
{
  VMenu *ProcList=(VMenu *)lParam;
  if (IsWindowVisible(hwnd) ||
      IsIconic(hwnd) && (GetWindowLong(hwnd,GWL_STYLE) & WS_DISABLED)==0)
  {
    char Title[256];
    GetWindowText(hwnd,Title,sizeof(Title));
    if (*Title)
    {
      struct MenuItem ListItem;
      ListItem.Checked=ListItem.Separator=ListItem.Selected=0;
      TruncStr(Title,sizeof(ListItem.Name)-1);
      sprintf(ListItem.Name,"%-25s",Title);
      CharToOem(ListItem.Name,ListItem.Name);
      sprintf(ListItem.UserData,"%d",(DWORD)hwnd);
      ListItem.UserDataSize=strlen(ListItem.UserData)+1;
      ProcList->AddItem(&ListItem);
    }
  }
  return(TRUE);
}
