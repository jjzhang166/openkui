/*
作者： b2b160
日期： 2011-03-07
功能： IM登陆窗口界面例子
*/

#include "stdafx.h"
#include ".\mainwnd.h"

HINSTANCE g_hInstance; 
CKuiApp<CMainWnd> _Module;
CAppModule* _ModulePtr = &_Module;

int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;

	_Module.Init( hInstance );
	_Module.Main();
	_Module.UnInit();

	return 0;
}
