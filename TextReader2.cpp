#define _CRT_SECURE_NO_WARNINGS

#include "TextReader2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define TEXT_YOUSO_MAX 20


using namespace std;


ReaderData g_data;

void ReadStageText(const char* TextName) {
	//vector<string> lines;
	char str[256];

	//reset
	g_data.g_circleNum = 0;
	g_data.g_rectNum = 0;
	g_data.g_capsuleNum = 0;
	g_data.g_emitterFallNum = 0;
	g_data.g_emitterBirdNum = 0;

	for (int i = 0; i < 50; i++)
	{
		g_data.g_circle[i].use =
			g_data.g_rect[i].use =
			g_data.g_capsule[i].use = 
			g_data.g_emitterFall[i].use=
			g_data.g_emitterBird[i].use = false;
	}


	FILE* inputFile=fopen(TextName,"rt");
	

	while (true) 
	{
		fscanf(inputFile, "%s", str);

		if (feof(inputFile) != 0) break;

		if (strcmp(str, "map") == 0) {
			fscanf(inputFile, "%f", &g_data.g_map.sizeX);
			fscanf(inputFile, "%f", &g_data.g_map.sizeY);
			fscanf(inputFile, "%s", g_data.g_map.textureName);
			fscanf(inputFile, "%f", &g_data.g_map.blockSize);
		}
		else if (strcmp(str, "col_rect") == 0) {
			/*g_rect[g_rectNum].name = { "col_rect" };*/
			//g_data.g_rect[g_data.g_rectNum].name = str;
			fscanf(inputFile, "%f", &g_data.g_rect[g_data.g_rectNum].posX);
			fscanf(inputFile, "%f", &g_data.g_rect[g_data.g_rectNum].posY);
			fscanf(inputFile, "%s",  g_data.g_rect[g_data.g_rectNum].fileName);
			fscanf(inputFile, "%f", &g_data.g_rect[g_data.g_rectNum].sizeX);
			fscanf(inputFile, "%f", &g_data.g_rect[g_data.g_rectNum].sizeY);
			fscanf(inputFile, "%d", &g_data.g_rect[g_data.g_rectNum].type);

			g_data.g_rectNum++;
		}
		else if (strcmp(str, "col_circle") == 0) {
			/*g_circle[g_circleNum].name = { "col_circle" };*/
			//g_data.g_circle[g_data.g_circleNum].name = str;
			fscanf(inputFile, "%f", &g_data.g_circle[g_data.g_circleNum].posX);
			fscanf(inputFile, "%f", &g_data.g_circle[g_data.g_circleNum].posY);
			fscanf(inputFile, "%s",  g_data.g_circle[g_data.g_circleNum].fileName);
			fscanf(inputFile, "%f", &g_data.g_circle[g_data.g_circleNum].sizeX);
			fscanf(inputFile, "%f", &g_data.g_circle[g_data.g_circleNum].sizeY);
			fscanf(inputFile, "%d", &g_data.g_circle[g_data.g_circleNum].type);
			fscanf(inputFile, "%f", &g_data.g_circle[g_data.g_circleNum].colRadius);

			g_data.g_circleNum++;
		}
		else if (strcmp(str, "col_capsule") == 0) {
			//g_data.g_capsule[g_data.g_capsuleNum].name = str;
			fscanf(inputFile, "%f", &g_data.g_capsule[g_data.g_capsuleNum].posX);
			fscanf(inputFile, "%f", &g_data.g_capsule[g_data.g_capsuleNum].posY);
			fscanf(inputFile, "%s",  g_data.g_capsule[g_data.g_capsuleNum].fileName);
			fscanf(inputFile, "%f", &g_data.g_capsule[g_data.g_capsuleNum].sizeX);
			fscanf(inputFile, "%f", &g_data.g_capsule[g_data.g_capsuleNum].sizeY);
			fscanf(inputFile, "%d", &g_data.g_capsule[g_data.g_capsuleNum].type);
			fscanf(inputFile, "%f", &g_data.g_capsule[g_data.g_capsuleNum].centerPosX);
			fscanf(inputFile, "%f", &g_data.g_capsule[g_data.g_capsuleNum].centerPosY);
			fscanf(inputFile, "%f", &g_data.g_capsule[g_data.g_capsuleNum].rectVectorX);
			fscanf(inputFile, "%f", &g_data.g_capsule[g_data.g_capsuleNum].rectVectorY);
			fscanf(inputFile, "%f", &g_data.g_capsule[g_data.g_capsuleNum].rectRadius);

			g_data.g_circleNum++;
		}
		else if (strcmp(str, "emitter_fall") == 0) {
			//g_data.g_emitterFall[g_data.g_emitterFallNum].name = str;
			fscanf(inputFile, "%f", &g_data.g_emitterFall[g_data.g_emitterFallNum].startPosX);
			fscanf(inputFile, "%f", &g_data.g_emitterFall[g_data.g_emitterFallNum].startPosY);
			fscanf(inputFile, "%f", &g_data.g_emitterFall[g_data.g_emitterFallNum].endPosY);
			fscanf(inputFile, "%d", &g_data.g_emitterFall[g_data.g_emitterFallNum].fallType);

			g_data.g_emitterFallNum++;
		}
		else if (strcmp(str, "emitter_bird") == 0) {
			//g_data.g_emitterBird[g_data.g_emitterBirdNum].name = str;
			fscanf(inputFile, "%f", &g_data.g_emitterBird[g_data.g_emitterBirdNum].homePosX);
			fscanf(inputFile, "%f", &g_data.g_emitterBird[g_data.g_emitterBirdNum].homePosY);

			g_data.g_emitterBirdNum++;
		}
	}
	fclose(inputFile);
}

//データデバッグ用
void printTextData() {
	//cout << "map:" << g_map.sizeX << " " << g_map.sizeY << " " << g_map.textureName << endl;
	//for (int i = 0; i < g_circleNum; i++) {
	//	cout << g_circle[i].name<< " " << g_circle[i].posX << " " << g_circle[i].posY << " " << g_circle[i].fileName << " " << g_circle[i].sizeX << " " << g_circle[i].sizeY << " " << g_circle[i].type << " " << g_circle[i].colRadius << endl;
	//}
	//for (int i = 0; i < g_rectNum; i++) {
	//	cout << g_rect[i].name << " " << g_rect[i].posX << " " << g_rect[i].posY << " " << g_rect[i].fileName << " " << g_rect[i].sizeX << " " << g_rect[i].sizeY << " " << g_rect[i].type << endl;
	//}
	//for (int i = 0; i < g_capsuleNum; i++) {
	//	cout << g_capsule[i].name << " " << g_capsule[i].posX << " " << g_capsule[i].posY << " " << g_capsule[i].fileName << " " << g_capsule[i].sizeX << " " << g_capsule[i].sizeY << " " << g_capsule[i].type << endl;
	//}
	//for (int i = 0; i < g_emitterFallNum; i++) {
	//	cout << g_emitterFall[i].name << " " << g_emitterFall[i].startPosX << " " << g_emitterFall[i].startPosY << " " << g_emitterFall[i].endPosY << " " << g_emitterFall[i].fallType << endl;
	//}
	//for (int i = 0; i < g_emitterBirdNum; i++) {
	//	cout << g_emitterBird[i].name << " " << g_emitterBird[i].homePosX << " " << g_emitterBird[i].homePosY << endl;
	//}
}

ReaderData* GetReaderData()
{
	return &g_data;
}
