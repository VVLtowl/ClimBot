//=============================================================================
//
// 入力処理 [input.h]
// Author : 
//
//=============================================================================
#pragma once

#include <XInput.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//ボタン一覧

// XINPUT_GAMEPAD_DPAD_UP			十字キー上
// XINPUT_GAMEPAD_DPAD_DOWN			十字キー下
// XINPUT_GAMEPAD_DPAD_LEFT			十字キー左
// XINPUT_GAMEPAD_DPAD_RIGHT		十字キー右
// XINPUT_GAMEPAD_START
// XINPUT_GAMEPAD_BACK
// XINPUT_GAMEPAD_LEFT_THUMB		Lスティック押し込み
// XINPUT_GAMEPAD_RIGHT_THUMB		Rスティック押し込み
// XINPUT_GAMEPAD_LEFT_SHOULDER		Lボタン
// XINPUT_GAMEPAD_RIGHT_SHOULDER	Rボタン
// XINPUT_GAMEPAD_A
// XINPUT_GAMEPAD_B
// XINPUT_GAMEPAD_X
// XINPUT_GAMEPAD_Y

//スティックの範囲
// X軸 左-32768　右 32767
// Y軸 上 32767　下-32768

//トリガーの範囲
// 0 〜 255

// バイブレーションの範囲
// 0 〜 255

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitXInput(HINSTANCE hInst, HWND hWnd);
void UninitXInput(void);
void UpdateXInput(void);

int GetThumbLeftX(int padNo);
int GetThumbLeftY(int padNo);
int GetThumbRightX(int padNo);
int GetThumbRightY(int padNo);

void SetLeftVibration(int padNo, int speed);
void SetRightVibration(int padNo, int speed);
void SetVibration(int padNo, int speed);
void StopVibration(int padNo);

int XGetLeftTrigger(int padNo);
int XGetRightTrigger(int padNo);

BOOL XIsButtonPressed(int padNo,DWORD button);
BOOL XIsButtonTriggered(int padNo,DWORD button);

