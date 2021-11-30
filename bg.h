#pragma once

#include "main.h"
#include "renderer.h"
#include "common.h"
#include "component.h"

class BG
{
public :
	D3DXVECTOR4 boundary;
	float blockSize;
	int gameObjectNum;
	GameObject* p_gameObjects;

	BG();
	~BG();
	void CreateBGGameObject(int num);
	GameObject* GetBGGameObject(int index);
	void Update();
	void Draw();
	void Reset();
};


HRESULT InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);

BG* GetBG();
D3DXVECTOR4 GetBoundary();
