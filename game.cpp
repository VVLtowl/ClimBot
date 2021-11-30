/*==============================================================================

   ゲーム処理 [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "main.h"
#include "input.h"
#include "fade.h"
#include "collision.h"
#include "sound.h"


#include "game.h"
#include "camera.h"

#include "TextReader2.h"
#include "climbObjManager.h"
#include "hold.h"
#include "bg.h"
#include "player.h"

/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;
static int g_gameState;

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitGame(void)
{
	InitCamera();
	InitBG();
	//InitEnemy();
	//InitEnemyEmitter();
	//InitBullet();
	////InitScore();
	//InitBG();
	//InitUI();


	////InitBlock();
	//InitSwinger();
	InitHold();

	g_BGMNo = LoadSound("data/BGM/sample001.wav");

	SetVolume(g_BGMNo, 1.0f);

	ReadStageText("data/MAP/test2.txt");
	ChangeReaderDataToClimbObjData();

	SetBoundary(GetBG()->boundary);

	InitPlayer();
	ChangeGameState(GameState::waitFirstCatch);

	//PlaySound(g_BGMNo, -1);
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	//初期化とは逆順に終了処理を行う
	//UninitSwinger();
	//UninitBG();
	////UninitScore();
	//UninitBullet();
	//UninitBlock();
	//UninitEnemy();
	//UninitEnemyEmitter();
	//UninitUI();

	UninitPlayer();
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	//UpdateSwinger();
	//UpdateBG();
	//UpdateBlock();
	//UpdateEnemy();
	//UpdateBullet();
	////UpdateScore();

	//UpdateEnemyEmitter();

	//UpdateCollision();
	UpdateHold();
	UpdatePlayer();

	UpdateCamera();
	UpdateClimbObjManager();
	//UpdateUI();

	//スペースキーが押されていて、フェード処理中ではないとき
	if ((GetKeyboardTrigger(DIK_RETURN)|| IsButtonTriggered(1, BUTTON_PAD_RETURN))
		&& GetFadeState() == FADE_NONE) 
	{
		//SetVolume(g_BGMNo, 0.1f);

		//RESULTへ移行する
		SceneTransition(SCENE_RESULT);
	}
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	//DrawBG();
	//DrawBlock();
	//DrawBullet();
	//DrawEnemy();
	////DrawPlayer();

	//DrawSwinger();
	//DrawUI();
	////DrawScore();
	DrawBG();
	DrawHold();
	DrawPlayer();
}

void ChangeGameState(GameState state)
{
	if (g_gameState == state)
	{
		return;
	}
	else
	{
		switch (g_gameState)
		{
		case GameState::startStage:
			break;
		case GameState::waitFirstCatch:
			break;
		case GameState::playing:
			break;
		case GameState::relife:
			break;
		case GameState::complete:
			break;
		case GameState::die:
			break;
		}
		switch (state)
		{
		case GameState::startStage:
			break;
		case GameState::waitFirstCatch:
			break;
		case GameState::playing:
			break;
		case GameState::relife:
			Test_ResetPlayer();
			break;
		case GameState::complete:
			break;
		case GameState::die:
			break;
		}

		g_gameState = state;
	}
}
int GetGameState()
{
	return g_gameState;
}
const char* GameStateName()
{
	char name[100] = "";
	switch (g_gameState)
	{
	case GameState::startStage:
		sprintf(name, "startStage");
		break;
	case GameState::waitFirstCatch:
		sprintf(name, "waitFirstCatch");
		break;
	case GameState::playing:
		sprintf(name, "playing");
		break;
	case GameState::relife:
		sprintf(name, "relife");
		break;
	case GameState::complete:
		sprintf(name, "complete");
		break;
	case GameState::die:
		sprintf(name,"die");
		break;
	}
	return name;
}




