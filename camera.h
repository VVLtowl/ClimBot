#pragma once
#include "main.h"
#include "common.h"
#include "component.h"
#include <vector>

using std::vector;

struct CAMERA
{
	 vector<GAME_OBJ*> objList;
	 Transform* pLookAtTransform = nullptr;

	 D3DXVECTOR4 boundary = { 0,0,0,0 };
	 float lookAtLerp = 0;
	 D3DXVECTOR2 cmrPos;
	 D3DXVECTOR2 deltaPos;

	 bool canShowCol = false;
	 int colTexNo;
};

void SetCmrLookAt(Transform* pLookAtTrs);
void RegisterObjToCmr(GAME_OBJ* p_gameObj);
void InitCamera();
void UpdateCamera();
void SetBoundary(D3DXVECTOR4 boundary);
D3DXVECTOR2 GetCmrDeltaPos();
D3DXVECTOR3 GetCmrDeltaPosV3();
int GetColTexNo();
bool CanShowCol();
