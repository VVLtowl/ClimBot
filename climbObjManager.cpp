#include "texture.h"
#include "sprite.h"

#include "camera.h"
#include "climbObjManager.h"
#include "TextReader2.h"
#include "hold.h"
#include "emitter.h"
#include "obstacle.h"
#include "bg.h"
#include "component.h"


#include <imgui.h>
//imgui
D3DXVECTOR2 flagPos;
char text[100];
void ImGui_ShowClimbObjManagerState();

//make hold start
void MakeHoldStart(Hold_Start* pHold)
{
	GameObject* pFlagGameObj;
	Display* pDisplay;
	Animation* pAnimation;
	int numX;
	int numY;
	float tw;
	float th;

	pFlagGameObj = &pHold->flagGameObject;

	//transform
	float offsetPosX = pHold->gameObject.transform.position.x + pHold->gameObject.p_displays[0].posOffset.x;
	float offsetPosY = pHold->gameObject.transform.position.y + pHold->gameObject.p_displays[0].posOffset.y - pHold->gameObject.p_displays[0].size.y / 2;
	pFlagGameObj->transform.position = { offsetPosX,offsetPosY };
	
	//display
	pFlagGameObj->CreateDisplay(1);
	pDisplay = &pFlagGameObj->p_displays[0];
	pDisplay->posOffset = { 20.0f,0 };
	pDisplay->texNo = LoadTexture(HOLD_START_FLAG_TEX_PATH);
	pDisplay->size = { HOLD_START_SIZE_WIDTH,HOLD_START_SIZE_HEIGHT };
	pDisplay->animeID = 0;

	pDisplay->CreateAnimation(1);

	numX = 8;
	numY = 2;
	tw = 1.0f / numX;
	th = 1.0f / numY;

	//animation 0
	{
		pAnimation = &pDisplay->p_animes[0];
		pAnimation->frameMax = 2;
		pAnimation->pieceMax = 8;

		pAnimation->CreatePieceUV(pAnimation->pieceMax);
		for (int i = 0; i < pAnimation->pieceMax; i++)
		{
			pAnimation->p_pieceUVs[i] = { tw * i,0,tw,th };
		}
	}

	//set first checkpoint
	SetCheckpointHold(pHold);
}
//make hold checkPoint
void MakeHoldCheckPoint(Hold_Checkpoint* pHold)
{
	GameObject* pFlagGameObj;
	Display* pDisplay;
	Animation* pAnimation;
	int numX;
	int numY;
	float tw;
	float th;

	pFlagGameObj = &pHold->flagGameObject;

	//transform
	float offsetPosX = pHold->gameObject.transform.position.x + pHold->gameObject.p_displays[0].posOffset.x;
	float offsetPosY = pHold->gameObject.transform.position.y + pHold->gameObject.p_displays[0].posOffset.y - pHold->gameObject.p_displays[0].size.y / 2;
	pFlagGameObj->transform.position = { offsetPosX,offsetPosY };

	//display
	pFlagGameObj->CreateDisplay(1);
	pDisplay = &pFlagGameObj->p_displays[0];
	pDisplay->texNo = LoadTexture(HOLD_START_FLAG_TEX_PATH);
	pDisplay->size = { HOLD_START_SIZE_WIDTH,HOLD_START_SIZE_HEIGHT };
	pDisplay->animeID = 0;

	pDisplay->CreateAnimation(3);
	numX = 8;
	numY = 2;
	tw = 1.0f / numX;
	th = 1.0f / numY;

	//animation 0:flag down
	{
		pAnimation = &pDisplay->p_animes[0];
		pAnimation->frameMax = 2;
		pAnimation->pieceMax = 1;

		pAnimation->CreatePieceUV(pAnimation->pieceMax);
		pAnimation->p_pieceUVs[0] = { 0,th,tw,th };
	}
	//animation 1:flag raise
	{
		pAnimation = &pDisplay->p_animes[1];
		pAnimation->frameMax = 2;
		pAnimation->pieceMax = 4;

		pAnimation->CreatePieceUV(pAnimation->pieceMax);
		for (int i = 0; i < pAnimation->pieceMax; i++)
		{
			pAnimation->p_pieceUVs[i] = { tw * i,th,tw,th };
		}
	}
	//animation 2:flag waving
	{
		pAnimation = &pDisplay->p_animes[2];
		pAnimation->frameMax = 2;
		pAnimation->pieceMax = 8;

		pAnimation->CreatePieceUV(pAnimation->pieceMax);
		for (int i = 0; i < pAnimation->pieceMax; i++)
		{
			pAnimation->p_pieceUVs[i] = { tw * i,0,tw,th };
		}
	}
}
//make hold goal
void MakeHoldGoal(Hold_Goal* pHold)
{
	GameObject* pFlagGameObj;
	Display* pDisplay;
	Animation* pAnimation;
	int numX;
	int numY;
	float tw;
	float th;

	pFlagGameObj = &pHold->flagGameObject;

	//transform
	float offsetPosX = pHold->gameObject.transform.position.x + pHold->gameObject.p_displays[0].posOffset.x;
	float offsetPosY = pHold->gameObject.transform.position.y + pHold->gameObject.p_displays[0].posOffset.y - pHold->gameObject.p_displays[0].size.y / 2;
	pFlagGameObj->transform.position = { offsetPosX,offsetPosY };

	//display
	pFlagGameObj->CreateDisplay(1);
	pDisplay = &pFlagGameObj->p_displays[0];
	pDisplay->texNo = LoadTexture(HOLD_START_FLAG_TEX_PATH);
	pDisplay->size = { HOLD_START_SIZE_WIDTH,HOLD_START_SIZE_HEIGHT };
	pDisplay->animeID = 0;

	pDisplay->CreateAnimation(3);
	numX = 8;
	numY = 2;
	tw = 1.0f / numX;
	th = 1.0f / numY;

	//animation 0:flag down
	{
		pAnimation = &pDisplay->p_animes[0];
		pAnimation->frameMax = 2;
		pAnimation->pieceMax = 1;

		pAnimation->CreatePieceUV(pAnimation->pieceMax);
		pAnimation->p_pieceUVs[0] = { 0,th,tw,th };
	}
	//animation 1:flag raise
	{
		pAnimation = &pDisplay->p_animes[1];
		pAnimation->frameMax = 2;
		pAnimation->pieceMax = 4;

		pAnimation->CreatePieceUV(pAnimation->pieceMax);
		for (int i = 0; i < pAnimation->pieceMax; i++)
		{
			pAnimation->p_pieceUVs[i] = { tw * i,th,tw,th };
		}
	}
	//animation 2:flag waving
	{
		pAnimation = &pDisplay->p_animes[2];
		pAnimation->frameMax = 2;
		pAnimation->pieceMax = 8;

		pAnimation->CreatePieceUV(pAnimation->pieceMax);
		for (int i = 0; i < pAnimation->pieceMax; i++)
		{
			pAnimation->p_pieceUVs[i] = { tw * i,0,tw,th };
		}
	}
}


void ChangeReaderDataToClimbObjData()
{
	ReaderData* pReaderdata=GetReaderData();
	//map
	{
		MAP* pMap = &pReaderdata->g_map;
		BG* pBG = GetBG();
		pBG->blockSize = pMap->blockSize;
		pBG->boundary = { (float)-pMap->sizeX / 2.0f,(float)pMap->sizeX / 2.0f,-(float)pMap->sizeY,0 };
		SetBoundary(pBG->boundary);

		pBG->CreateBGGameObject(1);
		GameObject* pBGGameObj = pBG->GetBGGameObject(0);
		flagPos=pBGGameObj->transform.position = { 0,-(float)pMap->sizeY / 2.0f };


		pBGGameObj->CreateDisplay(1);
		Display* pDisplay = &pBGGameObj->p_displays[0];
		char pathName[100] = "";
		sprintf(pathName, "data/TEXTURE/%s.png", pMap->textureName);
		strcpy(text, pathName);
		pDisplay->texNo = LoadTexture(pathName);
		pDisplay->animeID = 0;
		pDisplay->size = { (float)pMap->sizeX,(float)pMap->sizeY };

		pDisplay->CreateAnimation(1);
		Animation* pAnimation = &pDisplay->p_animes[0];
		pAnimation->CreatePieceUV(1);
		pAnimation->frameCount = 0;
		pAnimation->frameMax = 1;
		pAnimation->pieceID = 0;
		pAnimation->pieceMax = 1;
		pAnimation->p_pieceUVs[0] = { 0,0,1,1 };
	}
	//col_rect
	for (int i = 0; i < pReaderdata->g_rectNum; i++)
	{
		COL_RECT* pCol = &pReaderdata->g_rect[i];
		switch (pCol->type)
		{
		case 0://hold normal
		{
			Hold_Normal* pHold = new Hold_Normal();
			pHold->holdType = HoldType::normal;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			pHold->gameObject.pp_colliders[0] = new Collider_Rect({ pCol->sizeX,pCol->sizeY });

			AddHold(pHold);
		}
		break;
		case 1://hold start
		{
			Hold_Start* pHold = new Hold_Start();
			pHold->holdType = HoldType::start;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			pHold->gameObject.pp_colliders[0] = new Collider_Rect({ pCol->sizeX,pCol->sizeY });

			MakeHoldStart(pHold);

			AddHold(pHold);
		}
		break;
		case 2://hold checkpoint
		{
			Hold_Checkpoint* pHold = new Hold_Checkpoint();
			pHold->holdType = HoldType::checkPoint;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			pHold->gameObject.pp_colliders[0] = new Collider_Rect({ pCol->sizeX,pCol->sizeY });

			MakeHoldCheckPoint(pHold);

			AddHold(pHold);
		}
		break;
		case 3://hold goal
		{
			Hold_Goal* pHold = new Hold_Goal();
			pHold->holdType = HoldType::goal;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			pHold->gameObject.pp_colliders[0] = new Collider_Rect({ pCol->sizeX,pCol->sizeY });

			MakeHoldGoal(pHold);

			AddHold(pHold);
		}
		break;
		case 4://toge
		{

		}
		break;
		case 5://star
		{

		}
		break;
		}
	}
	//col_circle
	for (int i = 0; i < pReaderdata->g_circleNum; i++)
	{
		COL_CIRCLE* pCol = &pReaderdata->g_circle[i];
		switch (pCol->type)
		{
		case 0://hold normal
		{
			Hold_Normal* pHold = new Hold_Normal();
			pHold->holdType = HoldType::normal;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			pHold->gameObject.pp_colliders[0] = new Collider_Circle(pCol->colRadius);

			AddHold(pHold);
		}
		break;
		case 1://hold start
		{
			Hold_Start* pHold = new Hold_Start();
			pHold->holdType = HoldType::start;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			pHold->gameObject.pp_colliders[0] = new Collider_Circle(pCol->colRadius);

			MakeHoldStart(pHold);

			AddHold(pHold);
		}
		break;
		case 2://hold checkpoint
		{
			Hold_Checkpoint* pHold = new Hold_Checkpoint();
			pHold->holdType = HoldType::checkPoint;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			pHold->gameObject.pp_colliders[0] = new Collider_Circle(pCol->colRadius);

			MakeHoldCheckPoint(pHold);

			AddHold(pHold);
		}
		break;
		case 3://hold goal
		{
			Hold_Goal* pHold = new Hold_Goal();
			pHold->holdType = HoldType::goal;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			pHold->gameObject.pp_colliders[0] = new Collider_Circle(pCol->colRadius);

			MakeHoldGoal(pHold);

			AddHold(pHold);
		}
		break;

		//edit by ƒtƒWƒ^
		case 4://collapse
		{
			Hold_Collapse* pHold = new Hold_Collapse();
			pHold->holdType = HoldType::collapse;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			pHold->gameObject.pp_colliders[0] = new Collider_Circle(pCol->colRadius);

			pDisplay->CreateAnimation(3);
			int numX = 4;
			int numY = 2;
			float tw = 1.0f / numX;
			float th = 1.0f / numY;

			//animation 0:normal
			{
				pAnimation = &pDisplay->p_animes[0];
				pAnimation->frameMax = 2;
				pAnimation->pieceMax = 1;

				pAnimation->CreatePieceUV(pAnimation->pieceMax);
				pAnimation->p_pieceUVs[0] = { 0,th,tw,th };
			}
			//animation 1:collapse
			{
				pAnimation = &pDisplay->p_animes[1];
				pAnimation->frameMax = 2;
				pAnimation->pieceMax = 1;

				pAnimation->CreatePieceUV(pAnimation->pieceMax);
				
				pAnimation->p_pieceUVs[0] = { tw,th,tw,th };
				
			}
			//animation 2:is collapsing
			{
				pAnimation = &pDisplay->p_animes[2];
				pAnimation->frameMax = 4;
				pAnimation->pieceMax = 4;

				pAnimation->CreatePieceUV(pAnimation->pieceMax);
				for (int i = 0; i < pAnimation->pieceMax; i++)
				{
					pAnimation->p_pieceUVs[i] = { tw * i,0,tw,th };
				}
			}

			AddHold(pHold);
		}
		break;
		case 5://star
		{

		}
		break;
		case 6://toge
		{

		}
		break;
		}
	}
	//col_capsule
	for (int i = 0; i < pReaderdata->g_capsuleNum; i++)
	{
		COL_CAPSULE* pCol = &pReaderdata->g_capsule[i];
		switch (pCol->type)
		{
		case 0://hold normal
		{
			Hold_Normal* pHold = new Hold_Normal();
			pHold->holdType = HoldType::normal;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			//todo
			pHold->gameObject.pp_colliders[0] = new Collider_Capsule({ pCol->rectVectorX,pCol->rectVectorY }, pCol->rectRadius);

			AddHold(pHold);
		}
		break;
		case 1://hold start
		{
			Hold_Start* pHold = new Hold_Start();
			pHold->holdType = HoldType::start;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			//todo
			pHold->gameObject.pp_colliders[0] = new Collider_Capsule({ pCol->rectVectorX,pCol->rectVectorY }, pCol->rectRadius);

			MakeHoldStart(pHold);

			AddHold(pHold);
		}
		break;
		case 2://hold checkpoint
		{
			Hold_Checkpoint* pHold = new Hold_Checkpoint();
			pHold->holdType = HoldType::checkPoint;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			//todo
			pHold->gameObject.pp_colliders[0] = new Collider_Capsule({ pCol->rectVectorX,pCol->rectVectorY }, pCol->rectRadius);

			MakeHoldCheckPoint(pHold);

			AddHold(pHold);
		}
		break;
		case 3://hold goal
		{
			Hold_Goal* pHold = new Hold_Goal();
			pHold->holdType = HoldType::goal;

			//transform
			pHold->gameObject.transform.position = { pCol->posX , pCol->posY };

			//display
			pHold->gameObject.CreateDisplay(1);
			Display* pDisplay = &pHold->gameObject.p_displays[0];
			char pathName[100] = "";
			sprintf(pathName, "data/TEXTURE/%s.png", pCol->fileName);
			pDisplay->texNo = LoadTexture(pathName);
			pDisplay->size = { pCol->sizeX,pCol->sizeY };
			pDisplay->animeID = 0;

			pDisplay->CreateAnimation(1);
			Animation* pAnimation = &pDisplay->p_animes[0];
			pAnimation->frameMax = 2;
			pAnimation->pieceMax = 1;

			pAnimation->CreatePieceUV(1);
			pAnimation->p_pieceUVs[0] = { 0,0,1,1 };

			//collider
			pHold->gameObject.CreateCollider(1);
			//todo
			pHold->gameObject.pp_colliders[0] = new Collider_Capsule({ pCol->rectVectorX,pCol->rectVectorY }, pCol->rectRadius);

			MakeHoldGoal(pHold);

			AddHold(pHold);
		}
		break;
		case 4://toge
		{

		}
		break;
		case 5://star
		{

		}
		break;
		}
	}
}

void UpdateClimbObjManager()
{
	ImGui_ShowClimbObjManagerState();
}
void ImGui_ShowClimbObjManagerState()
{
	ImGui::Begin("ClimbObj", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::Text("%.2lf,%.2lf\n", GetBG()->p_gameObjects[0].p_displays[0].size.x, GetBG()->p_gameObjects[0].p_displays[0].size.y);
	ImGui::Text("%.2lf,%.2lf\n", GetBG()->p_gameObjects[0].p_displays[0].size.x, GetBG()->p_gameObjects[0].p_displays[0].size.y);
	ImGui::End();
}
