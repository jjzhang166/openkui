/*
作者： BILL
日期： 2011-03-10
功能： 
EMAIL：bill1263g@gmail.com
*/
#ifndef _H_CSNAKEDLG_H
#define _H_CSNAKEDLG_H

#include "stdafx.h"

#define DELETE_OBJECT(x) {if(x!=NULL){ DeleteObject(x);x=NULL;}}


class CSnakeWnd : public CWindowImpl<CSnakeWnd>
{
public:
	CSnakeWnd(){};
	~CSnakeWnd(){};
	LRESULT OnInitDialog( HWND hDlg, LPARAM lParam );
	void OnDestroy();
    
	void OnTimer(UINT_PTR nIDEvent);   // 定时器
	
	int GetGameState();

	BEGIN_MSG_MAP_EX(CSnakeWnd)
		MSG_WM_TIMER(OnTimer)

		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_DESTROY(OnDestroy)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
};

enum ENUM_MAPUNIT
{
	enumLAND = 0,
	enumWALL,
	enumSNAKE,
	enumREWARD
};

enum ENUM_GAMESTATE
{
	enumStart = 0,
	enumGame,
	enumEnd
};

enum ENUM_DIRCTION
{
	enumLEFT,
	enumUP,
	enumRIGHT,
	enumDOWN
};

struct tagSnakeNode
{
	tagSnakeNode()
		:nX(0)
		,nY(0)
	{};

	int nX;
	int nY;
};

const int GAMEFRAME_WIDTH	= 300;
const int GAMEFRAME_HEIGHT	= 300;
const int BLOCK_WIDTH		= 10;
const int BLOCK_HEIGHT		= 10;
const int SNAKE_MAXLONG		= 100;
const int g_MapWidth = GAMEFRAME_WIDTH/BLOCK_WIDTH;
const int g_MapHeight = GAMEFRAME_HEIGHT/BLOCK_HEIGHT;
// 游戏绘制
void DrawGame( HDC hDC );
void DrawStart( HDC hDC );
void DrawEnd( HDC hDC );
void DrawBack( HDC hDC );
void DrawSnake( HDC hDC );

// 初始化游戏
bool InitGame( HWND hDlg );
// 释放游戏资源
void Release();
// 重置游戏
bool ResetGame();
// 设置框架
void SetGameFrame( HWND hDlg );
// 点击开始结束按钮
void OnStartGame( HWND hDlg );
// 游戏循环
void OnGameLooping( HWND hDlg );
// 游戏控制
void OnKeyDown( WPARAM wParam, LPARAM lParam );
// 游戏更新
bool UpdateGame( DWORD dwTimeTick );
// 绘制小方块
void DrawBlock( HDC hDC, int nX, int nY, ENUM_MAPUNIT nType );
// 小蛇移动
bool MoveSnake( DWORD dwTimeTick );
// 检测物品
ENUM_MAPUNIT GetLandType( int nX, int nY );
// 是否撞倒自己
bool IsHitSelf( int nX, int nY );
// 吃奖品
bool EatReward( int nX, int nY, ENUM_MAPUNIT );
// 游戏结束
void GameOver();
// 产生奖品
bool GenerateReward();

#endif
