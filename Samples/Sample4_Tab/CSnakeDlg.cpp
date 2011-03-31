/*
作者： BILL
日期： 2011-03-10
功能： 
EMAIL：bill1263g@gmail.com
*/
#include "CSnakeDlg.h"
#include "MainWnd.h"

const int INIT_SPEED = 11;
char g_pMap[g_MapWidth*g_MapHeight];
tagSnakeNode g_Snake[SNAKE_MAXLONG];
int g_nSnakeLong = 0;
ENUM_DIRCTION g_nDirection = enumLEFT;
ENUM_DIRCTION g_nOldDirection = enumLEFT;

int g_nSpeed = INIT_SPEED;
int g_IsReward = 0;
int g_nScore = 0;
int g_nGameState = enumStart;
HWND g_hDlg = NULL;
RECT g_rtGame;
int g_nLastTime = 0;

bool g_GameRunning = false;

LRESULT CSnakeWnd::OnInitDialog( HWND hDlg, LPARAM lParam )
{
	g_hDlg = hDlg;
	InitGame( hDlg );
	return TRUE;
}

int CSnakeWnd::GetGameState()
{
	return g_GameRunning;
}

void CSnakeWnd::OnDestroy()
{
	
	KillTimer( 1 );
	Release();
}

void CSnakeWnd::OnTimer(UINT_PTR nIDEvent)
{
    OnGameLooping( g_hDlg );
}


// 初始化游戏
bool InitGame( HWND hDlg )
{
	g_rtGame.left = 0;
	g_rtGame.top = 0;
	g_rtGame.right = GAMEFRAME_WIDTH;
	g_rtGame.bottom = GAMEFRAME_HEIGHT;

	srand( GetTickCount() );
	
	return true;
}

// 重置游戏
bool ResetGame()
{
	int nLoop=0;
	for( nLoop = 0; nLoop<g_MapWidth*g_MapHeight; nLoop++ )
	{
		g_pMap[nLoop] = enumLAND;
	}

	for( nLoop = 0; nLoop<g_MapWidth; nLoop++ )
	{
		g_pMap[nLoop] = enumWALL;
		g_pMap[(g_MapHeight-1)*g_MapWidth + nLoop] = enumWALL;
	}

	for( nLoop = 1; nLoop<g_MapHeight-1; nLoop++ )
	{
		g_pMap[ ( nLoop * g_MapWidth ) ] = enumWALL;
		g_pMap[ ( nLoop * g_MapWidth )+ g_MapWidth - 1 ] = enumWALL;
	}

	g_nSnakeLong = 0;
	for( nLoop = 0; nLoop<5; nLoop++ )
	{
		g_Snake[g_nSnakeLong].nX = 5+nLoop;
		g_Snake[g_nSnakeLong++].nY = 5;
	}
	g_nDirection = enumLEFT;
	g_nGameState = enumStart;
	g_nLastTime = GetTickCount();

	g_IsReward = 0;
	GenerateReward();

	g_nScore = 0;
	CString strScore;
	strScore.Format( _T("%d"), g_nScore );
	g_pMainWnd->SetItemText( 303, strScore );

	return true;
}

// 释放游戏资源
void Release()
{
	
}

// 设置框架
void SetGameFrame( HWND hDlg )
{
	HWND hGamePane = hDlg;
	if( NULL != hGamePane )
	{
		RECT rt;
		GetClientRect( hDlg, &rt );
		int nFrameWidth = rt.right - rt.left;
		int nFrameHeight = rt.bottom - rt.top;
		int nPosX = rt.left + 70 + ( nFrameWidth - 70 - GAMEFRAME_WIDTH ) / 2;
		int nPosY = rt.top + ( nFrameHeight - GAMEFRAME_HEIGHT ) / 2;

	}
}

// 游戏控制
void OnKeyDown( WPARAM wParam, LPARAM lParam )
{
	switch( wParam )
	{
	case VK_LEFT:
		if( g_nOldDirection == enumUP || g_nOldDirection == enumDOWN )
			g_nDirection = enumLEFT;
		break;
	case VK_UP:
		if( g_nOldDirection == enumLEFT || g_nOldDirection == enumRIGHT )
			g_nDirection = enumUP;
		break;
	case VK_RIGHT:
		if( g_nOldDirection == enumUP || g_nOldDirection == enumDOWN )
			g_nDirection = enumRIGHT;
		break;
	case VK_DOWN:
		if( g_nOldDirection == enumLEFT || g_nOldDirection == enumRIGHT )
			g_nDirection = enumDOWN;
		break;
	}
}

// 检测物品
ENUM_MAPUNIT GetLandType( int nX, int nY )
{
	return (ENUM_MAPUNIT)g_pMap[ nY * g_MapWidth + nX ];
}

// 点击开始结束按钮
void OnStartGame( HWND hDlg )
{
	if( g_GameRunning )
	{
		g_GameRunning = false;
		g_pMainWnd->SetItemText( 302, _T("开始游戏") );
		KillTimer( hDlg, 1 );
	}
	else
	{
		ResetGame();
		g_GameRunning = true;
		g_pMainWnd->SetItemText( 302, _T("停止游戏") );
		SetTimer( hDlg, 1, 50, NULL );
	}
}

// 游戏更新
bool UpdateGame( DWORD dwTimeTick )
{
	bool bRet = false;
	switch( g_nGameState )
	{
	case enumStart:
		{
			if( ( dwTimeTick - g_nLastTime ) > 1000 )
			{
				g_nGameState = enumGame;
			}
			
			return true;
		}
		break;
	case enumGame:
		{
			bRet |= MoveSnake( dwTimeTick );
		}
		break;
	case enumEnd:
		return true;
		break;
	}
	
	return bRet;
	
}

// 游戏绘制
void DrawGame( HDC hDC )
{
	int nX, nY;
	for( nY = 0; nY< g_MapHeight; nY++ )
		for( nX = 0; nX<g_MapWidth; nX++ )
		{
			DrawBlock( hDC, nX, nY, (ENUM_MAPUNIT)g_pMap[nY*g_MapWidth + nX] );
		}

	DrawSnake(hDC);
}

void OnGameLooping( HWND hDlg )
{
	if( UpdateGame( GetTickCount() ) )
	{
		HWND hGame = hDlg;
		HDC hDC=GetDC( hDlg );
		switch( g_nGameState )
		{
		case enumStart:
			DrawStart( hDC );
			break;
		case enumGame:
			DrawGame( hDC );
			break;
		case enumEnd:
			DrawEnd( hDC );
			break;
		}

		ReleaseDC( hGame, hDC );
	}
}

// 绘制小方块
void DrawBlock( HDC hDC, int nX, int nY, ENUM_MAPUNIT nType )
{
	RECT rt;
	rt.left = nX * BLOCK_WIDTH;
	rt.right = rt.left + BLOCK_WIDTH;
	rt.top = nY * BLOCK_HEIGHT;
	rt.bottom = rt.top + BLOCK_HEIGHT;
	switch( nType )
	{
	case enumWALL:
	case enumSNAKE:
		{
			FillRect( hDC, &rt, (HBRUSH)GetStockObject( BLACK_BRUSH ) );
		}
		break;
	case enumREWARD:
		FillRect( hDC, &rt, (HBRUSH)GetStockObject( GRAY_BRUSH ) );
		break;
	default:
		FillRect( hDC, &rt, (HBRUSH)GetStockObject( WHITE_BRUSH ) );
		break;
	}
}

void DrawSnake( HDC hDC )
{
	int nLoop=0;
	for( nLoop = 0; nLoop<g_nSnakeLong; nLoop++ )
	{
		DrawBlock( hDC, g_Snake[nLoop].nX, g_Snake[nLoop].nY, enumSNAKE );
	}
}

// 小蛇移动
bool MoveSnake( DWORD dwTimeTick )
{
	bool bRet = false;
	static int s_OldTick = dwTimeTick;

	if( ( (int)dwTimeTick - s_OldTick )< ( 50*( 10 - g_nSpeed ) ) )
		return false;
	
	s_OldTick = dwTimeTick;

	POINT ptNewHead;
	ENUM_MAPUNIT nLandNewPos = enumLAND;

	switch( g_nDirection )
	{
	case enumLEFT:
		{
			ptNewHead.x = g_Snake[0].nX - 1;
			ptNewHead.y = g_Snake[0].nY;
		}
		break;
	case enumUP:
		{
			ptNewHead.x = g_Snake[0].nX;
			ptNewHead.y = g_Snake[0].nY-1;
		}
		break;
	case enumRIGHT:
		{
			ptNewHead.x = g_Snake[0].nX + 1;
			ptNewHead.y = g_Snake[0].nY;
		}
		break;
	case enumDOWN:
		{
			ptNewHead.x = g_Snake[0].nX;
			ptNewHead.y = g_Snake[0].nY+1;
		}
		break;
	}

	nLandNewPos = GetLandType( ptNewHead.x, ptNewHead.y );
	if( nLandNewPos == enumWALL )
	{
		GameOver();
		return true;
	}
	else if( nLandNewPos == enumREWARD )
	{
		EatReward( ptNewHead.x, ptNewHead.y, enumREWARD );
	}
	else
	{
		if( IsHitSelf( ptNewHead.x, ptNewHead.y ) )
		{
			GameOver();
			return true;
		}
	}

	int nLoop=0;
	for( nLoop = g_nSnakeLong-1; nLoop>=1; nLoop-- )
	{
		g_Snake[nLoop].nX = g_Snake[nLoop-1].nX;
		g_Snake[nLoop].nY = g_Snake[nLoop-1].nY;
	}
	g_Snake[0].nX = ptNewHead.x;
	g_Snake[0].nY = ptNewHead.y;
	if( g_nOldDirection != g_nDirection )
		g_nOldDirection = g_nDirection;

	bRet = true;
	return bRet;
}

void DrawStart( HDC hDC )
{
	DrawBack( hDC );
	TCHAR pText[128];
	_tcscpy( pText, _T("贪吃蛇 V1.0") );
	DrawText( hDC, pText, (int)_tcslen( pText ), &g_rtGame, DT_SINGLELINE | DT_VCENTER | DT_CENTER );
}

void DrawEnd( HDC hDC )
{
	DrawGame( hDC );

	TCHAR pText[128];
	_tcscpy( pText, _T("游戏结束") );
	DrawText( hDC, pText, (int)_tcslen( pText ), &g_rtGame, DT_SINGLELINE | DT_VCENTER | DT_CENTER );
}

void DrawBack( HDC hDC )
{
	RECT rt;
	rt.left = rt.top = 0;
	rt.right = GAMEFRAME_WIDTH;
	rt.bottom = GAMEFRAME_HEIGHT;
	FillRect( hDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH) );
}

// 是否撞倒自己
bool IsHitSelf( int nX, int nY )
{
	int nLoop=0;
	for( nLoop = 1; nLoop<g_nSnakeLong; nLoop++ )
	{
		if( g_Snake[nLoop].nX == nX && g_Snake[nLoop].nY == nY )
			return true;
	}

	return false;
}

// 游戏结束
void GameOver()
{
	g_nGameState = enumEnd;
	g_GameRunning = false;
	g_pMainWnd->SetItemText( 302, _T("开始游戏") );
	KillTimer( g_hDlg, 1 );
}

// 产生奖品
bool GenerateReward()
{
	if( g_IsReward == 1 )
		return false;

	int nLoop = 0;
	for( nLoop = 0; nLoop<100; nLoop++ )
	{
		int nX = 1 + rand() % ( g_MapWidth - 1);
		int nY = 1 + rand() % ( g_MapHeight - 1);

		if( g_pMap[nX + nY*g_MapWidth ] == enumLAND && !IsHitSelf( nX, nY ) )
		{
			g_pMap[nX + nY*g_MapWidth ] = enumREWARD;
			g_IsReward = 1;
			return true;
		}
	}
	for( nLoop=0; nLoop<g_MapWidth*g_MapHeight; nLoop++ )
	{
		if( g_pMap[nLoop] == enumLAND && !IsHitSelf( nLoop % g_MapWidth, nLoop / g_MapWidth ) )
		{
			g_pMap[nLoop] = enumREWARD;
			g_IsReward = 1;
			return true;
		}
	}
	return false;

}

// 吃奖品
bool EatReward( int nX, int nY, ENUM_MAPUNIT nLandType )
{
	g_pMap[nX + nY*g_MapWidth ] = enumLAND;
	g_IsReward = 0;
	GenerateReward();
	if( g_nSnakeLong>=SNAKE_MAXLONG )
		return true;

	int nOld = g_nSnakeLong++;
	g_Snake[g_nSnakeLong].nX = g_Snake[nOld].nX;
	g_Snake[g_nSnakeLong].nY = g_Snake[nOld].nY;

	g_nScore += 10*g_nSnakeLong;

	g_nSpeed = INIT_SPEED + g_nScore / 1000;
	if( g_nSpeed>10 )
		g_nSpeed = 10;
	CString strScore;
	strScore.Format( _T("%d"), g_nScore );
	g_pMainWnd->SetItemText( 303, strScore );
	return true;
}