#pragma once
#include "common.h"

#define MAX_SWINGER (5)


struct ARM;
struct SWINGER_BASE;
struct PLAYER_SW;
struct BLOCK;


//アームには描画しない
typedef struct ARM
{
	float length = 0;
	
	SWINGER_BASE* p_swingerLeft = nullptr;
	SWINGER_BASE* p_swingerRight = nullptr;

	float rotateLeft = 0;
	float rotateRight = 0;
};

#include "common.h"
typedef struct SWINGER_BASE
{
	bool use;
	GAME_OBJ obj;
	
	ARM* p_armLeft = nullptr;
	ARM* p_armRight = nullptr;


	//回転動きに関する情報+++++++++++++++++++++++
	float rotate = 0;//今回転の角度
	float rotateSpd = 0;//回転スピード
	D3DXVECTOR2* p_centerPos = nullptr;//円心座標
	float* p_radius = nullptr;//回転半径

	//掴む相関+++++++++++++++++++++++++++++++++++
	bool canCatch = false;
	bool isCatch = false;
	BLOCK* p_catchBlock = nullptr;

	//ハンドパーツ+++++++++++++++++++++++++++++++
};
enum PlayerState
{
	stop=0,
	fly,
	rightHand,
	leftHand,
	twoHand,
};
struct PLAYER_SW
{
	SWINGER_BASE* p_body = nullptr;
	SWINGER_BASE* p_leftHand = nullptr;
	SWINGER_BASE* p_rightHand = nullptr;

	//回転動きに関する情報+++++++++++++++++++++++
	int state = PlayerState::stop;
	D3DXVECTOR2 velocity = D3DXVECTOR2(0, 0);
};

HRESULT InitSwinger(void);
void UninitSwinger(void);
void UpdateSwinger(void);
void DrawSwinger(void);

SWINGER_BASE* GetSwinger(int id);
PLAYER_SW* GetSWPlayer(void);

void CatchBlock(SWINGER_BASE* swinger);
void ReleaseBlock(SWINGER_BASE* swinger);
void SetCanCatch(SWINGER_BASE* swinger,BLOCK* block ,bool can);
void SetCanCatchOff(SWINGER_BASE* swinger);
void SetSwingerCenterPos(D3DXVECTOR2 pos);

char* PlayerStateName(int state);
char* GameStateName(int state);