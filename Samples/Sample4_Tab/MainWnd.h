/*
作者： bill
日期： 2011-03-24
功能： Tab控件使用例子
*/
#pragma once
#include "stdafx.h"
#include "CSnakeDlg.h"
class CMainWnd : public CKuiDialogImpl<CMainWnd>
	, public CWHRoundRectFrameHelper<CMainWnd>
{
public:
	CMainWnd(void);
	virtual ~CMainWnd(void);
	LRESULT OnInitDialog( HWND hDlg, LPARAM lParam );
	void OnDestroy();

	void OnBkBtnClose();
    void OnBkBtnMax();
    void OnBkBtnMin();

	void OnStartGame();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnSysCommand(WPARAM wParam, CPoint pt );

	void OnTimer(UINT_PTR nIDEvent);   // 动画定时器

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
        KUI_NOTIFY_ID_COMMAND(60001, OnBkBtnClose)
        KUI_NOTIFY_ID_COMMAND(60002, OnBkBtnMax)
        KUI_NOTIFY_ID_COMMAND(60003, OnBkBtnMin)
		KUI_NOTIFY_ID_COMMAND(302, OnStartGame)
        //KUI_NOTIFY_TAB_SELCHANGE(IDC_TAB_MAIN, OnBkTabMainSelChange)
    KUI_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CMainWnd)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CKuiDialogImpl<CMainWnd>)
		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CMainWnd>)
		
		MSG_WM_KEYDOWN(OnKeyDown)

		MSG_WM_INITDIALOG(OnInitDialog)
		//MSG_WM_SYSCOMMAND(OnSysCommand)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_SYSCOMMAND(OnSysCommand)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
protected:
	CKuiRealListCtrl		m_ctlListCtrl;
	CSnakeWnd				m_SnakeGame;
	CWHHtmlContainerWindow	m_ctlWeb;
	KUIMulStatusTree		m_ctlTree;
};

extern CMainWnd *g_pMainWnd;
