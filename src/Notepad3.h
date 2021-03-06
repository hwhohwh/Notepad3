﻿/******************************************************************************
*                                                                             *
*                                                                             *
* Notepad3                                                                    *
*                                                                             *
* Notepad3.h                                                                  *
*   Global definitions and declarations                                       *
*   Based on code from Notepad2, (c) Florian Balmer 1996-2011                 *
*                                                                             *
*                                                  (c) Rizonesoft 2008-2019   *
*                                                    https://rizonesoft.com   *
*                                                                             *
*                                                                             *
*******************************************************************************/
#pragma once
#ifndef _NP3_NOTEPAD3_H_
#define _NP3_NOTEPAD3_H_

#include "TypeDefs.h"

//==== Main Window ============================================================

#define ONLINE_HELP_WEBSITE L"https://www.rizonesoft.com/documents/notepad3/"

//==== Data Type for WM_COPYDATA ==============================================
#define DATA_NOTEPAD3_PARAMS 0xFB10
typedef struct np3params {

  int   flagFileSpecified;
  int   flagChangeNotify;
  int   flagLexerSpecified;
  int   iInitialLexer;
  int   flagQuietCreate;
  int   flagJumpTo;
  int   iInitialLine;
  int   iInitialColumn;
  int   iSrcEncoding;
  int   flagSetEncoding;
  int   flagSetEOLMode;
  int   flagTitleExcerpt;
  WCHAR wchData;

} np3params, *LPnp3params;


typedef struct _undoSel
{
  int selMode_undo;
  DocPos anchorPos_undo;
  DocPos curPos_undo;
  DocPos anchorVS_undo;
  DocPos curVS_undo;

  int selMode_redo;
  DocPos anchorPos_redo;
  DocPos curPos_redo;
  DocPos anchorVS_redo;
  DocPos curVS_redo;
} 
UndoRedoSelection_t;

#define INIT_UNDOREDOSEL  { SC_SEL_STREAM, (DocPos)-1, (DocPos)-1, 0, 0, SC_SEL_STREAM, (DocPos)-1, (DocPos)-1, 0, 0 }


typedef enum {
  UNDO = true,
  REDO = false
} DoAction;


//==== Toolbar Style ==========================================================
#define NP3_WS_TOOLBAR (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | \
                        TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_ALTDRAG | TBSTYLE_LIST | \
                        CCS_NODIVIDER | CCS_NOPARENTALIGN | CCS_ADJUSTABLE)


//==== ReBar Style ============================================================
#define NP3_WS_REBAR (WS_CHILD | WS_CLIPCHILDREN | WS_BORDER | RBS_VARHEIGHT | \
                      RBS_BANDBORDERS | CCS_NODIVIDER | CCS_NOPARENTALIGN)


//==== Ids ====================================================================
#define IDC_STATUSBAR    0xFB00
#define IDC_TOOLBAR      0xFB01
#define IDC_REBAR        0xFB02
#define IDC_EDIT         0xFB03
#define IDC_EDITFRAME    0xFB04
#define IDC_FILENAME     0xFB05
#define IDC_REUSELOCK    0xFB06



//==== Change Notifications ===================================================
#define ID_WATCHTIMER 0xA000
#define WM_CHANGENOTIFY WM_USER+1
//#define WM_CHANGENOTIFYCLEAR WM_USER+2


//==== Callback Message from System Tray ======================================
#define WM_TRAYMESSAGE WM_USER


//==== Paste Board Timer ======================================================
#define ID_PASTEBOARDTIMER 0xA001


//==== Reuse Window Lock Timeout ==============================================
#define REUSEWINDOWLOCKTIMEOUT 1000


//==== Function Declarations ==================================================
bool InitApplication(HINSTANCE hInstance);
HWND InitInstance(HINSTANCE hInstance, LPCWSTR pszCmdLine, int nCmdShow);
void BeginWaitCursor(LPCWSTR text);
void EndWaitCursor();
bool ActivatePrevInst();
bool RelaunchMultiInst();
bool RelaunchElevated(LPWSTR lpArgs);
void SnapToWinInfoPos(HWND hwnd, const WININFO* pWinInfo, bool bFullWorkArea);
void ShowNotifyIcon(HWND hwnd, bool bAdd);
void SetNotifyIconTitle(HWND hwnd);
void InstallFileWatching(LPCWSTR lpszFile);
void CALLBACK WatchTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK PasteBoardTimer(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


void LoadSettings();
void SaveSettings(bool);
void ParseCommandLine();
void LoadFlags();
int  FindIniFile();
int  TestIniFile();
int  CreateIniFile();
int  CreateIniFileEx(LPCWSTR lpszIniFile);


void MarkAllOccurrences(int delay, bool bForceClear);
void UpdateToolbar();
void UpdateStatusbar(bool);
void UpdateMarginWidth();
void UpdateSettingsCmds();
void UpdateVisibleUrlHotspot(int delay);
void UpdateUI();

void UndoRedoRecordingStart();
void UndoRedoRecordingStop();
int  BeginUndoAction();
void EndUndoAction(int token);
void RestoreAction(int token, DoAction doAct);

#define _BEGIN_UNDO_ACTION_  { int const _token_ = BeginUndoAction(); __try {  
#define _END_UNDO_ACTION_    } __finally { EndUndoAction(_token_); } }


void OpenHotSpotURL(DocPos position, bool bForceBrowser);

bool IsFindPatternEmpty();
void SetFindPattern(LPCWSTR wchFindPattern);
void SetFindPatternMB(LPCSTR chFindPattern);
void GetFindPattern(LPWSTR wchFindPattern, size_t bufferSize);
void GetFindPatternMB(LPSTR chFindPattern, size_t bufferSize);

bool FileIO(bool,LPWSTR pszFileName,bool,bool,int* ienc,int* ieol,bool*,bool*,bool*,bool*,bool);
bool FileLoad(bool,bool,bool,bool,bool,LPCWSTR lpszFile);
bool FileRevert(LPCWSTR szFileName,bool);
bool FileSave(bool,bool,bool,bool);
bool OpenFileDlg(HWND hwnd,LPWSTR lpstrFile,int cchFile,LPCWSTR lpstrInitialDir);
bool SaveFileDlg(HWND hwnd,LPWSTR lpstrFile,int cchFile,LPCWSTR lpstrInitialDir);

void CreateBars(HWND hwnd, HINSTANCE hInstance);

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);
LRESULT MsgCreate(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgEndSession(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);
LRESULT MsgThemeChanged(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgDPIChanged(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgSize(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgDropFiles(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgCopyData(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgContextMenu(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);
LRESULT MsgInitMenu(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgNotify(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgChangeNotify(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgTrayMessage(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT MsgCommand(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

LRESULT MsgSysCommand(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);


void IgnoreNotifyChangeEvent();
void ObserveNotifyChangeEvent();
bool CheckNotifyChangeEvent();
#define _IGNORE_NOTIFY_CHANGE_     __try { IgnoreNotifyChangeEvent(); 
#define _OBSERVE_NOTIFY_CHANGE_  } __finally { ObserveNotifyChangeEvent(); }


#endif //_NP3_NOTEPAD3_H_
///   End of Notepad3.h   ///
