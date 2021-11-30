#pragma once

enum GameState
{
	startStage,
	waitFirstCatch,
	playing,
	relife,
	complete,
	die,
};

void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void ChangeGameState(GameState state);
int GetGameState();
const char* GameStateName();