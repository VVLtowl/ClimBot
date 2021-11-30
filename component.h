#pragma once
#include "main.h"
#include <vector>

using std::vector;

class Collider;
class Display;
class Transform;
class Animation;

//move position
class Transform
{
public :
	D3DXVECTOR2 position;
	float rotation;
	D3DXVECTOR2 scale;
	
	Transform();
};

//collision
enum ColliderType
{
	rect,
	circle,
	capsule,
};
class Collider
{
public:
	D3DXVECTOR2 posOffset;
	int type;
	Collider();
	Collider(ColliderType _type);

	//rect data
	virtual D3DXVECTOR2 RectGetRectSize() { return { 0,0 }; }
	//circle data
	virtual float CircleGetRadiusRadius() { return 0; }
	//capsule data
	virtual D3DXVECTOR2 CapsuleGetRectVector() { return { 0,0 }; }
	virtual float CapsuleGetRectRadius() { return 0; }
};
class Collider_Rect :public Collider
{
public :
	D3DXVECTOR2 size;
	
	Collider_Rect();
	Collider_Rect(D3DXVECTOR2 _size) :
		Collider(ColliderType::rect),
		size(_size)
	{};
	D3DXVECTOR2 RectGetRectSize()override { return size; }
};
class Collider_Circle :public Collider
{
public:
	float radius;

	Collider_Circle();
	Collider_Circle(float _radius) :
		Collider(ColliderType::circle),
		radius(_radius)
	{};
	float CircleGetRadiusRadius() override { return radius; }
};
class Collider_Capsule :public Collider
{
public:
	D3DXVECTOR2 rectVector;
	float rectRadius;

	Collider_Capsule();
	Collider_Capsule(D3DXVECTOR2 _rectVector, float _rectRadius) :
		Collider(ColliderType::capsule),
		rectVector(_rectVector),
		rectRadius(_rectRadius)
	{};
	D3DXVECTOR2 CapsuleGetRectVector() override { return rectVector; }
	float CapsuleGetRectRadius() override { return rectRadius; }
};

//display
class Display
{
public:
	D3DXVECTOR2 posOffset;
	int texNo;
	D3DXVECTOR2 size;
	int animeID;
	Animation* p_animes;
	D3DXCOLOR color;

	Display();
	~Display();
	void CreateAnimation(int animeNum);
	void SetAnimation(int index, int _frameMax, int _pieceMax);
};

//animation
class Animation
{
public:
	int frameCount;
	int frameMax;
	int pieceID;
	int pieceMax;
	D3DXVECTOR4* p_pieceUVs;

	Animation();
	~Animation();
	void CreatePieceUV(int pieceNum);
	void SetPieceUV(int index,D3DXVECTOR4 uv);
};



//game obj
class GameObject
{
public :
	Transform transform;
	int displayNum;
	Display *p_displays;
	int colliderNum;
	Collider **pp_colliders;

	GameObject();
	~GameObject();
	void CreateDisplay(int displayNum);
	void CreateCollider(int colliderNum);
	void Update();
	void Draw();
};
