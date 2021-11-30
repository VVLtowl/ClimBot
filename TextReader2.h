#pragma once


struct COL_RECT {
	bool use;
	//char name[100];
	float posX;
	float posY;
	char fileName[50];
	float sizeX;
	float sizeY;
	int type;
	float rectSizeX;
	float rectSizeY;
};
struct COL_CIRCLE {
	bool use;
	//string name;
	float posX;
	float posY;
	char fileName[50];
	float sizeX;
	float sizeY;
	int type;
	float colRadius;
};
struct COL_CAPSULE {
	bool use;
	//string name;
	float posX;
	float posY;
	char fileName[50];
	float sizeX;
	float sizeY;
	int type;
	float centerPosX;
	float centerPosY;
	float rectVectorX;
	float rectVectorY;
	float rectRadius;
};
struct EMITTER_FALL {
	bool use;
	//string name;
	float startPosX;
	float startPosY;
	float endPosY;
	int fallType;
};
struct EMITTER_BIRD {
	bool use;
	//string name;
	float homePosX;
	float homePosY;
};

struct MAP {
	float sizeX;
	float sizeY;
	char textureName[50];
	float blockSize;
};

struct ReaderData
{
	MAP g_map;
	COL_CIRCLE g_circle[50];
	COL_RECT g_rect[50];
	COL_CAPSULE g_capsule[50];
	EMITTER_FALL g_emitterFall[50];
	EMITTER_BIRD g_emitterBird[50];

	int g_circleNum = 0;
	int g_rectNum = 0;
	int g_capsuleNum = 0;
	int g_emitterFallNum = 0;
	int g_emitterBirdNum = 0;
};

void ReadStageText(const char* TextName);
void printTextData();
ReaderData* GetReaderData();
