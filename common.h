#pragma once
#define PI 3.1415926f
#define RADIANT(A) (A*PI/180.0f)

//struct OBJ
//{
//	D3DXVECTOR2 pos;
//	D3DXVECTOR2 scale;
//	D3DXVECTOR2 rotateAngle;
//};

class GAME_OBJ
{
public :
	D3DXVECTOR2 drawPos;
	D3DXVECTOR2 worldPos;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 size;
	float rotateAngle;
	D3DXCOLOR color;

	//son
	float sonRadius;
	float sonRotateAngle;
	int texNo;
};


void MyLog(const char* strOutputString, ...);