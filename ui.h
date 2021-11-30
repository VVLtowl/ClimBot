#pragma once
#include "common.h"

struct UI_IMAGE
{
	GAME_OBJ obj;
	int texNo;
};



void InitUI();
void UninitUI();
void UpdateUI();
void DrawUI();