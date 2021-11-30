#include "main.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"

#include "game.h"


#include "bg.h"
#include "collision.h"

#include <imgui.h>
#include "player.h"
#include "hold.h"

//キーボードボタンの設定
#define KEY_LEFT_SHAKE (DIK_W)
#define KEY_RIGHT_SHAKE (DIK_O)
#define KEY_AUTO_SHAKE (DIK_SPACE)

#define KEY_LEFT_CATCH (DIK_E)
#define KEY_RIGHT_CATCH (DIK_I)

#define KEY_LEFT_SKILL (DIK_R)
#define KEY_RIGHT_SKILL (DIK_U)

#define KEY_SHAKE_COOL_DOWN_RATE (25)


//
#define BALL_NUM (3)
#define BALL_SIZE_HAND (80.0f)
#define BALL_SIZE_BODY (70.0f)
#define BALL_HAND_NORMAL_TEX_PATH "data/TEXTURE/palm_normal.png"
#define BALL_BODY_NORMAL_TEX_PATH "data/TEXTURE/robot_main.png"
#define BALL_HAND_BG0_TEX_PATH "data/TEXTURE/palm_bg0.png"
#define BALL_COL_RADIUS (35.0f)


#define ARM_NUM (BALL_NUM-1)
#define ARM_WIDTH (15.0f)
#define ARM_NORMAL_TEX_PATH "data/TEXTURE/tube.png"

//physic
#define GRAVITY_A (0.006f)
#define GRAVITY_FLY (0.5f)
#define DRAG_FLY (0.005f)
#define PULL_A (RADIANT(12.0f))
#define MAX_ROTATE_SPEED (RADIANT(12.0f))

#define MAX_JUMP_HIGH (UNIT_SIZE)
#define MAX_JUMP_SPEED_Y (16.0f)
#define MIN_JUMP_SPEED_X (2.4f)
#define MAX_JUMP_SPEED_X (5.0f)
void Test_ResetPlayer();
void InputPull();
void InputCatch();
void ImGui_ShowPlayerInfo();
Player g_player;

void Test_ResetPlayer()
{
	g_player.Reset();

	//init ball
	{
		g_player.CreateBall(3);
		Ball* pBall;
		//left hand (hold hand)
		{
			pBall = &g_player.p_balls[0];
			//new
			{
				//transform
				Hold* pHoldCheckpoint = GetCheckpointHold();
				pBall->transform.position = pHoldCheckpoint->gameObject.transform.position;
				pBall->isCatch = true;

				//display
				pBall->CreateDisplay(2);

				{
					Display* pDisplay = &pBall->p_displays[0];
					pDisplay->size = { BALL_SIZE_HAND,BALL_SIZE_HAND };
					pDisplay->texNo = LoadTexture(BALL_HAND_BG0_TEX_PATH);
					pDisplay->animeID = 0;
					pDisplay->color = { 0.95f,1.0f,0.6f,1 };
					pDisplay->CreateAnimation(1);
					Animation* pAnimation = &pDisplay->p_animes[0];
					pAnimation->frameMax = 1;
					pAnimation->pieceID = 1;

					pAnimation->CreatePieceUV(1);
					D3DXVECTOR4 uv = { 0,0,1,1 };
					pAnimation->p_pieceUVs[0] = uv;
					pAnimation->pieceID = 0;
				}
				{
					Display* pDisplay = &pBall->p_displays[1];
					pDisplay->size = { BALL_SIZE_HAND,BALL_SIZE_HAND };
					pDisplay->texNo = LoadTexture(BALL_HAND_NORMAL_TEX_PATH);
					pDisplay->animeID = 0;
					pDisplay->color = { 1,1,1,1 };
					pDisplay->CreateAnimation(1);
					Animation* pAnimation = &pDisplay->p_animes[0];
					pAnimation->frameMax = 1;
					pAnimation->pieceID = 1;

					pAnimation->CreatePieceUV(1);
					D3DXVECTOR4 uv = { 0,0,1,1 };
					pAnimation->p_pieceUVs[0] = uv;
					pAnimation->pieceID = 0;
				}

				//collider
				pBall->collider = new Collider_Circle(BALL_COL_RADIUS);
			}

			//gameobj
			{
			//	//transform
			//	Hold* pHoldCheckpoint = GetCheckpointHold();
			//	pBall->gameObject.transform.position = pHoldCheckpoint->gameObject.transform.position;
			//	pBall->isCatch = true;

			//	//display
			//	pBall->gameObject.CreateDisplay(1);
			//	Display* pDisplay = &pBall->gameObject.p_displays[0];
			//	pDisplay->size = { BALL_SIZE_HAND,BALL_SIZE_HAND };
			//	pDisplay->texNo = LoadTexture(BALL_HAND_NORMAL_TEX_PATH);
			//	pDisplay->animeID = 0;

			//	pDisplay->CreateAnimation(1);
			//	Animation* pAnimation = &pDisplay->p_animes[0];
			//	pAnimation->frameMax = 1;
			//	pAnimation->pieceID = 1;

			//	pAnimation->CreatePieceUV(1);
			//	D3DXVECTOR4 uv = { 0,0,1,1 };
			//	pAnimation->p_pieceUVs[0] = uv;
			//	pAnimation->pieceID = 0;

			//	//collider
			//	pBall->gameObject.CreateCollider(1);
			//	pBall->gameObject.pp_colliders[0] = new Collider_Circle(BALL_COL_RADIUS);
			}
		}

		//body
		{
			//new
			{
				pBall = &g_player.p_balls[1];

				//display
				pBall->CreateDisplay(1);
				Display* pDisplay = &pBall->p_displays[0];
				pDisplay->size = { BALL_SIZE_BODY,BALL_SIZE_BODY };
				pDisplay->texNo = LoadTexture(BALL_BODY_NORMAL_TEX_PATH);
				pDisplay->animeID = 0;

				pDisplay->CreateAnimation(1);
				Animation* pAnimation = &pDisplay->p_animes[0];
				pAnimation->frameMax = 1;
				pAnimation->pieceID = 1;

				pAnimation->CreatePieceUV(1);
				D3DXVECTOR4 uv = { 0,0,1,1 };
				pAnimation->p_pieceUVs[0] = uv;
				pAnimation->pieceID = 0;
			}

			//gameObj
			{
				//pBall = &g_player.p_balls[1];
				////gameobj
				////transform
				////Ball* pFatherBall = pBall->GetFatherBall();
				////pBall->gameObject.transform.position = pFatherBall->gameObject.transform.position + D3DXVECTOR2(ARM_LENGTH_NORMAL, 0);

////display
//pBall->gameObject.CreateDisplay(1);
//Display* pDisplay = &pBall->gameObject.p_displays[0];
//pDisplay->size = { BALL_SIZE_BODY,BALL_SIZE_BODY };
//pDisplay->texNo = LoadTexture(BALL_BODY_NORMAL_TEX_PATH);
//pDisplay->animeID = 0;

//pDisplay->CreateAnimation(1);
//Animation* pAnimation = &pDisplay->p_animes[0];
//pAnimation->frameMax = 1;
//pAnimation->pieceID = 1;

//pAnimation->CreatePieceUV(1);
//D3DXVECTOR4 uv = { 0,0,1,1 };
//pAnimation->p_pieceUVs[0] = uv;
//pAnimation->pieceID = 0;

//////collider
//pBall->gameObject.colliderNum = 0;
////pBall->gameObject.CreateCollider(1);
////Collider* pCollider = pBall->gameObject.pp_colliders[0];
////pCollider = new Collider_Circle(BALL_COL_RADIUS);
			}
		}

		//right hand
		{
		pBall = &g_player.p_balls[2];

		//new
		{
			//display
			pBall->CreateDisplay(2);
			{
				Display* pDisplay = &pBall->p_displays[0];
				pDisplay->size = { BALL_SIZE_HAND,BALL_SIZE_HAND };
				pDisplay->texNo = LoadTexture(BALL_HAND_BG0_TEX_PATH);
				pDisplay->animeID = 0;
				pDisplay->color = { 0.5f,0.7f,1.0f,1 };
				pDisplay->CreateAnimation(1);
				Animation* pAnimation = &pDisplay->p_animes[0];
				pAnimation->frameMax = 1;
				pAnimation->pieceID = 1;

				pAnimation->CreatePieceUV(1);
				D3DXVECTOR4 uv = { 0,0,1,1 };
				pAnimation->p_pieceUVs[0] = uv;
				pAnimation->pieceID = 0;
			}
			{
				Display* pDisplay = &pBall->p_displays[1];
				pDisplay->size = { BALL_SIZE_HAND,BALL_SIZE_HAND };
				pDisplay->texNo = LoadTexture(BALL_HAND_NORMAL_TEX_PATH);
				pDisplay->animeID = 0;
				pDisplay->color = { 1,1,1,1 };
				pDisplay->CreateAnimation(1);
				Animation* pAnimation = &pDisplay->p_animes[0];
				pAnimation->frameMax = 1;
				pAnimation->pieceID = 1;

				pAnimation->CreatePieceUV(1);
				D3DXVECTOR4 uv = { 0,0,1,1 };
				pAnimation->p_pieceUVs[0] = uv;
				pAnimation->pieceID = 0;
			}

			//collider
			pBall->collider = new Collider_Circle(BALL_COL_RADIUS);
		}

		//gameobj
		{
			//	//transform
			////Ball* pFatherBall = pBall->GetFatherBall();
			////pBall->gameObject.transform.position = pFatherBall->gameObject.transform.position + D3DXVECTOR2(ARM_LENGTH_NORMAL, 0);

			////display
			//	pBall->gameObject.CreateDisplay(1);
			//	Display* pDisplay = &pBall->gameObject.p_displays[0];
			//	pDisplay->size = { BALL_SIZE_HAND,BALL_SIZE_HAND };
			//	pDisplay->texNo = LoadTexture(BALL_HAND_NORMAL_TEX_PATH);
			//	pDisplay->animeID = 0;

			//	pDisplay->CreateAnimation(1);
			//	Animation* pAnimation = &pDisplay->p_animes[0];
			//	pAnimation->frameMax = 1;
			//	pAnimation->pieceID = 1;

			//	pAnimation->CreatePieceUV(1);
			//	D3DXVECTOR4 uv = { 0,0,1,1 };
			//	pAnimation->p_pieceUVs[0] = uv;
			//	pAnimation->pieceID = 0;

			//	//collider
			//	pBall->gameObject.CreateCollider(1);
			//	pBall->gameObject.pp_colliders[0] = new Collider_Circle(BALL_COL_RADIUS);
		}
		}
	}

	//init arm
	{
	g_player.CreateArm(2);
	Arm* pArm;
	//left arm
	{
		pArm = &g_player.p_arms[0];
		//display
		{
			pArm->display.CreateAnimation(1);
			Display* pDisplay = &pArm->display;

			pDisplay->size = { pArm->length ,ARM_WIDTH };
			pDisplay->texNo = LoadTexture(ARM_NORMAL_TEX_PATH);
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 1;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			D3DXVECTOR4 uv = { 0,0,1,1 };
			pAnimation->p_pieceUVs[0] = uv;
		}
	}
	//right arm
	{
		pArm = &g_player.p_arms[1];
		//display
		{
			pArm->display.CreateAnimation(1);
			Display* pDisplay = &pArm->display;

			pDisplay->size = { pArm->length ,ARM_WIDTH };
			pDisplay->texNo = LoadTexture(ARM_NORMAL_TEX_PATH);
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 1;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			D3DXVECTOR4 uv = { 0,0,1,1 };
			pAnimation->p_pieceUVs[0] = uv;
		}
	}
	}

		
	

	Ball* balls = g_player.p_balls;
	Arm* arms = g_player.p_arms;
	//link ball and arm
	{
		balls[0].ballPos = BallPos::bodyLeft;
		balls[1].ballPos = BallPos::bodySelf;
		balls[2].ballPos = BallPos::bodyRight;

		balls[0].SetTwoArm(nullptr, &arms[0]);
		arms[0].SetTwoBall(&balls[0], &balls[1]);
		balls[1].SetTwoArm(&arms[0], &arms[1]);
		arms[1].SetTwoBall(&balls[1], &balls[2]);
		balls[2].SetTwoArm(&arms[1], nullptr);

		Ball* pFatherBall = balls[1].GetFatherBall();
		balls[1].transform.position = pFatherBall->transform.position + D3DXVECTOR2(ARM_LENGTH_NORMAL, 0);
		pFatherBall = balls[2].GetFatherBall();
		balls[2].transform.position = pFatherBall->transform.position + D3DXVECTOR2(ARM_LENGTH_NORMAL, 0);
	}

	//init player
	{
		//ball
		g_player.pLeftBall = &balls[0];
		g_player.pBodyBall = &balls[1];
		g_player.pRightBall = &balls[2];

		g_player.pHoldBall = &balls[0];
		g_player.pHoldBall->isCatch = true;

		g_player.ChangeState(PlayerState::leftHand);

		//move 
	}
}
void InitPlayer()
{
	Test_ResetPlayer();
}
void UninitPlayer()
{
	g_player.Reset();
}
void UpdatePlayer()
{
	InputPull();
	InputCatch();
	g_player.Update();

	//out boundary check
	{
		bool allBallOut = true;
		D3DXVECTOR4 boundary = GetBoundary();

		for (int i = 0; i < g_player.ballNum; i++)
		{
			Ball* pBall = &g_player.p_balls[i];
			D3DXVECTOR3 pos = pBall->transform.position;
			D3DXVECTOR2 size = pBall->p_displays[0].size;

			if (pos.x + size.x / 2 < boundary.x ||
				pos.x - size.x / 2 > boundary.y ||
				pos.y + size.y / 2 < boundary.z ||
				pos.y - size.y / 2 > boundary.w)
			{
			}
			else
			{
				allBallOut = false;
			}
		}


		if (allBallOut)
		{
			ChangeGameState(GameState::relife);
		}
	}
}
void DrawPlayer()
{
	g_player.Draw();
	ImGui_ShowPlayerInfo();
}


Player* GetPlayer()
{
	return &g_player;
}

//---------------------------------------------------------
char* PlayerStateName()
{
	switch (g_player.state) {
	case 0: return "stop"; break;
	case 1: return "fly"; break;
	case 2: return "rightHand"; break;
	case 3: return "leftHand"; break;
	case 4: return "twoHand"; break;
	}
}

void ImGui_ShowPlayerInfo()
{
	ImGui::Begin("Player", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::Text("player: %s\n", PlayerStateName());
	//ImGui::Text("left rotSpd: %.1lf\n", g_player.pLeftBall->rotateSpeed);
	//ImGui::Text("right rotSpd: %.1lf\n", g_player.pRightBall->rotateSpeed);
	ImGui::Text(" %.1lf -> %.1lf -> %.1lf -> %.1lf \n", RADIANT(0), RADIANT(90), RADIANT(180), RADIANT(-90));
	ImGui::Text("body rot: %.1lf\n", g_player.pBodyBall->GetRotate());
	ImGui::Text("move spd: %.1lf,%.1lf\n", g_player.moveSpeed.x, g_player.moveSpeed.y);
	ImGui::Text(" leftCatch: %s/%s\n",
		g_player.pLeftBall->isCatch ? "true" : "false",
		g_player.pLeftBall->pCatchHold ? "true" : "false");
	ImGui::Text(" rightCatch: %s/%s\n",
		g_player.pRightBall->isCatch ? "true" : "false",
		g_player.pRightBall->pCatchHold ? "true" : "false");

	ImGui::Text("game: %s\n", GameStateName());
	ImGui::End();
}
void InputPull()
{
	static int frameCount = -1;
	if (frameCount == -1)
	{

		if (g_player.state == PlayerState::leftHand ||
			g_player.state == PlayerState::rightHand)
		{
			if (GetKeyboardTrigger(KEY_AUTO_SHAKE))
			{
				g_player.Pull(PullType::same);
				frameCount = 0;
			}
			if (IsButtonTriggered(1, BUTTON_LEFT))
			{
				g_player.Pull(PullType::left);
				frameCount = 0;
			}
			if (IsButtonTriggered(1, BUTTON_RIGHT))
			{
				g_player.Pull(PullType::right);
				frameCount = 0;
			}
		}
		else if (g_player.state == PlayerState::fly)
		{
			//rocket left right ?
			/*if (GetKeyboardPress(KEY_LEFT_SHAKE)||
				IsButtonPressed(1, BUTTON_LEFT))
			{
				g_playerSW.velocity.x = max(g_playerSW.velocity.x - g_gravity/3, -12.0f);
			}
			if (GetKeyboardPress(KEY_RIGHT_SHAKE) ||
				IsButtonPressed(1, BUTTON_RIGHT))
			{
				g_playerSW.velocity.x = min(g_playerSW.velocity.x + g_gravity/2, 12.0f);
			}*/
		}
	}
	else
	{
		frameCount++;
		if (frameCount >= KEY_SHAKE_COOL_DOWN_RATE)
		{
			frameCount = -1;
		}
	}


}
void InputCatch()
{
	if (GetGameState() == GameState::playing)
	{
		g_player.pRightBall->isCatch = false;
		g_player.pLeftBall->isCatch = false;
	}
	if (GetGameState() == GameState::waitFirstCatch)
	{
		//g_player.pLeftBall->isCatch = true;
		//g_player.pRightBall->isCatch = false;
	}

	//g_player.pLeftBall->pCatchHold =
	//	g_player.pRightBall->pCatchHold = true;

	if (g_player.pLeftBall->pCatchHold &&
		!g_player.pLeftBall->isCatch)
	{
		if ((GetKeyboardPress(KEY_LEFT_CATCH) || IsButtonPressed(1, BUTTON_L2)))
		{
			g_player.pLeftBall->isCatch = true;
			//first catch and start playing
			{
				if (GetGameState() != GameState::playing)
				{
					ChangeGameState(GameState::playing);
				}
			}
		}
		else
		{
			//	ReleaseBlock(&g_swinger[g_leftID]);
		}
	}


	if (g_player.pRightBall->pCatchHold &&
		!g_player.pRightBall->isCatch)
	{
		if ((GetKeyboardPress(KEY_RIGHT_CATCH) || IsButtonPressed(1, BUTTON_R2)))
		{
			//g_swinger[g_rightID].isCatch = true;
			//CatchBlock(&g_swinger[g_rightID]);
			g_player.pRightBall->isCatch = true;
			//first catch and start playing
			{
				if (GetGameState() != GameState::playing)
				{
					ChangeGameState(GameState::playing);
				}
			}
		}
		else
		{
			//ReleaseBlock(&g_swinger[g_rightID]);
		}
	}

}


///class---------------------------------------------------


Ball* Ball::GetFatherBall()
{
	Ball* pBall = nullptr;
	Arm* pArm;
	if (g_player.state == PlayerState::leftHand)
	{
		pArm = pLeftArm;
		if (pArm)pBall = pArm->pLeftBall;
	}
	else if (g_player.state == PlayerState::rightHand)
	{
		pArm = pRightArm;
		if (pArm)pBall = pArm->pRightBall;
	}
	else if (g_player.state == PlayerState::fly)
	{
		if (ballPos == BallPos::bodyLeft)pBall = pRightArm->pRightBall;
		if (ballPos == BallPos::bodyRight)pBall = pLeftArm->pLeftBall;
	}
	else if (g_player.state == PlayerState::stop||
		g_player.state == PlayerState::twoHand )
	{
		pArm = pLeftArm;
		if (pArm)pBall = pArm->pLeftBall;
	}
	return pBall;
}

Arm* Ball::GetFatherArm()
{
	Ball* pBall = nullptr;
	Arm* pArm = nullptr;
	if (g_player.state == PlayerState::leftHand)
	{
		pArm = pLeftArm;
	}
	else if (g_player.state == PlayerState::rightHand)
	{
		pArm = pRightArm;
	}
	else if (g_player.state == PlayerState::fly)
	{
		if (ballPos == BallPos::bodyRight)pArm = pLeftArm ? pLeftArm : nullptr;
		if (ballPos == BallPos::bodyLeft)pArm = pRightArm ? pRightArm : nullptr;
		{
			//if (this != g_player.pBodyBall)
		//{

		//	//check left
		//	pBall = g_player.pBodyBall;
		//	pArm = pBall->pLeftArm;
		//	while (pArm)
		//	{
		//		if (pArm->pLeftBall == this)
		//		{
		//			return pArm;
		//		}
		//		else
		//		{
		//			pArm = pArm->pLeftBall->pLeftArm;
		//		}
		//	}

		//	//check right
		//	pBall = g_player.pBodyBall;
		//	pArm = pBall->pLeftArm;
		//	while (pArm)
		//	{
		//		if (pArm->pRightBall == this)
		//		{
		//			return pArm;
		//		}
		//		else
		//		{
		//			pArm = pArm->pRightBall->pRightArm;
		//		}
		//	}

		//}
		}
	}
	else if (g_player.state == PlayerState::stop ||
		g_player.state == PlayerState::twoHand)
	{
		pArm = pLeftArm;
	}
	return pArm;
}

Ball* Ball::GetSonBall()
{
	Ball* pBall = nullptr;
	Arm* pArm;
	if (g_player.state == PlayerState::leftHand)
	{
		pArm = pRightArm;
		if (pArm)pBall = pArm->pRightBall;
	}
	else if (g_player.state == PlayerState::rightHand)
	{
		pArm = pLeftArm;
		if (pArm)pBall = pArm->pLeftBall;
	}
	else if (g_player.state == PlayerState::fly)
	{
		if (ballPos == BallPos::bodyLeft)pBall = pLeftArm ? pLeftArm->pLeftBall : nullptr;
		if (ballPos == BallPos::bodyRight)pBall = pRightArm ? pRightArm->pRightBall : nullptr;
	}
	else if (g_player.state == PlayerState::stop ||
		g_player.state == PlayerState::twoHand)
	{
		pArm = pRightArm;
		if (pArm)pBall = pArm->pRightBall;
	}
	return pBall;
}

Arm* Ball::GetSonArm()
{
	Ball* pBall = nullptr;
	Arm* pArm = nullptr;
	if (g_player.state == PlayerState::leftHand)
	{
		pArm = pRightArm;
	}
	else if (g_player.state == PlayerState::rightHand)
	{
		pArm = pLeftArm;
	}
	else if (g_player.state == PlayerState::fly)
	{
		if (ballPos == BallPos::bodyLeft)pArm = pLeftArm ? pLeftArm : nullptr;
		if (ballPos == BallPos::bodyRight)pArm = pRightArm ? pRightArm : nullptr;
		//if (this != g_player.pBodyBall)
		//{
		//	//check left
		//	pBall = g_player.pBodyBall;
		//	pArm = pBall->pLeftArm;
		//	while (pArm)
		//	{
		//		if (pArm->pLeftBall == this)
		//		{
		//			return this->pLeftArm;
		//		}
		//		else
		//		{
		//			pArm = pArm->pLeftBall->pLeftArm;
		//		}
		//	}

		//	//check right
		//	pBall = g_player.pBodyBall;
		//	pArm = pBall->pLeftArm;
		//	while (pArm)
		//	{
		//		if (pArm->pRightBall == this)
		//		{
		//			return this->pRightArm;
		//		}
		//		else
		//		{
		//			pArm = pArm->pRightBall->pRightArm;
		//		}
		//	}
		//}
	}
	else if (g_player.state == PlayerState::stop ||
		g_player.state == PlayerState::twoHand)
	{
		pArm = pRightArm;
	}
	return pArm;
}

void Ball::Update()
{
	if (g_player.state == PlayerState::fly)
	{
		//rotate speed
		//UpdateRotateSpeed();
		//rotateSpeed = MAX_ROTATE_SPEED;

		RotateDisplay();
	}
	else if (g_player.state == PlayerState::twoHand)
	{
		rotateSpeed = 0;
	}
	else if (g_player.state == PlayerState::leftHand ||
		g_player.state == PlayerState::rightHand)
	{
		////rotate speed
		//if (!isCatch)
		//{
		//	D3DXVECTOR2 fatherPos = GetFatherBall()->gameObject.transform.position;
		//	D3DXVECTOR2 sonPos = gameObject.transform.position;
		//	float rot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x);
		//	rotateSpeed += -cosf(rot) * GRAVITY_A;
		//	Arm* pArm = GetFatherArm();
		//	if (pArm)
		//	{
		//		if (pArm == pRightArm)
		//		{
		//			if (pRightArm)
		//				rotateSpeed += (pRightArm->pRightBall->rotateSpeed - rotateSpeed) * 0.03f;
		//		}
		//		if (pArm == pLeftArm)
		//		{
		//			if (pLeftArm)
		//				rotateSpeed += (pLeftArm->pLeftBall->rotateSpeed - rotateSpeed) * 0.03f;
		//		}
		//	}
		//	rotateSpeed = fmaxf(-MAX_ROTATE_SPEED, fminf(MAX_ROTATE_SPEED, rotateSpeed));
		//}
		
		//rotate speed
		UpdateRotateSpeed();

		//Rotate();
		RotateDisplay();
	}

	//player hold collision
	if (ballPos != BallPos::bodySelf)
	{
		bool hasCol = false;
		for (int i = 0; i < GetHold().size(); i++)
		{
			Hold* pHold = GetHold()[i];
			bool isCol = false;
			for (int j = 0; j < pHold->gameObject.colliderNum; j++)
			{
				Collider* pHoldCol = pHold->gameObject.pp_colliders[j];

				switch (pHoldCol->type)
				{
				case ColliderType::rect:
				{
					D3DXVECTOR2 pos1 = transform.position;
					D3DXVECTOR2 size1 = { collider->CircleGetRadiusRadius(),collider->CircleGetRadiusRadius() };
					D3DXVECTOR2 pos2 = pHold->gameObject.transform.position;
					D3DXVECTOR2 size2 = pHoldCol->RectGetRectSize();
					isCol = CollisionBB(pos1, pos2, size1, size2);
				}
				break;
				case ColliderType::circle:
				{
					D3DXVECTOR2 pos1 = transform.position;
					float radius1 = collider->CircleGetRadiusRadius();
					D3DXVECTOR2 pos2 = pHold->gameObject.transform.position;
					float radius2 = pHoldCol->CircleGetRadiusRadius();

					isCol = CollisionBC(pos1, pos2, radius1, radius2);
				}
				break;
				case ColliderType::capsule:
					break;
				}
			}
			

			//edit by fujita
			if (isCol)
			{
				hasCol = true;
				pCatchHold = pHold;
				if(g_player.pLeftBall->isCatch || g_player.pRightBall->isCatch)
				if (pCatchHold->holdType == collapse) {
					pCatchHold->isCatchedCount++;
				}
			}
			
		}
		if (!hasCol||pCatchHold->isCollapsing ||!pCatchHold->isUse)
		{

			pCatchHold = nullptr;
		}
	}
}

void Ball::Draw()
{
	//new 
	{
		//deisplay
		{
			for (int i = 0; i < displayNum; i++)
			{
				Display* pDisplay = &p_displays[i];
				Animation* pAnimation = &pDisplay->p_animes[pDisplay->animeID];
				D3DXVECTOR4 uv = pAnimation->p_pieceUVs[pAnimation->pieceID];

				int texNo = pDisplay->texNo;
				float x = transform.position.x + pDisplay->posOffset.x;
				float y = transform.position.y + pDisplay->posOffset.y;
				float w = transform.scale.x * pDisplay->size.x;
				float h = transform.scale.y * pDisplay->size.y;
				float tx = uv.x;
				float ty = uv.y;
				float tw = uv.z;
				float th = uv.w;
				D3DXCOLOR cl = pDisplay->color;

				D3DXVECTOR2 offsetPos = pDisplay->posOffset;
				float offsetRot = atan2f(-offsetPos.y, offsetPos.x);
				float rot = displayRotation + offsetRot;
				DrawSpriteColorRotate(
					texNo,
					x, y, w, h,
					tx, ty, tw, th,
					cl,
					rot);
			}
		}

		//collider
		if (CanShowCol() &&
			collider)
		{
			Collider* pCollider = collider;

			int texNo = GetColTexNo();
			float x = transform.position.x + pCollider->posOffset.x;
			float y = transform.position.y + pCollider->posOffset.y;
			float w;
			float h;
			if (pCollider->type == ColliderType::rect)
			{
				w = transform.scale.x * pCollider->RectGetRectSize().x;
				h = transform.scale.y * pCollider->RectGetRectSize().y;
			}
			else if (pCollider->type == ColliderType::circle)
			{
				w = transform.scale.x * (pCollider->CircleGetRadiusRadius() * 2);
				h = transform.scale.y * (pCollider->CircleGetRadiusRadius() * 2);
			}
			else if (pCollider->type == ColliderType::capsule)
			{
				w = transform.scale.x * (pCollider->CapsuleGetRectVector().x + pCollider->CapsuleGetRectRadius() * 2);
				h = transform.scale.y * (pCollider->CapsuleGetRectRadius() * 2);
			}

			float tx = 0;
			float ty = 0;
			float tw = 1;
			float th = 1;
			D3DXCOLOR cl = { 1,0,0,0.2f };

			D3DXVECTOR2 offsetPos = pCollider->posOffset;
			float offsetRot = atan2f(offsetPos.y, offsetPos.x);
			float rot = transform.rotation + offsetRot;

			DrawSpriteColorRotate(
				texNo,
				x, y, w, h,
				tx, ty, tw, th,
				cl,
				rot
			);
		}
	}

	//gameObject.Draw();
}

void Ball::Rotate()
{
	if (GetFatherBall())
	{
		D3DXVECTOR2 fatherPos = GetFatherBall()->gameObject.transform.position;
		D3DXVECTOR2 sonPos = gameObject.transform.position;
		float radius = GetFatherArm()->length;
		float rot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x) + rotateSpeed;
		float x = fatherPos.x + radius * cosf(rot);
		float y = fatherPos.y - radius * sinf(rot);
		gameObject.transform.position = { x,y };
	}
}

float Ball::GetRotate()
{
	if (GetFatherArm())
	{
		D3DXVECTOR2 fatherPos = GetFatherBall()->transform.position;
		D3DXVECTOR2 sonPos = transform.position;
		float rot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x);
		return rot;
	}
	else
	{
		return -35.0f;
	}
}

void Ball::CreateDisplay(int num)
{
	displayNum = num;
	p_displays = new Display[num];
}

void Ball::UpdateRotateSpeed()
{
	//rotate speed
	if (!isCatch)
	{
		if (GetFatherArm())
		{
			D3DXVECTOR2 fatherPos = GetFatherBall()->transform.position;
			D3DXVECTOR2 sonPos = transform.position;
			float rot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x);
			rotateSpeed += -cosf(rot) * GRAVITY_A;

			rotateSpeed += (GetFatherBall()->rotateSpeed - rotateSpeed) * 0.02f;
			/*Arm* pArm = GetFatherArm();
			if (pArm)
			{
				if (pArm == pRightArm)
				{
					if (pRightArm)
						rotateSpeed += (pRightArm->pRightBall->rotateSpeed - rotateSpeed) * 0.03f;
				}
				if (pArm == pLeftArm)
				{
					if (pLeftArm)
						rotateSpeed += (pLeftArm->pLeftBall->rotateSpeed - rotateSpeed) * 0.03f;
				}
			}*/
			rotateSpeed = fmaxf(-MAX_ROTATE_SPEED, fminf(MAX_ROTATE_SPEED, rotateSpeed));
		}
	}
}

void Ball::RotateSon()
{
	if (GetSonArm())
	{
		Ball* pSonBall = GetSonBall();

		D3DXVECTOR2 fatherPos = transform.position;
		D3DXVECTOR2 sonPos = pSonBall->transform.position;
		float radius = GetSonArm()->length;
		float rot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x) + transform.rotation + pSonBall->rotateSpeed;
		float x = fatherPos.x + radius * cosf(rot);
		float y = fatherPos.y - radius * sinf(rot);
		pSonBall->transform.position = { x,y };
		pSonBall->RotateSon();
		{
			//Ball* pSonBall = GetSonBall();
			//D3DXVECTOR2 fatherPos = gameObject.transform.position;
			//D3DXVECTOR2 sonPos = pSonBall->gameObject.transform.position;
			//float radius = GetSonArm()->length;
			//float rot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x) + gameObject.transform.rotation + pSonBall->rotateSpeed;
			//float x = fatherPos.x + radius * cosf(rot);
			//float y = fatherPos.y - radius * sinf(rot);
			//pSonBall->gameObject.transform.position = { x,y };
			//pSonBall->RotateSon();
		}
		
	}
}

void Ball::RotateTwoSon()
{
	if (pLeftArm)
	{
		Ball* pSonBall = pLeftArm->pLeftBall;

		D3DXVECTOR2 fatherPos = transform.position;
		D3DXVECTOR2 sonPos = pSonBall->transform.position;
		float radius = pLeftArm->length;
		float rot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x) + transform.rotation + pSonBall->rotateSpeed;
		float x = fatherPos.x + radius * cosf(rot);
		float y = fatherPos.y - radius * sinf(rot);
		pSonBall->transform.position = { x,y };
		pSonBall->RotateSon();
	}
	if (pRightArm)
	{
		Ball* pSonBall = pRightArm->pRightBall;

		D3DXVECTOR2 fatherPos = transform.position;
		D3DXVECTOR2 sonPos = pSonBall->transform.position;
		float radius = pRightArm->length;
		float rot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x) + transform.rotation + pSonBall->rotateSpeed;
		float x = fatherPos.x + radius * cosf(rot);
		float y = fatherPos.y - radius * sinf(rot);
		pSonBall->transform.position = { x,y };
		pSonBall->RotateSon();
	}
}

void Ball::RotateDisplay()
{
	if (this != g_player.pBodyBall&&
		isCatch==false)
	{
		{
			if (GetFatherBall())
			{
				D3DXVECTOR2 fatherPos = GetFatherBall()->transform.position;
				D3DXVECTOR2 sonPos = transform.position;
				float newRot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x);
				float newRotMin = newRot - RADIANT(360.0f);
				float newRotMax = newRot + RADIANT(360.0f);

				float nowRot = displayRotation;

				float deltaMinRot = newRot;
				if (fabsf(deltaMinRot - nowRot) > fabsf(newRotMin - nowRot))
				{
					deltaMinRot = newRotMin;
				}
				if (fabsf(deltaMinRot - nowRot) > fabsf(newRotMax - nowRot))
				{
					deltaMinRot = newRotMax;
				}
				displayRotation = nowRot + (deltaMinRot - nowRot) / 5.0f;
				float* pRot = &displayRotation;
				if (*pRot > RADIANT(360))
				{
					*pRot -= RADIANT(360);
				}
				if (*pRot < RADIANT(0))
				{
					*pRot += RADIANT(360);
				}
				// fminf(RADIANT(360.0f), fmaxf(0, nowRot + (deltaMinRot - nowRot) / 5.0f));
			}
		}
		{
			//if (GetFatherBall())
		//{
		//	D3DXVECTOR2 fatherPos = GetFatherBall()->gameObject.transform.position;
		//	D3DXVECTOR2 sonPos = gameObject.transform.position;
		//	float newRot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x);
		//	float newRotMin = newRot - RADIANT(360.0f);
		//	float newRotMax = newRot + RADIANT(360.0f);

		//	float nowRot = gameObject.transform.rotation;

		//	float deltaMinRot = newRot;
		//	if (fabsf(deltaMinRot - nowRot) > fabsf(newRotMin - nowRot))
		//	{
		//		deltaMinRot = newRotMin;
		//	}
		//	if (fabsf(deltaMinRot - nowRot) > fabsf(newRotMax - nowRot))
		//	{
		//		deltaMinRot = newRotMax;
		//	}
		//	gameObject.transform.rotation = nowRot + (deltaMinRot - nowRot) / 5.0f;
		//	float* pRot = &gameObject.transform.rotation;
		//	if (*pRot > RADIANT(360))
		//	{
		//		*pRot -= RADIANT(360);
		//	}
		//	if (*pRot < RADIANT(0))
		//	{
		//		*pRot += RADIANT(360);
		//	}
		//	// fminf(RADIANT(360.0f), fmaxf(0, nowRot + (deltaMinRot - nowRot) / 5.0f));
		//}
		}
	}
}

void Ball::Pull(PullType type)
{
	if (!isCatch)
	{
		if (type == PullType::same)
		{
			if (rotateSpeed > 0)
			{
				rotateSpeed += PULL_A;
			}
			else
			{
				rotateSpeed -= PULL_A;
			}
		}
		else if (type == PullType::left)
		{
			rotateSpeed -= PULL_A;
		}
		else if (type == PullType::right)
		{
			rotateSpeed += PULL_A;
		}
	}
}

Arm::~Arm()
{
}

void Arm::Update()
{
}

void Arm::Draw()
{
	Animation* pAnimation = &display.p_animes[display.animeID];
	D3DXVECTOR4 uv = pAnimation->p_pieceUVs[pAnimation->pieceID];

	int texNo = display.texNo;
	D3DXVECTOR2 leftPos = pLeftBall->transform.position;
	D3DXVECTOR2 rightPos = pRightBall->transform.position;
	D3DXVECTOR2 deltaPos = rightPos - leftPos;

	float x = ((leftPos + rightPos) / 2.0f).x;
	float y = ((leftPos + rightPos) / 2.0f).y;
	float w = D3DXVec2Length(&deltaPos);
	float h = display.size.y;

	float ratio = w / ARM_LENGTH_NORMAL;
	float tx = uv.x;
	float ty = uv.y;
	float tw = uv.z * ratio;
	float th = uv.w;
	D3DXCOLOR cl = display.color;

	float rot = atan2f(-deltaPos.y, deltaPos.x);

	DrawSpriteColorRotate(
		texNo,
		x, y, w, h,
		tx, ty, tw, th,
		cl,
		rot
	);
}

void Player::CreateBall(int num)
{
	ballNum = num;
	p_balls = new Ball[num];
}

void Player::CreateArm(int num)
{
	armNum = num;
	p_arms = new Arm[num];
}

void Player::Reset()
{
	//if (ballNum>0)delete p_balls;
	//if (armNum>0)delete p_arms;
	p_balls = nullptr;
	p_arms = nullptr;

	ballNum = 0;
	armNum = 0;

	state = PlayerState::stop;

	pBodyBall = nullptr;
	pLeftBall = nullptr;
	pRightBall = nullptr;
	pHoldBall = nullptr;
	moveSpeed = { 0,0 };
}

void Player::Update()
{
	//check player state
	{
		if (pLeftBall->isCatch && pRightBall->isCatch)
		{
			ChangeState(PlayerState::twoHand);
		}
		if (pLeftBall->isCatch && !pRightBall->isCatch)
		{
			ChangeState(PlayerState::leftHand);
		}
		if (!pLeftBall->isCatch && pRightBall->isCatch)
		{
			ChangeState(PlayerState::rightHand);
		}
		if (!pLeftBall->isCatch && !pRightBall->isCatch)
		{
			ChangeState(PlayerState::fly);
		}
	}

	//make ball rotate
	if (pHoldBall)
	{
		pHoldBall->RotateSon();
	}
	else
	{
		//move speed
		{
			//y
			moveSpeed.y += GRAVITY_FLY;
			moveSpeed.y = fmaxf(-30.0f, fminf(15.0f, moveSpeed.y));

			//x
			float vx = moveSpeed.x;
			if (vx != 0)
			{
				vx = vx > 0 ? (vx - DRAG_FLY) : (vx + DRAG_FLY);
				vx = vx > 0 ? fmaxf(MIN_JUMP_SPEED_X, vx) : fminf(-MIN_JUMP_SPEED_X, vx);
				moveSpeed.x = fmaxf(-30.0f, fminf(30.0f, vx));
			}
		}

		pBodyBall->RotateTwoSon();
	}

	//update ball
	for (int i = 0; i < ballNum; i++)
	{
		Ball* pBall = &p_balls[i];
		pBall->Update();
		pBall->transform.position += moveSpeed;
	}
}

void Player::Draw()
{
	for (int i = 0; i < armNum; i++)
	{
		Arm* pArm = &p_arms[i];
		pArm->Draw();
	}
	for (int i = 0; i < ballNum; i++)
	{
		Ball* pBall = &p_balls[i];
		pBall->Draw();
	}
}

void Player::Pull(PullType type)
{
	for (int i = 0; i < ballNum; i++)
	{
		Ball* pBall = &p_balls[i];
		pBall->Pull(type);
	}
}


void Player::ChangeState(PlayerState state)
{
	if (this->state == state)return;
	else
	{
		//exit state
		switch (this->state)
		{
		case PlayerState::leftHand:
		{
			g_player.pHoldBall->rotateSpeed = g_player.pRightBall->rotateSpeed;
		}
		break;
		case PlayerState::rightHand:
		{
			g_player.pHoldBall->rotateSpeed = g_player.pLeftBall->rotateSpeed;
		}
		break;
		case PlayerState::twoHand:
		{
			g_player.pRightBall->rotateSpeed = g_player.pLeftBall->rotateSpeed = 0;
		}
		break;
		case PlayerState::fly:
		{
			moveSpeed = { 0,0 };
		}
		break;
		}
		//enter state
		switch (state)
		{
		case PlayerState::leftHand:
		{
			pHoldBall = pLeftBall;
			pHoldBall->rotateSpeed = 0;
			SetCmrLookAt(&pHoldBall->transform);
		}
		break;
		case PlayerState::rightHand:
		{
			pHoldBall = pRightBall;
			pHoldBall->rotateSpeed = 0;
			SetCmrLookAt(&pHoldBall->transform);
		}
		break;
		case PlayerState::twoHand:
		{
			pHoldBall = pLeftBall;
			pHoldBall->rotateSpeed = 0;
		}
		break;
		case PlayerState::fly:
		{
			//get start fly move speed
			{
				float rotSpd = pBodyBall->rotateSpeed;
				//rot spd to move spd
				{
					//float rotSpd = pBodyBall->rotateSpeed;
					//D3DXVECTOR2 fatherPos = pBodyBall->GetFatherBall()->transform.position;
					//D3DXVECTOR2 sonPos = pBodyBall->transform.position;
					//D3DXVECTOR2 deltaPos = (sonPos - fatherPos);
					//deltaPos = deltaPos / D3DXVec2Length(&deltaPos);
					//D3DXVECTOR2 spdDir = rotSpd > 0 ?
					//	D3DXVECTOR2(deltaPos.y, -deltaPos.x) :
					//	D3DXVECTOR2(-deltaPos.y, deltaPos.x);

					//float spdMin = 5.0f;
					//float spdMax = 25.0f;
					//float spdAbs = spdMin + fabsf(rotSpd) / MAX_ROTATE_SPEED * (spdMax - spdMin);
					//moveSpeed = spdDir * spdAbs;
					////moveSpeed = { spdDir.x > 0 ? 0.5f : -0.5f, fmaxf(-1.0f,spdDir.y) * 15 };
				}
			
				//left right to move spd
				{
					D3DXVECTOR2 fatherPos = pBodyBall->GetFatherBall()->transform.position;
					D3DXVECTOR2 sonPos = pBodyBall->transform.position;
					float rot = atan2f(-(sonPos - fatherPos).y, (sonPos - fatherPos).x);
					float vy = fmaxf(0.6f, fabsf(rotSpd) / MAX_ROTATE_SPEED) * (-MAX_JUMP_SPEED_Y);
					float vx = MAX_JUMP_SPEED_X;
					
					if (rotSpd <0)
					{
						if (rot<RADIANT(-90.0f) || rot>RADIANT(90.0f))//fly left
						{
							moveSpeed = { -vx ,vy };
						}
						else
						{
							moveSpeed = { MIN_JUMP_SPEED_X,0 };
						}
					}
					else if(rotSpd>0)
					{
						if (rot<RADIANT(90.0f) && rot>RADIANT(-90.0f))//fly right
						{
							moveSpeed = { vx, vy };
						}
						else
						{
							moveSpeed = { -MIN_JUMP_SPEED_X,0 };
						}
					}
					else
					{
						moveSpeed = { 0,0 };
					}

				}

				//set son rotate spd
				pLeftBall->rotateSpeed =
					pRightBall->rotateSpeed = (rotSpd > 0 ? 1 : -1) * RADIANT(6.0f);//pBodyBall->rotateSpeed * 0.05f;
			}		


			pHoldBall = nullptr;
			SetCmrLookAt(&pBodyBall->transform);
		}
		break;
		}
		this->state = state;
	}
}
