#include "texture.h"
#include "component.h"
#include "camera.h"
static CAMERA g_camera;

D3DXVECTOR2 lookatPos;
void SetCmrLookAt(Transform* pLookAtTrs)
{
	g_camera.pLookAtTransform = pLookAtTrs;
	lookatPos = g_camera.pLookAtTransform->position;
}

void RegisterObjToCmr(GAME_OBJ* p_gameObj)
{
	g_camera.objList.push_back(p_gameObj);
}

void InitCamera()
{
	g_camera.objList.clear();
	g_camera.lookAtLerp = 10;
	g_camera.cmrPos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	g_camera.canShowCol = true;
	g_camera.colTexNo = LoadTexture("data/TEXTURE/fade_white.png");
}
void UpdateCamera()
{
	int num = g_camera.objList.size();
	float lerp = g_camera.lookAtLerp;
	D3DXVECTOR2 pos = g_camera.cmrPos;
	D3DXVECTOR4 boundary = g_camera.boundary;
	if (g_camera.pLookAtTransform)	pos += (g_camera.pLookAtTransform->position - pos) / lerp;
	else pos += (D3DXVECTOR2(40.0f, -400) - pos) / lerp;

	pos.x = min(boundary.y - +SCREEN_WIDTH / 2, max(boundary.x + SCREEN_WIDTH / 2, pos.x));
	pos.y = min(boundary.w - +SCREEN_HEIGHT / 2, max(boundary.z + SCREEN_HEIGHT / 2, pos.y));
	g_camera.cmrPos = pos;
	g_camera.deltaPos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2) - g_camera.cmrPos;
	
	//for (int i = 0; i < num; i++)
	//{
	//	g_camera.objList[i]->drawPos += deltaPos;
	//}
}

D3DXVECTOR2 GetCmrDeltaPos()
{
	return g_camera.deltaPos;
}

D3DXVECTOR3 GetCmrDeltaPosV3()
{
	return D3DXVECTOR3(g_camera.deltaPos.x, g_camera.deltaPos.y, 0);
}

int GetColTexNo()
{
	return g_camera.colTexNo;
}

bool CanShowCol()
{
	return g_camera.canShowCol;
}

void SetBoundary(D3DXVECTOR4 boundary)
{
	g_camera.boundary = boundary;
}
