#pragma once

#include "component.h"
#include "Textreader2.h"
#include <vector>

using std::vector;

//edit by フジタ
enum HoldType
{
	normal,
	start,
	checkPoint,
	goal,
	collapse,
};

class Hold
{
public:
	GameObject gameObject;
	int holdType;


	virtual void Update() = 0;
	virtual void Draw() = 0;

	//collapse
	virtual AddCount() {};
};

class Hold_Normal :public Hold
{
public:
	void Update()override
	{
		gameObject.Update();
	}
	void Draw()override {
		gameObject.Draw();
	}
};
#define HOLD_START_FLAG_TEX_PATH "data/TEXTURE/checkpoint_animation.png"
#define HOLD_START_SIZE_WIDTH (80.0f)
#define HOLD_START_SIZE_HEIGHT (HOLD_START_SIZE_WIDTH)
class Hold_Start :public Hold
{
public:
	GameObject flagGameObject;
	
	void Update()override {
		gameObject.Update();
		flagGameObject.Update();
	}
	void Draw()override {
		gameObject.Draw();
		flagGameObject.Draw();
	}
};

#define HOLD_CHECKPOINT_FLAG_TEX_PATH "data/TEXTURE/checkpoint_animation.png"
#define HOLD_CHECKPOINT_SIZE_WIDTH (80.0f)
#define HOLD_CHECKPOINT_SIZE_HEIGHT (HOLD_CHECKPOINT_SIZE_WIDTH)
class Hold_Checkpoint :public Hold
{
public:
	GameObject flagGameObject;
	
	void Update()override {
		gameObject.Update();
		flagGameObject.Update();
	}
	void Draw()override {
		gameObject.Draw();
		flagGameObject.Draw();
	}
};

#define HOLD_GOAL_FLAG_TEX_PATH "data/TEXTURE/checkpoint_animation.png"
#define HOLD_GOAL_SIZE_WIDTH (80.0f)
#define HOLD_GOAL_SIZE_HEIGHT (HOLD_CHECKPOINT_SIZE_WIDTH)
class Hold_Goal :public Hold
{
public:
	GameObject flagGameObject;

	void Update()override
	{
		gameObject.Update();
		flagGameObject.Update();
	}
	void Draw()override {
		gameObject.Draw();
		flagGameObject.Draw();
	}
};

//edit by フジタ
enum CollapseState
{
	collapse_use,
	collapse_warning,
	collapse_break,
	collapse_wait,
};
class Hold_Collapse:public Hold
{
public:
	int count = 0;

	bool isCollapsing = false;
	bool isUse = true;
	int state=collapse_use;

	void Update()override;

	void Draw()override {
		if (isUse)gameObject.Draw();
	}
};

//class HoldManager
//{
//public:
//	std::vector<Hold> list_hold;
//};

void InitHold();
void UninitHold();
void UpdateHold();
void DrawHold();

void AddHold(Hold* pHold);
void SetCheckpointHold(Hold* pHold);
Hold *GetCheckpointHold();
vector<Hold*> GetHold();