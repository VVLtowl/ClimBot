//=============================================================================
//
// プレイヤー処理 [sprite.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitSprite();
void UninitSprite();

//give up使わないで
void DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawSpriteColor(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color);

void DrawSpriteColorRotate(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR Color, float Rot);
void DrawSpriteColorRotateLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR Color, float Rot);
void DrawSpriteColorRotateNoCmr(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR Color, float Rot);
void DrawSpriteColorRotateLeftTopNoCmr(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR Color, float Rot);
