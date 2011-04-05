#include "stdafx.h"
#include ".\mainwnd.h"


CMainWnd::CMainWnd(void) : CKuiDialogImpl<CMainWnd>( "IDR_DLG_MAIN" )
, m_nCurProgress( 30 )
{
	m_rtProgress.SetRect( 50,200,250,210 );
}

CMainWnd::~CMainWnd(void)
{
}

LRESULT CMainWnd::OnInitDialog( HWND hDlg, LPARAM lParam )
{
	SetTimer( 1, 80 );
	return TRUE;
}

void CMainWnd::OnDestroy()
{
	KillTimer( 1 );
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

void CMainWnd::OnNotify( UINT nID, LPCSTR pClassName )
{
	CString str;
	str.Format( _T("Item Notify.ID:%d, Item Type:%s"), nID, pClassName );
	SetItemText( 2, str );
}

void CMainWnd::OnAdd()
{
	m_nCurProgress += 10;
	if( m_nCurProgress>100 )
		m_nCurProgress = 0;
	SetItemIntAttribute( 8, "value", m_nCurProgress );

}

void CMainWnd::OnDec()
{
	m_nCurProgress -= 10;
	if( m_nCurProgress<0 )
		m_nCurProgress = 100;
	SetItemIntAttribute( 8, "value", m_nCurProgress );
}

void CMainWnd::OnTimer(UINT_PTR nIDEvent)
{
    static int nFrame = 0;
    SetItemIntAttribute( 11, "sub", nFrame++);
    if (nFrame > 5)
        nFrame = 0;
}

void CMainWnd::OnShowProgress()
{
	SetItemVisible( 8, !IsItemVisible(8) );

	SetItemText( 12, IsItemVisible(8)?_T("隐藏进度条") : _T("显示进度条") );
}

void CMainWnd::WindowMoveLeft()
{
	CRect rt;
	GetWindowRect( &rt );
	rt.OffsetRect( -10, 0 );
	MoveWindow( &rt );
}

void CMainWnd::WindowMoveRight()
{
	CRect rt;
	GetWindowRect( &rt );
	rt.OffsetRect( 10, 0 );
	MoveWindow( &rt );
}

void CMainWnd::ProgressMoveLeft()
{
	m_rtProgress.OffsetRect( -10, 0 );
	CString strPos;
	strPos.Format( _T("%d,%d,%d,%d"), m_rtProgress.left, m_rtProgress.top, m_rtProgress.right, m_rtProgress.bottom );
	SetItemAttribute( 8, _T("pos"), strPos );
}

void CMainWnd::ProgressMoveRight()
{
	m_rtProgress.OffsetRect( 10, 0 );
	CString strPos;
	strPos.Format( _T("%d,%d,%d,%d"), m_rtProgress.left, m_rtProgress.top, m_rtProgress.right, m_rtProgress.bottom );
	SetItemAttribute( 8, _T("pos"), strPos );
}
