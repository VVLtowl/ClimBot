#include "texture.h"
#include "sprite.h"
#include "ui.h"

UI_IMAGE g_imgKeyboardCtrlInfo;

void InitUI()
{
	g_imgKeyboardCtrlInfo.texNo = LoadTexture("data/TEXTURE/keyboardHelp_250x78.png");
	g_imgKeyboardCtrlInfo.obj.size = { 250,78 };
	g_imgKeyboardCtrlInfo.obj.drawPos = { 250 / 2, 78 / 2 };
}

void UninitUI()
{
}

void UpdateUI()
{
}

void DrawUI()
{
	int texNo = g_imgKeyboardCtrlInfo.texNo;
	float x = g_imgKeyboardCtrlInfo.obj.drawPos.x;
	float y = g_imgKeyboardCtrlInfo.obj.drawPos.y;
	float w = g_imgKeyboardCtrlInfo.obj.size.x;
	float h = g_imgKeyboardCtrlInfo.obj.size.y;
	float tx = 0;
	float ty = 0;
	float tw = 1;
	float th = 1;
	D3DXCOLOR color = { 1,1,1,1 };
	DrawSpriteColorRotateNoCmr(texNo,
		x,y,w,h,
		tx,ty,tw,th,
		color,
		0);
}
