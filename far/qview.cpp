/*
qview.cpp

Quick view panel

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
#ifndef __STDIO_H
#include <stdio.h>
#endif
#ifndef __TIME_H
#include <time.h>
#endif
#ifndef __IO_H
#include <io.h>		// chmod
#endif
#ifndef __DOS_H
#include <dos.h>	// FA_*
#endif
#ifndef __STAT_H
#include <sys\stat.h>	// S_IREAD...
#endif
#ifndef __STRING_H
#include <string.h>
#endif
#if !defined(__NEW_H)
#pragma option -p-
#include <new.h>
#pragma option -p.
#endif

#ifndef __FARCONST_HPP__
#include "farconst.hpp"
#endif
#ifndef __FARSTRUCT_HPP__
#include "struct.hpp"
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


static int LastWrapMode=FALSE;

QuickView::QuickView()
{
  Type=QVIEW_PANEL;
  QView=NULL;
  *CurFileName=0;
  *CurFileType=0;
  *TempName=0;
  Directory=0;
}


QuickView::~QuickView()
{
  CloseFile();
}


void QuickView::DisplayObject()
{
  char Title[NM];
  if (QView==NULL && !ProcessingPluginCommand)
    CtrlObject->GetAnotherPanel(this)->UpdateViewPanel();
  if (QView!=NULL)
    QView->SetPosition(X1+1,Y1+1,X2-1,Y2-3);
  Box(X1,Y1,X2,Y2,COL_PANELBOX,DOUBLE_BOX);
  SetScreen(X1+1,Y1+1,X2-1,Y2-1,' ',COL_PANELTEXT);
  SetColor(Focus ? COL_PANELSELECTEDTITLE:COL_PANELTITLE);
  sprintf(Title," %s ",MSG(MQuickViewTitle));
  TruncStr(Title,X2-X1-3);
  if (*Title)
  {
    GotoXY(X1+(X2-X1+1-strlen(Title))/2,Y1);
    Text(Title);
  }
  DrawSeparator(Y2-2);
  SetColor(COL_PANELTEXT);
  GotoXY(X1+1,Y2-1);
  mprintf("%-*.*s",X2-X1-1,X2-X1-1,PointToName(CurFileName));
  if (*CurFileType)
  {
    char TypeText[sizeof(CurFileType)];
    sprintf(TypeText," %s ",CurFileType);
    TruncStr(TypeText,X2-X1-1);
    SetColor(COL_PANELSELECTEDINFO);
    GotoXY(X1+(X2-X1+1-strlen(TypeText))/2,Y2-2);
    Text(TypeText);
  }
  if (Directory)
  {
    char Msg[NM];
    sprintf(Msg,MSG(MQuickViewFolder),CurFileName);
    TruncStr(Msg,X2-X1-4);
    SetColor(COL_PANELTEXT);
    GotoXY(X1+2,Y1+2);
    PrintText(Msg);
    if (Directory==1 || Directory==4)
    {
      GotoXY(X1+2,Y1+4);
      PrintText(MSG(MQuickViewContains));
      GotoXY(X1+2,Y1+6);
      PrintText(MSG(MQuickViewFolders));
      SetColor(COL_PANELSELECTEDTEXT);
      sprintf(Msg,"%d",DirCount);
      PrintText(Msg);
      SetColor(COL_PANELTEXT);
      GotoXY(X1+2,Y1+7);
      PrintText(MSG(MQuickViewFiles));
      SetColor(COL_PANELSELECTEDTEXT);
      sprintf(Msg,"%d",FileCount);
      PrintText(Msg);
      SetColor(COL_PANELTEXT);
      GotoXY(X1+2,Y1+8);
      PrintText(MSG(MQuickViewBytes));
      SetColor(COL_PANELSELECTEDTEXT);
      InsertCommas(FileSize,Msg);
      PrintText(Msg);
      SetColor(COL_PANELTEXT);
      GotoXY(X1+2,Y1+9);
      PrintText(MSG(MQuickViewCompressed));
      SetColor(COL_PANELSELECTEDTEXT);
      InsertCommas(CompressedFileSize,Msg);
      PrintText(Msg);
      if (Directory!=4 && RealFileSize>=CompressedFileSize)
      {
        SetColor(COL_PANELTEXT);
        GotoXY(X1+2,Y1+11);
        PrintText(MSG(MQuickViewCluster));
        SetColor(COL_PANELSELECTEDTEXT);
        InsertCommas(ClusterSize,Msg);
        PrintText(Msg);
        SetColor(COL_PANELTEXT);
        GotoXY(X1+2,Y1+12);
        PrintText(MSG(MQuickViewRealSize));
        SetColor(COL_PANELSELECTEDTEXT);
        InsertCommas(RealFileSize,Msg);
        PrintText(Msg);
        SetColor(COL_PANELTEXT);
        GotoXY(X1+2,Y1+13);
        PrintText(MSG(MQuickViewSlack));
        SetColor(COL_PANELSELECTEDTEXT);
        InsertCommas(RealFileSize-CompressedFileSize,Msg);
        char SlackMsg[100];
        int64 Size1=RealFileSize-CompressedFileSize;
        int64 Size2=RealFileSize;
        while (Size2.HighPart!=0)
        {
          Size1=Size1>>1;
          Size2=Size2>>1;
        }
        sprintf(SlackMsg,"%s (%d%%)",Msg,ToPercent(Size1.LowPart,Size2.LowPart));
        PrintText(SlackMsg);
      }
    }
  }
  else
    if (QView!=NULL)
      QView->Show();
}


int QuickView::ProcessKey(int Key)
{
  if (!IsVisible())
    return(FALSE);
  {
    char ShortcutFolder[NM],PluginModule[NM],PluginFile[NM],PluginData[8192];
    if (GetShortcutFolder(Key,ShortcutFolder,PluginModule,PluginFile,PluginData))
    {
      Panel *AnotherPanel=CtrlObject->GetAnotherPanel(this);
      if (AnotherPanel->GetType()==FILE_PANEL && *PluginModule==0)
      {
        AnotherPanel->SetCurDir(ShortcutFolder,TRUE);
        AnotherPanel->Redraw();
      }
      return(TRUE);
    }
  }
  if (Key==KEY_F3 || Key==KEY_NUMPAD5)
  {
    Panel *AnotherPanel=CtrlObject->GetAnotherPanel(this);
    if (AnotherPanel->GetType()==FILE_PANEL)
      AnotherPanel->ProcessKey(KEY_F3);
    return(TRUE);
  }
  if (QView!=NULL && !Directory && Key>=256)
    return(QView->ProcessKey(Key));
  return(FALSE);
}


int QuickView::ProcessMouse(MOUSE_EVENT_RECORD *MouseEvent)
{
  int RetCode;
  if (!IsVisible())
    return(FALSE);
  if (Panel::PanelProcessMouse(MouseEvent,RetCode))
    return(RetCode);
  SetFocus();
  if (QView!=NULL && !Directory)
    return(QView->ProcessMouse(MouseEvent));
  return(FALSE);
}

#pragma warn -par
void QuickView::Update(int Mode)
{
  if (!EnableUpdate)
    return;
  if (*CurFileName==0)
    CtrlObject->GetAnotherPanel(this)->UpdateViewPanel();
  Redraw();
}
#pragma warn +par


void QuickView::ShowFile(char *FileName,int TempFile,HANDLE hDirPlugin)
{
  char *ExtPtr;
  int FileAttr;
  CloseFile();
  QView=NULL;
  *CurFileName=0;
  if (!IsVisible())
    return;
  if (FileName==NULL)
  {
    ProcessingPluginCommand++;
    Show();
    ProcessingPluginCommand--;
    return;
  }
  QView=new Viewer;
  QView->SetRestoreScreenMode(FALSE);
  QView->SetPosition(X1+1,Y1+1,X2-1,Y2-3);
  QView->SetStatusMode(0);
  QView->EnableHideCursor(0);
  QView->SetWrapMode(LastWrapMode);
  strcpy(CurFileName,FileName);

  if ((ExtPtr=strrchr(CurFileName,'.'))!=NULL)
  {
    char Value[80];
    LONG ValueSize=sizeof(Value);
    if (RegQueryValue(HKEY_CLASSES_ROOT,(LPCTSTR)ExtPtr,(LPTSTR)Value,&ValueSize)==ERROR_SUCCESS)
    {
      ValueSize=sizeof(CurFileType);
      if (RegQueryValue(HKEY_CLASSES_ROOT,Value,(LPTSTR)CurFileType,&ValueSize)!=ERROR_SUCCESS)
        *CurFileType=0;
      CharToOem(CurFileType,CurFileType);
    }
  }
  if (hDirPlugin || (FileAttr=GetFileAttributes(CurFileName))!=-1 && (FileAttr & FA_DIREC))
  {
    if (hDirPlugin)
    {
      int ExitCode=GetPluginDirInfo(hDirPlugin,CurFileName,DirCount,
                   FileCount,FileSize,CompressedFileSize);
      if (ExitCode)
        Directory=4;
      else
        Directory=3;
    }
    else
    {
      int ExitCode=GetDirInfo(MSG(MQuickViewTitle),CurFileName,DirCount,
                   FileCount,FileSize,CompressedFileSize,RealFileSize,
                   ClusterSize,500,TRUE);
      if (ExitCode==1)
        Directory=1;
      else
        if (ExitCode==-1)
          Directory=2;
        else
          Directory=3;
    }
  }
  else
    if (*CurFileName)
      QView->OpenFile(CurFileName);
  if (TempFile)
    ConvertNameToFull(CurFileName,TempName);
  Redraw();
}


void QuickView::CloseFile()
{
  if (QView!=NULL)
  {
    LastWrapMode=QView->GetWrapMode();
    delete QView;
    QView=NULL;
  }
  QViewDelTempName();
  *CurFileType=0;
  Directory=0;
}


void QuickView::QViewDelTempName()
{
  if (*TempName)
  {
    if (QView!=NULL)
    {
      LastWrapMode=QView->GetWrapMode();
      delete QView;
      QView=NULL;
    }
    chmod(TempName,S_IREAD|S_IWRITE);
    remove(TempName);
    *PointToName(TempName)=0;
    RemoveDirectory(TempName);
    *TempName=0;
  }
}


void QuickView::PrintText(char *Str)
{
  if (WhereY()>Y2-3 || WhereX()>X2-2)
    return;
  mprintf("%.*s",X2-2-WhereX()+1,Str);
}


int QuickView::UpdateIfChanged()
{
  if (IsVisible() && *CurFileName && Directory==2)
  {
    char ViewName[NM];
    strcpy(ViewName,CurFileName);
    ShowFile(ViewName,*TempName,NULL);
    return(TRUE);
  }
  return(FALSE);
}

