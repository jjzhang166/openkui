#include "stdafx.h"
#include ".\mainwnd.h"


CMainWnd::CMainWnd(void) : CKuiDialogImpl<CMainWnd>( "IDR_DLG_MAIN" )
{
}

CMainWnd::~CMainWnd(void)
{
}

void CMainWnd::OnDestroy()
{
    PostQuitMessage(0);
}


void CMainWnd::OnBkBtnMax()
{
	if (WS_MAXIMIZE == (GetStyle() & WS_MAXIMIZE))
	{
		SendMessage(WM_SYSCOMMAND, SC_RESTORE | HTCAPTION, 0);
	}
	else
	{
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE | HTCAPTION, 0);
	}
}

void CMainWnd::OnBkBtnMin()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE | HTCAPTION, 0);
}

void CMainWnd::OnBkBtnClose()
{
	DestroyWindow();
}