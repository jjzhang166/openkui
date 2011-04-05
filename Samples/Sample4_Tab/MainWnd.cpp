/*
作者： bill
日期： 2011-03-24
功能： Tab控件使用例子
*/

#include "stdafx.h"
#include ".\mainwnd.h"
CMainWnd *g_pMainWnd = NULL;

CMainWnd::CMainWnd(void) : CKuiDialogImpl<CMainWnd>( "IDR_DLG_MAIN" )
{
	g_pMainWnd = this;
}

CMainWnd::~CMainWnd(void)
{
}

LRESULT CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	return TRUE;
}

LRESULT CMainWnd::OnInitDialog( HWND hDlg, LPARAM lParam )
{
	DWORD dwStyle = WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_OWNERDRAWFIXED;
        
	if( m_ctlListCtrl.Create( GetRichWnd(),  NULL, NULL, dwStyle, 0, 101 ) )
	{
		DWORD dwExStyle = LVS_EX_FULLROWSELECT;
        dwExStyle |= m_ctlListCtrl.GetExtendedListViewStyle();
		
        m_ctlListCtrl.SetExtendedListViewStyle(dwExStyle);

		m_ctlListCtrl.InsertColumn( 0, _T("标题一"), LVCFMT_LEFT, 100);
		m_ctlListCtrl.InsertColumn( 1, _T("标题二"), LVCFMT_LEFT, 200);
		m_ctlListCtrl.InsertColumn( 2, _T("标题三"), LVCFMT_LEFT, 300);
		

		m_ctlListCtrl.InsertItem( 0, _T("项目一") );
		m_ctlListCtrl.InsertItem( 1, _T("项目二") );
		m_ctlListCtrl.InsertItem( 2, _T("项目三") );

		m_ctlListCtrl.SetItemText( 0, 1, _T("第二列") );
		m_ctlListCtrl.SetItemText( 0, 2, _T("第三列") );
		

		m_ctlListCtrl.Init();
	}

	if( !m_SnakeGame.Create( GetRichWnd(),  NULL, NULL, WS_CHILD, 0, 301 ) )
	{
		CKuiMsgBox::Show( _T("无法初始化游戏") );
	}
	else
		m_SnakeGame.OnInitDialog( m_SnakeGame.m_hWnd, 0 );
	if( !m_ctlWeb.Create( GetViewHWND(), 401, FALSE, RGB(0xFB, 0xFC, 0xFD) ) )
	{
		CKuiMsgBox::Show( _T("无法初始化网页") );
	}
	else
	{
		m_ctlWeb.Show2( _T("http://www.baidu.com/"), _T("about:blank") );
	}
	if( !m_ctlTree.Create( GetViewHWND(), 501 ) )
	{
		CKuiMsgBox::Show( _T("无法初始化树控件") );
	}
	else
	{
		HTREEITEM hItem = m_ctlTree.InsertItem( _T("全选集"), NULL, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		m_ctlTree.InsertItem( _T("下属项目1"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		m_ctlTree.InsertItem( _T("下属项目2"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		m_ctlTree.InsertItem( _T("下属项目3"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		m_ctlTree.InsertItem( _T("下属项目4"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		m_ctlTree.InsertItem( _T("下属项目5"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );

		hItem = m_ctlTree.InsertItem( _T("半选集"), NULL, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		m_ctlTree.InsertItem( _T("下属项目1"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		m_ctlTree.InsertItem( _T("下属项目2"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		m_ctlTree.InsertItem( _T("下属项目3"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		m_ctlTree.InsertItem( _T("下属项目4"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		m_ctlTree.InsertItem( _T("下属项目5"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );

		hItem = m_ctlTree.InsertItem( _T("全非选集"), NULL, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		m_ctlTree.InsertItem( _T("下属项目1"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		m_ctlTree.InsertItem( _T("下属项目2"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		m_ctlTree.InsertItem( _T("下属项目3"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		m_ctlTree.InsertItem( _T("下属项目4"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		m_ctlTree.InsertItem( _T("下属项目5"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
	}

	CenterWindow();
	return TRUE;
}

void CMainWnd::OnDestroy()
{
    PostQuitMessage(0);
}


void CMainWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	::OnKeyDown( nChar, 0 );
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

void CMainWnd::OnSysCommand(WPARAM wParam, CPoint pt )
{
	SetMsgHandled(FALSE);

	switch (wParam & 0xFFF0)
	{
	case SC_CLOSE:
		SetMsgHandled(TRUE);
		DestroyWindow();
		break;
	case SC_RESTORE:
		{
			DWORD dwStyle = GetStyle();
			if (WS_MINIMIZE == (dwStyle & WS_MINIMIZE))
				break;

			if (WS_MAXIMIZE == (dwStyle & WS_MAXIMIZE))
			{
				SetItemAttribute(IDC_BTN_SYS_MAX, "skin", "maxbtn");
				break;
			}
		}
	case SC_MAXIMIZE:
		SetItemAttribute(IDC_BTN_SYS_MAX, "skin", "restorebtn");
		break;
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

void CMainWnd::OnStartGame()
{
	SetFocus();
	::OnStartGame( m_SnakeGame.m_hWnd );
}
