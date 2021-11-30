#pragma once
#include "common.h"
#include "component.h"
#include "hold.h"

#define ARM_LENGTH_NORMAL (80.0f)

class Arm;
class Ball;
class Player;
enum PlayerState
{
	stop = 0,
	fly,
	rightHand,
	leftHand,
	twoHand,
};
enum PullType
{
	same,
	left,
	right,
};
enum BallPos
{
	bodyLeft,
	bodySelf,
	bodyRight,
};


class Arm
{
public:
	float length = ARM_LENGTH_NORMAL;
	Display display;
	Ball* pLeftBall = nullptr;
	Ball* pRightBall = nullptr;

	~Arm();
	void SetTwoBall(Ball* pLeft, Ball* pRight)
	{
		pLeftBall = pLeft;
		pRightBall = pRight;
	}
	void Update();
	void Draw();
};
class Ball
{
public:
	Transform transform;
	int displayNum;
	Display* p_displays;
	Collider* collider = nullptr;
	GameObject gameObject;//back up
	Arm* pLeftArm = nullptr;
	Arm* pRightArm = nullptr;
	BallPos ballPos = BallPos::bodySelf;
	float displayRotation = 0;
	float rotateSpeed = 0;
	bool isCatch = false;
	Hold* pCatchHold = nullptr;

	~Ball()
	{
		delete collider;
	}
	Ball* GetFatherBall();
	Arm* GetFatherArm();
	Ball* GetSonBall();
	Arm* GetSonArm();
	void SetTwoArm(Arm* pLeft, Arm* pRight)
	{
		pLeftArm = pLeft;
		pRightArm = pRight;
	}
	void Update();
	void Draw();
	void Rotate();//back up
	float GetRotate();
	void CreateDisplay(int num);
	void UpdateRotateSpeed();
	void RotateSon();
	void RotateTwoSon();
	void RotateDisplay();
	void Pull(PullType type);
};

class Player
{
public:
	int ballNum;
	int armNum;
	Ball* p_balls;// = nullptr;
	Arm* p_arms; //= nullptr;

	int state=PlayerState::stop;

	Ball* pBodyBall = nullptr;
	Ball* pLeftBall = nullptr;
	Ball* pRightBall = nullptr;

	Ball* pHoldBall = nullptr;

	D3DXVECTOR2 moveSpeed = { 0,0 };

	void CreateBall(int num);
	void CreateArm(int num);
	void Reset();
	void Update();
	void Draw();
	void Pull(PullType type);
	void ChangeState(PlayerState state);
};




//---------------------------------------

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

Player* GetPlayer();
char* PlayerStateName();
void Test_ResetPlayer();
//void ReleaseCatchHold();