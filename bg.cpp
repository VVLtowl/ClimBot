//=============================================================================
//
// îwåièàóù [bg.cpp]
// Author : 
//
//=============================================================================

#include "texture.h"
#include "sprite.h"
#include "camera.h"

#include "bg.h"

BG g_bg;



HRESULT InitBG(void)
{
	return S_OK;
}

void UninitBG(void)
{

}

void UpdateBG(void)
{

}

void DrawBG(void)
{
	g_bg.Draw();
}

BG *GetBG()
{
	return &g_bg;
}

D3DXVECTOR4 GetBoundary()
{
	return g_bg.boundary;
}
//-------------------------------------------------------------------
BG::BG()
{
	p_gameObjects = nullptr;
	gameObjectNum = 0;
}

BG::~BG()
{
	//delete[] p_gameObjects;
}

void BG::CreateBGGameObject(int num)
{
	gameObjectNum = num;
	p_gameObjects = new GameObject[num];
}

GameObject* BG::GetBGGameObject(int index)
{
	return &p_gameObjects[index];
}

void BG::Update()
{

}

void BG::Draw()
{
	for (int i = 0; i < g_bg.gameObjectNum; i++)
	{
		g_bg.p_gameObjects[i].Draw();
	}
}

void BG::Reset()
{
	if(g_bg.p_gameObjects)delete[] g_bg.p_gameObjects;
	g_bg.p_gameObjects = nullptr;
	gameObjectNum = 0;
	boundary = { 0,0,0,0 };
}
