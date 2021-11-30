#include "main.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "swinger.h"
#include "camera.h"
#include "bg.h"
#include "collision.h"
//#include "block.h"
#include "bullet.h"

#include <imgui.h>

//アームの長さ
#define ARM_NORMAL_LENGTH  (80.0f)
#define ARM_SHORT_LENGTH  (40.0f)
#define ARM_LONG_LENGTH  (160.0f)
#define SWINGER_SIZE_WIDTH (45.0f)
#define SWINGER_SIZE_HEIGHT (SWINGER_SIZE_WIDTH)
//キーボードボタンの設定
#define KEY_LEFT_SHAKE (DIK_W)
#define KEY_RIGHT_SHAKE (DIK_O)
#define KEY_AUTO_SHAKE (DIK_SPACE)

#define KEY_LEFT_CATCH (DIK_E)
#define KEY_RIGHT_CATCH (DIK_I)

#define KEY_LEFT_SKILL (DIK_R)
#define KEY_RIGHT_SKILL (DIK_U)
//==============================================================
void SetSwinger(int swingerID,
	float sizeX, float sizeY,
	D3DXCOLOR color,
	ARM* armLeft, ARM* armRight,
	float rotate,
	bool isCatch
);
void SetArm(int armID,
	float length,
	SWINGER_BASE* swingerLeft,
	SWINGER_BASE* swingerRight
);
void InputPull(SWINGER_BASE* swinger);
void UpdateSwingerRotate(SWINGER_BASE* swinger, bool isRotateLeft);
void UpdateSwingerRotateFly(SWINGER_BASE* swinger, bool isRotateLeft);

void UpdateSwingerPos();
void InputCatch();

void ChangeSwingerRotateInfo();
void CheckPlayerState();
void SetPlayerSWVelocity(bool isOn);

void ResetClimbot();

//skill
void SkillShoot();
void SkillScale();

//imgui
void ImGui_ShowPlayerState();
//==============================================================

int g_tex;
float g_gravity = 0.8f;
float g_pull = 0.8f;
D3DXVECTOR2 g_center;

//0-0-0-0-0
SWINGER_BASE g_swinger[MAX_SWINGER];
ARM g_arm[MAX_SWINGER-1];
PLAYER_SW g_playerSW;

//
//bool g_isLeftHead;
//bool g_isLeftVLeft;
int g_centerID;//片手状態、円心になった振り子の添え字
int g_bodyID;//body振り子の添え字
int g_leftID;
int g_rightID;
int g_gameState;

enum GameState
{
	waitToStart,
	playing,
	relife,
	pause,
};


void SetPlayerSW(D3DXVECTOR2 move)
{
	D3DXVECTOR2 pos = g_playerSW.p_body->obj.worldPos;
	pos += move;
	
	//for (int y = 0; y < MAP_BLOCK_Y_NUM; y++)
	//{
	//	for (int x = 0; x < MAP_BLOCK_X_NUM; x++)
	//	{
	//		BLOCK* block = GetBlock(y, x);
	//		if (block->use)
	//		{
	//			if (block->colType == BlockColType::box)
	//			{
	//				//left hand
	//				D3DXVECTOR2 pos1 = pos;
	//				D3DXVECTOR2 pos2 = block->obj.worldPos;
	//				D3DXVECTOR2 size1 = g_swinger[g_bodyID].obj.size;
	//				D3DXVECTOR2 size2 = block->obj.size;


	//				int direction = CollisionBBDir4_2(pos1, pos2, size1, size2);

	//				switch (direction)
	//				{
	//				case 0://up
	//					pos = { pos.x, pos2.y - size2.y / 2 - size1.y / 2 };
	//					break;
	//				case 1://right
	//					pos = { pos2.x + size2.x / 2 + size1.x / 2, pos.y };
	//					break;
	//				case 2://down
	//					pos = { pos.x, pos2.y + size2.y / 2 + size1.y / 2 };
	//					break;
	//				case 3://left
	//					pos = { pos2.x - size2.x / 2 - size1.x / 2, pos.y };
	//					break;
	//				case -1://none collision
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}

	g_playerSW.p_body->obj.worldPos = pos;
}
void ResetClimbot()//この前に全部初期化される必要がある
{
	{
		//手動で設置
		//g_swinger[0].obj.worldPos = GetBlock(41,0)->obj.worldPos;
		SetSwinger(0,
			SWINGER_SIZE_WIDTH, SWINGER_SIZE_HEIGHT,
			{ 1,0,0,1 },
			nullptr, &g_arm[0],
			0,
			true);
		SetArm(0, ARM_NORMAL_LENGTH, &g_swinger[0], &g_swinger[1]);
		SetSwinger(1,
			SWINGER_SIZE_WIDTH, SWINGER_SIZE_HEIGHT,
			{ 1,1,1,1 },
			&g_arm[0], &g_arm[1],
			0,
			false);
		SetArm(1, ARM_NORMAL_LENGTH, &g_swinger[1], &g_swinger[2]);
		SetSwinger(2,
			SWINGER_SIZE_WIDTH, SWINGER_SIZE_HEIGHT,
			{ 0,0,1,1 },
			&g_arm[1], nullptr,
			0,
			false);
		//set playerSW
		g_playerSW.p_body = &g_swinger[1];
		g_playerSW.p_leftHand = &g_swinger[0];
		g_playerSW.p_rightHand = &g_swinger[2];
		g_playerSW.state = PlayerState::leftHand;
		g_playerSW.velocity = D3DXVECTOR2(0, 0);
		ChangeSwingerRotateInfo();

		SetCmrLookAt(&g_swinger[g_centerID].obj);
		//set swinger pos 
		UpdateSwingerPos();

		//important
		g_gameState = GameState::waitToStart;
	}
}

HRESULT InitSwinger(void)
{
	g_tex = LoadTexture("data/TEXTURE/majo.png");
	g_center = D3DXVECTOR2(SCREEN_WIDTH / 2, 10.0f);
	g_gravity = 0.8f;
	g_pull = 9.0f;
	/*g_isLeftHead = true;
	g_isLeftVLeft = false;*/
	g_centerID = 0;
	g_bodyID = 1;
	g_leftID = 0;
	g_rightID = 2;
	g_gameState = GameState::waitToStart;


	//ロボットの作成！
	//アームの初期化
	for (int i = 0; i < 4; i++)
	{
		g_arm[i].length = ARM_NORMAL_LENGTH;
		g_arm[i].p_swingerLeft = 
			g_arm[i].p_swingerRight = nullptr;
		g_arm[i].rotateLeft =
			g_arm[i].rotateRight = 0;
	}
	//振り子の初期化
	for (int i = 0; i < 5; i++)
	{
		g_swinger[i].use = false;

		g_swinger[i].obj.worldPos = { 0,0 };
		g_swinger[i].obj.size = { 45,45 };
		g_swinger[i].obj.color = { 0,0,0,0 };
		g_swinger[i].p_armLeft = 
			g_swinger[i].p_armRight = nullptr;

		g_swinger[i].p_centerPos = nullptr;
		g_swinger[i].p_radius = nullptr;
		g_swinger[i].rotateSpd = 0.0f;
		g_swinger[i].rotate = 0.0f;

		g_swinger[i].isCatch = false;
	}
	//playerSW初期化
	{
		g_playerSW.p_body =
			g_playerSW.p_rightHand = 
			g_playerSW.p_leftHand = nullptr;
		g_playerSW.state = PlayerState::stop;
		g_playerSW.velocity = {0,0};
	}


	//初期クライモット設定
	ResetClimbot();

	return S_OK;
}

void UninitSwinger(void)
{
}

void UpdateSwinger(void)
{
	UpdateSwingerPos();

	InputCatch();
	SkillScale();
	SkillShoot();

	CheckPlayerState();

	//imgui
	ImGui_ShowPlayerState();

	//g_swinger[g_leftID].canCatch = false;
	//g_swinger[g_rightID].canCatch = false;

}

void DrawSwinger(void)
{
	for (int i = 0; i < MAX_SWINGER; i++)
	{
		SWINGER_BASE* swinger = &g_swinger[i];
		if (swinger->use)
		{
			float x = swinger->obj.worldPos.x;
			float y = swinger->obj.worldPos.y;
			float w = swinger->obj.size.x;
			float h = swinger->obj.size.y;
			float tx = 0.15;
			float ty = 0.15;
			float tw = 0.01f;
			float th = 0.01f;
			D3DXCOLOR color = swinger->obj.color;

			DrawSpriteColor(g_tex,
				x, y, w, h,
				tx, ty, tw, th,
				color);
		}
	}
}

//------------------------
//このcppで使う関数
//------------------------
//振り子を設置
void SetSwinger(int swingerID,
	float sizeX, float sizeY,
	D3DXCOLOR color,
	ARM* armLeft, ARM* armRight,
	float rotate,
	bool isCatch
)
{
	g_swinger[swingerID].use = true;

	//g_swinger[swingerID].obj.worldPos = { posX,posY };
	g_swinger[swingerID].obj.size = { sizeX,sizeY };
	g_swinger[swingerID].obj.color = color;
	g_swinger[swingerID].p_armLeft = armLeft;
	g_swinger[swingerID].p_armRight = armRight;
	g_swinger[swingerID].rotate = rotate;
	g_swinger[swingerID].isCatch = isCatch;
}
//アームの設置
void SetArm(int armID,
	float length,
	SWINGER_BASE* swingerLeft,
	SWINGER_BASE* swingerRight
	)
{
	g_arm[armID].length = length;
	g_arm[armID].p_swingerLeft = swingerLeft;
	g_arm[armID].p_swingerRight = swingerRight;
}



void InputPull(SWINGER_BASE* swinger)
{
	if (g_playerSW.state == PlayerState::leftHand ||
		g_playerSW.state == PlayerState::rightHand)
	{
		if (GetKeyboardTrigger(KEY_AUTO_SHAKE))
		{
			D3DXVECTOR2 center = *swinger->p_centerPos;
			float radius = *swinger->p_radius;
			float deltaY = -(center.y - swinger->obj.worldPos.y);
			float sin = deltaY / radius;
			if (swinger->rotateSpd > 0)
			{
				swinger->rotateSpd += g_pull * sin;
			}
			else
			{
				swinger->rotateSpd -= g_pull * sin;
			}
		}
		if (IsButtonTriggered(1, BUTTON_LEFT))
		{
			D3DXVECTOR2 center = *swinger->p_centerPos;
			float radius = *swinger->p_radius;
			float deltaY = -(center.y - swinger->obj.worldPos.y);
			float sin = deltaY / radius;
			swinger->rotateSpd -= g_pull * sin;
		}
		if (IsButtonTriggered(1, BUTTON_RIGHT))
		{
			D3DXVECTOR2 center = *swinger->p_centerPos;
			float radius = *swinger->p_radius;
			float deltaY = -(center.y - swinger->obj.worldPos.y);
			float sin = deltaY / radius;
			swinger->rotateSpd += g_pull * sin;
		}
	}
	else if(g_playerSW.state==PlayerState::fly)
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
void UpdateSwingerRotate(SWINGER_BASE* swinger,bool isRotateLeft)
{
	D3DXVECTOR2 center = *swinger->p_centerPos;
	float radius = *swinger->p_radius;
	float deltaX = center.x - swinger->obj.worldPos.x;
	float cos = deltaX / radius;
	swinger->rotateSpd += g_gravity * cos;

	float otherForce = 0;
	ARM* armLeft = swinger->p_armLeft;
	ARM* armRight = swinger->p_armRight;
	if (armLeft)
	{
		otherForce += (armLeft->p_swingerLeft->rotateSpd - swinger->rotateSpd) * 0.5f;
	}
	if (armRight)
	{
		otherForce += (armRight->p_swingerRight->rotateSpd - swinger->rotateSpd) * 0.5f;
	}
	swinger->rotateSpd += otherForce * 0.05f;
	InputPull(swinger);
	swinger->rotate += swinger->rotateSpd;
	if (swinger->rotate > 360)
	{
		swinger->rotate -= 360.0f;
	}
	if (swinger->rotate < 0)
	{
		swinger->rotate += 360.0f;
	}
	
	if (isRotateLeft)
	{
		ARM* arm = swinger->p_armRight;
		if (arm)
		{
			arm->rotateLeft = swinger->rotate;
			arm->rotateRight = (int)(arm->rotateLeft + 180.0f) % 360;
		}
	}
	else
	{
		ARM* arm = swinger->p_armLeft;
		if (arm)
		{
			arm->rotateRight = swinger->rotate;
			arm->rotateLeft = (int)(arm->rotateRight + 180.0f) % 360;
		}
	}
}
void UpdateSwingerRotateFly(SWINGER_BASE* swinger, bool isRotateLeft)
{
	InputPull(swinger);
	swinger->rotate += swinger->rotateSpd;
	if (swinger->rotate > 360)
	{
		swinger->rotate -= 360.0f;
	}
	if (swinger->rotate < 0)
	{
		swinger->rotate += 360.0f;
	}

	if (isRotateLeft)
	{
		ARM* arm = swinger->p_armRight;
		if (arm)
		{
			arm->rotateLeft = swinger->rotate;
			arm->rotateRight = (int)(arm->rotateLeft + 180.0f) % 360;
		}
	}
	else
	{
		ARM* arm = swinger->p_armLeft;
		if (arm)
		{
			arm->rotateRight = swinger->rotate;
			arm->rotateLeft = (int)(arm->rotateRight + 180.0f) % 360;
		}
	}
}
void UpdateSwingerPos()
{
	//MyLog("rotate spd: %lf\n", g_swinger[g_bodyID].rotateSpd);
	switch (g_playerSW.state)
	{
	case PlayerState::rightHand:
	{
		SWINGER_BASE* swinger0 = &g_swinger[g_centerID];
		SWINGER_BASE* swinger1 = swinger0->p_armLeft->p_swingerLeft;
		while (true)
		{
			D3DXVECTOR2 center = *swinger1->p_centerPos;
			float angle = swinger1->rotate * 3.14f / 180.0f;
			float radius = *swinger1->p_radius;
			swinger1->obj.worldPos.x = center.x + radius * cosf(angle);
			swinger1->obj.worldPos.y = center.y - radius * sinf(angle);

			UpdateSwingerRotate(swinger1, true);

			swinger0 = swinger1;
			if (swinger0->p_armLeft)
			{
				swinger1 = swinger0->p_armLeft->p_swingerLeft;
			}
			else
			{
				break;
			}
		}
	}
		break;
	case PlayerState::leftHand:
	{
		SWINGER_BASE* swinger0 = &g_swinger[g_centerID];
		//test
		//swinger0->obj.worldPos += D3DXVECTOR2(0,1);
		SWINGER_BASE* swinger1 = swinger0->p_armRight->p_swingerRight;
		while (true)
		{
			D3DXVECTOR2 center = *swinger1->p_centerPos;
			float angle = swinger1->rotate * 3.14f / 180.0f;
			float radius = *swinger1->p_radius;
			swinger1->obj.worldPos.x = center.x + radius * cosf(angle);
			swinger1->obj.worldPos.y = center.y - radius * sinf(angle);

			UpdateSwingerRotate(swinger1, false);

			swinger0 = swinger1;
			if (swinger0->p_armRight)
			{
				swinger1 = swinger0->p_armRight->p_swingerRight;
			}
			else
			{
				break;
			}
		}
	}
		break;
	case PlayerState::twoHand:
		
		break;
	case PlayerState::fly:
		SWINGER_BASE* swinger0 = &g_swinger[g_centerID];
		SWINGER_BASE* swinger1 = swinger0->p_armLeft->p_swingerLeft;
		while (true)
		{
			D3DXVECTOR2 center = *swinger1->p_centerPos;
			float angle = swinger1->rotate * 3.14f / 180.0f;
			float radius = *swinger1->p_radius;
			swinger1->obj.worldPos.x = center.x + radius * cosf(angle);
			swinger1->obj.worldPos.y = center.y - radius * sinf(angle);

			UpdateSwingerRotateFly(swinger1,true);

			swinger0 = swinger1;
			if (swinger0->p_armLeft)
			{
				swinger1 = swinger0->p_armLeft->p_swingerLeft;
			}
			else
			{
				break;
			}
		}
		swinger0 = &g_swinger[g_centerID];
		swinger1 = swinger0->p_armRight->p_swingerRight;
		while (true)
		{
			D3DXVECTOR2 center = *swinger1->p_centerPos;
			float angle = swinger1->rotate * 3.14f / 180.0f;
			float radius = *swinger1->p_radius;
			swinger1->obj.worldPos.x = center.x + radius * cosf(angle);
			swinger1->obj.worldPos.y = center.y - radius * sinf(angle);

			UpdateSwingerRotateFly(swinger1,false);

			swinger0 = swinger1;
			if (swinger0->p_armRight)
			{
				swinger1 = swinger0->p_armRight->p_swingerRight;
			}
			else
			{
				break;
			}
		}

		//fly 
		{

			SWINGER_BASE* swinger = g_playerSW.p_body;
			swinger->obj.worldPos += g_playerSW.velocity;

			float velX = g_playerSW.velocity.x;
			float velMin = 5.0f;
			if (velX > velMin)
			{
				velX -= g_gravity/5;
				if (velX < velMin)velX = velMin;
			}
			else if(velX< -velMin)
			{
				velX += g_gravity/5;
				if (velX > -velMin)velX = -velMin;
			}
			else
			{
				if (velX > 0) velX = velMin;
				else if (velX < 0) velX = -velMin;
				else velX = 0;
			}
			g_playerSW.velocity.x = velX;
			g_playerSW.velocity.y = max(-12.0f, min(12.0f, g_playerSW.velocity.y + g_gravity/1.3f));

			//check outside map
			{
				bool isOut = true;
				for (int i = 0; i < MAX_SWINGER; i++)
				{
					SWINGER_BASE* swinger = &g_swinger[i];
					if (swinger->use)
					{
						float minX = swinger->obj.worldPos.x - swinger->obj.size.x / 2;
						float maxX = swinger->obj.worldPos.x + swinger->obj.size.x / 2;
						float minY = swinger->obj.worldPos.y - swinger->obj.size.y / 2;
						float maxY = swinger->obj.worldPos.y + swinger->obj.size.y / 2;

						if (maxX<GetBoundary().x ||
							minX>GetBoundary().y ||
							maxY<GetBoundary().z ||
							minY>GetBoundary().w)
						{
							isOut = true;
						}
						else
						{
							isOut = false;
							break;
						}
					}
				}

				if (isOut)
				{
					ResetClimbot();
				}
			}
		}
		break;
	}
}

void CatchBlock(SWINGER_BASE *swinger)
{
	//BLOCK* block = swinger->p_catchBlock;
	//if (block)
	//{
	//	if (block->type == 3)
	//	{
	//		AddBlockSonObj(block, &swinger->obj);
	//	}
	//	else
	//	{
	//	}
	//}
	//swinger->isCatch = true;
}
void ReleaseBlock(SWINGER_BASE* swinger)
{
	//BLOCK* block = swinger->p_catchBlock;
	//if (block)
	//{
	//	if (block->type == 3)
	//	{
	//		RemoveBlockSonObj(block, &swinger->obj);
	//	}
	//	else
	//	{
	//	}
	//}
	//swinger->p_catchBlock = nullptr;
	//swinger->isCatch = false;
}
void InputCatch()
{
	if (g_gameState == GameState::playing)
	{
		g_swinger[g_leftID].isCatch = false;
		g_swinger[g_rightID].isCatch = false;
	}
	
	if (g_swinger[g_leftID].canCatch &&
		!g_swinger[g_leftID].isCatch)
	{
		if ((GetKeyboardPress(KEY_LEFT_CATCH) || IsButtonPressed(1, BUTTON_L2)))
		{
			//g_swinger[g_leftID].isCatch = true;
			CatchBlock(&g_swinger[g_leftID]);

			//first catch and start playing
			{
				if (g_gameState != GameState::playing)
				{
					g_gameState = GameState::playing;
				}
			}
		}
		else
		{
			ReleaseBlock(&g_swinger[g_leftID]);
		}
	}


	if (g_swinger[g_rightID].canCatch &&
		!g_swinger[g_rightID].isCatch)
	{
		if ((GetKeyboardPress(KEY_RIGHT_CATCH) || IsButtonPressed(1, BUTTON_R2)))
		{
			//g_swinger[g_rightID].isCatch = true;
			CatchBlock(&g_swinger[g_rightID]);

			//first catch and start playing
			{
				if (g_gameState != GameState::playing)
				{
					g_gameState = GameState::playing;
				}
			}
		}
		else
		{
			ReleaseBlock(&g_swinger[g_rightID]);
		}
	}

	if (g_gameState == GameState::waitToStart)
	{
		g_swinger[g_leftID].isCatch = true;
		g_swinger[g_rightID].isCatch = false;
	}
}

void ChangeSwingerRotateInfo()
{
	SWINGER_BASE* swinger0 = nullptr;
	SWINGER_BASE* swinger1 = nullptr;
	switch (g_playerSW.state)
	{
	case PlayerState::leftHand:
	{
		g_centerID = g_leftID;
		swinger0 = &g_swinger[g_centerID];
		swinger1 = swinger0->p_armRight->p_swingerRight;

		swinger0->p_centerPos = nullptr;
		swinger0->p_radius = nullptr;
		swinger0->rotateSpd = 0;
		swinger0->rotate = 0;

		while (true)
		{
			swinger1->p_centerPos = &swinger0->obj.worldPos;
			swinger1->p_radius = &swinger0->p_armRight->length;
			swinger1->rotateSpd = 0;
			swinger1->rotate = swinger0->p_armRight->rotateRight;

			swinger0 = swinger1;
			if (swinger0->p_armRight)
			{
				swinger1 = swinger0->p_armRight->p_swingerRight;
				//MyLog("swinger0  %lf\n", swinger0->obj.size.x);
				//MyLog("swinger1  %lf\n", swinger1->obj.size.x);
			}
			else
			{
				break;
			}
		}
	}
	break;
	case PlayerState::rightHand:
	{
		g_centerID = g_rightID;
		swinger0 = &g_swinger[g_centerID];
		swinger1 = swinger0->p_armLeft->p_swingerLeft;

		swinger0->p_centerPos = nullptr;
		swinger0->p_radius = nullptr;
		swinger0->rotateSpd = 0;
		swinger0->rotate = 0;

		while (true)
		{
			swinger1->p_centerPos = &swinger0->obj.worldPos;
			swinger1->p_radius = &swinger0->p_armLeft->length;
			swinger1->rotateSpd = 0;
			swinger1->rotate = swinger0->p_armLeft->rotateLeft;


			swinger0 = swinger1;
			if (swinger0->p_armLeft)
			{
				swinger1 = swinger0->p_armLeft->p_swingerLeft;
			}
			else
			{
				break;
			}
		}
	}
	break;
	case PlayerState::twoHand:

		break;
	case PlayerState::fly:
	{
		g_centerID = g_bodyID;
		swinger0 = &g_swinger[g_centerID];
		swinger1 = swinger0->p_armLeft->p_swingerLeft;
		float rotateSpd = swinger0->rotateSpd / 10;

		swinger0->p_centerPos = nullptr;
		swinger0->p_radius = nullptr;
		swinger0->rotateSpd = 0;
		swinger0->rotate = 0;
		while (true)
		{
			swinger1->p_centerPos = &swinger0->obj.worldPos;
			swinger1->p_radius = &swinger0->p_armLeft->length;
			swinger1->rotateSpd = rotateSpd;
			swinger1->rotate = swinger0->p_armLeft->rotateLeft;

			swinger0 = swinger1;
			if (swinger0->p_armLeft)
			{
				swinger1 = swinger0->p_armLeft->p_swingerLeft;
			}
			else
			{
				break;
			}
		}
		swinger0 = &g_swinger[g_centerID];
		swinger1 = swinger0->p_armRight->p_swingerRight;
		while (true)
		{
			swinger1->p_centerPos = &swinger0->obj.worldPos;
			swinger1->p_radius = &swinger0->p_armRight->length;
			swinger1->rotateSpd = rotateSpd;
			swinger1->rotate = swinger0->p_armRight->rotateRight;

			swinger0 = swinger1;
			if (swinger0->p_armRight)
			{
				swinger1 = swinger0->p_armRight->p_swingerRight;
			}
			else
			{
				break;
			}
		}
	}
	break;
	}
}
void CheckPlayerState()
{
	if (g_swinger[g_leftID].isCatch == false &&
		g_swinger[g_rightID].isCatch == false)
	{
		if (g_playerSW.state != PlayerState::fly)
		{
			g_playerSW.state = PlayerState::fly;
			SetCmrLookAt(&g_swinger[g_bodyID].obj);
			SetPlayerSWVelocity(true);
			ChangeSwingerRotateInfo();
		}
	}
	else if (g_swinger[g_leftID].isCatch == true &&
		g_swinger[g_rightID].isCatch == false)
	{
		if (g_playerSW.state != PlayerState::leftHand)
		{
			g_playerSW.state = PlayerState::leftHand;
			SetCmrLookAt(&g_swinger[g_leftID].obj);
			ChangeSwingerRotateInfo();
			SetPlayerSWVelocity(false);
		}
	}
	else if (g_swinger[g_leftID].isCatch == false &&
		g_swinger[g_rightID].isCatch == true)
	{
		if (g_playerSW.state != PlayerState::rightHand)
		{
			g_playerSW.state = PlayerState::rightHand;
			SetCmrLookAt(&g_swinger[g_rightID].obj);
			ChangeSwingerRotateInfo();
			SetPlayerSWVelocity(false);
		}
	}
	else if (g_swinger[g_leftID].isCatch == true &&
		g_swinger[g_rightID].isCatch == true)
	{
		if (g_playerSW.state != PlayerState::twoHand)
		{
			g_playerSW.state = PlayerState::twoHand;
			//SetCmrLookAt(&g_swinger[g_bodyID].obj);
			ChangeSwingerRotateInfo();
			SetPlayerSWVelocity(false);
		}
	}
}
void SetPlayerSWVelocity(bool isOn)
{
	if (isOn)
	{
		{
			float v = 12.0f;
			//MyLog("body rotate %lf\n", g_playerSW.p_body->rotate);
			if (fabsf(g_swinger[g_bodyID].rotate - 270.0f) < 30.0f ||
				fabsf(g_swinger[g_bodyID].rotateSpd) < 2.5f)
			{
				g_playerSW.velocity.x = 0;
				g_playerSW.velocity.y = 0;
			}
			else if (fabsf(g_swinger[g_bodyID].rotate - 90.0f) < 60.0f)
			{
				g_playerSW.velocity.x = 0;
				g_playerSW.velocity.y = -v * 4;
			}
			else
			{
				if (g_swinger[g_bodyID].rotate > 90.0f &&
					g_swinger[g_bodyID].rotate < 270.0f)
				{
					v = -v;
				}
				else
				{
					v = v;
				}
				float angle = g_playerSW.p_body->rotate * 3.14f / 180.0f;
				float cos = fabsf(cosf(angle));
				float sin = fabsf(sinf(angle));
				g_playerSW.velocity.x = v * (0.3f + sin);
				g_playerSW.velocity.y = -fabsf(v) * 4 - fabsf(v) * cos;
			}
		}

	}
	else
	{
		g_playerSW.velocity.x = 0;
		g_playerSW.velocity.y = 0;
	}
}

//skill
void SkillShoot()
{
	if (IsButtonTriggered(1, BUTTON_L) ||
		GetKeyboardTrigger(KEY_LEFT_SKILL))
	{
		//MyLog("shoot \n");
		SetBullet(g_swinger[g_leftID].obj.worldPos);
	}
}

void ScaleArm(float nextLength)
{
	switch (g_playerSW.state)
	{
	case PlayerState::rightHand:
	{
		SWINGER_BASE* swinger0 = &g_swinger[g_centerID];
		SWINGER_BASE* swinger1 = swinger0->p_armLeft->p_swingerLeft;
		while (true)
		{


			swinger0 = swinger1;
			if (swinger0->p_armLeft)
			{
				swinger1 = swinger0->p_armLeft->p_swingerLeft;
			}
			else
			{
				break;
			}
		}
	}
	break;
	case PlayerState::leftHand:
	{
		SWINGER_BASE* swinger0 = &g_swinger[g_centerID];
		SWINGER_BASE* swinger1 = swinger0->p_armRight->p_swingerRight;
		while (true)
		{
			ARM* arm = swinger0->p_armRight;
			arm->length = nextLength;

			swinger0 = swinger1;
			if (swinger0->p_armRight)
			{
				swinger1 = swinger0->p_armRight->p_swingerRight;
			}
			else
			{
				break;
			}
		}
	}
	break;
	case PlayerState::twoHand:

		break;
	case PlayerState::fly:
		SWINGER_BASE* swinger0 = &g_swinger[g_centerID];
		SWINGER_BASE* swinger1 = swinger0->p_armLeft->p_swingerLeft;
		while (true)
		{
	

			swinger0 = swinger1;
			if (swinger0->p_armLeft)
			{
				swinger1 = swinger0->p_armLeft->p_swingerLeft;
			}
			else
			{
				break;
			}
		}
		swinger0 = &g_swinger[g_centerID];
		swinger1 = swinger0->p_armRight->p_swingerRight;
		while (true)
		{

			swinger0 = swinger1;
			if (swinger0->p_armRight)
			{
				swinger1 = swinger0->p_armRight->p_swingerRight;
			}
			else
			{
				break;
			}
		}

		break;
	}
}
void SkillScale()
{
	//static int timeCount = 0;
	//int timeMax = 30;

	////right
	//if (IsButtonPressed(1, BUTTON_R) ||
	//	GetKeyboardPress(KEY_RIGHT_SKILL))
	//{
	//	timeCount++;
	//	if (timeCount > timeMax)
	//	{

	//	}
	//}
	//else
	//{
	//	timeCount = 0;
	//}
	static int scaleState=0;// -1:short,0:normal, 1:long
	static bool nowLonger = false;
	if (IsButtonTriggered(1, BUTTON_R) ||
		GetKeyboardTrigger(KEY_RIGHT_SKILL))
	{
		if (nowLonger)//伸びる
		{
			scaleState++;
             
			//長さを変える
			{
				switch (scaleState)
				{
				case 0:
					ScaleArm(ARM_NORMAL_LENGTH);
					break;
				case -1:
					ScaleArm(ARM_SHORT_LENGTH);
					break;
				case 1:
					ScaleArm(ARM_LONG_LENGTH);
					break;
				}
			}

			if (scaleState == 1)
			{
				nowLonger = false;
			}
		}
		else//縮む
		{
			scaleState--;

			//長さを変える
			{
				switch (scaleState)
				{
				case 0:
					ScaleArm(ARM_NORMAL_LENGTH);
					break;
				case -1:
					ScaleArm(ARM_SHORT_LENGTH);
					break;
				case 1:
					ScaleArm(ARM_LONG_LENGTH);
					break;
				}
			}

			if (scaleState == -1)
			{
				nowLonger = true;
			}
		}
	}
}


//imgui
void ImGui_ShowPlayerState()
{
	//ImGui::ShowDemoWindow();
	ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::Text("%s\n", GameStateName(g_gameState));
	ImGui::Text("%s\n", PlayerStateName( g_playerSW.state));
	ImGui::Text("left: \n%s/%s\n", g_swinger[g_leftID].canCatch ? "can catch" : "no", g_swinger[g_leftID].isCatch ? "now catch" : "no");
	ImGui::Text("right: \n%s/%s\n", g_swinger[g_rightID].canCatch ? "can catch" : "no", g_swinger[g_rightID].isCatch ? "now catch" : "no");
	ImGui::Text("center pos: %.1lf, %.1lf\n", g_swinger[g_centerID].obj.worldPos.x, g_swinger[g_centerID].obj.worldPos.y);
	ImGui::End();
	//ImGui::End();
}




HRESULT InitPlayer(void)
{
	return E_NOTIMPL;
}

//------------------------
// 外部から使う
//------------------------
SWINGER_BASE* GetSwinger(int id)
{
	return &g_swinger[id];
}
PLAYER_SW* GetSWPlayer(void)
{
	return &g_playerSW;
}
void SetCanCatch(SWINGER_BASE* swinger, BLOCK* block, bool can)
{
	if (can)
	{
		if (block)
		{
			if (!swinger->p_catchBlock)
			{
				swinger->p_catchBlock = block;
			}
		}
	}
	else
	{
		if (!block)
		{
			ReleaseBlock(swinger);
		}
	}

	swinger->canCatch = can;
}
void SetCanCatchOff(SWINGER_BASE* swinger)
{
	swinger->canCatch = false;
}
void SetSwingerCenterPos(D3DXVECTOR2 pos)
{
	g_swinger[g_centerID].obj.worldPos = pos;
}

char* PlayerStateName(int state)
{
	switch (state) {
	case 0: return "stop"; break;
	case 1: return "fly"; break;
	case 2: return "rightHand"; break;
	case 3: return "leftHand"; break;
	case 4: return "twoHand"; break;
	}
}
char* GameStateName(int state)
{
	switch (state) {
	case 0: return "waitToStart"; break;
	case 1: return "playing"; break;
	case 2: return "relife"; break;
	case 3: return "pause"; break;
	}
}



