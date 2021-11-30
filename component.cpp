#include "main.h"
#include "sprite.h"

#include "camera.h"
#include "component.h"
#include <vector>
using std::vector;

GameObject::GameObject()
{
	displayNum = 0;
	colliderNum = 0;

	p_displays = nullptr;
	pp_colliders = nullptr;
}

GameObject::~GameObject()
{
	//delete p_displays;
	//delete pp_colliders;
}

void GameObject::CreateDisplay(int displayNum)
{
	if (p_displays)delete[] p_displays;
	this->displayNum = displayNum;
	p_displays = new Display[displayNum];
}

void GameObject::CreateCollider(int colliderNum)
{
	if (pp_colliders)delete[] pp_colliders;
	this->colliderNum = colliderNum;
	pp_colliders = (Collider**)malloc(colliderNum);
}

void GameObject::Update()
{
	for (int i = 0; i < displayNum; i++)
	{
		Display* pDisplay = &p_displays[i];
		Animation* pAnimation = &pDisplay->p_animes[pDisplay->animeID];

		pAnimation->frameCount++;
		if (pAnimation->frameCount >= pAnimation->frameMax)
		{
			pAnimation->frameCount = 0;
			pAnimation->pieceID++;
			if (pAnimation->pieceID >= pAnimation->pieceMax)
			{
				pAnimation->pieceID = 0;
			}
		}
	}
}

void GameObject::Draw()
{
	for (int i = 0; i <displayNum; i++)
	{
		Display* pDisplay = &p_displays[i];
		Animation* pAnimation = &pDisplay->p_animes[pDisplay->animeID];
		D3DXVECTOR4 uv = pAnimation->p_pieceUVs[pAnimation->pieceID];

		int texNo = pDisplay->texNo;
		float x =transform.position.x + pDisplay->posOffset.x;
		float y =transform.position.y + pDisplay->posOffset.y;
		float w =transform.scale.x * pDisplay->size.x;
		float h =transform.scale.y * pDisplay->size.y;
		float tx = uv.x;
		float ty = uv.y;
		float tw = uv.z;
		float th = uv.w;
		D3DXCOLOR cl = pDisplay->color;

		D3DXVECTOR2 offsetPos = pDisplay->posOffset;
		float offsetRot = atan2f(-offsetPos.y, offsetPos.x);
		float rot = transform.rotation + offsetRot;
		DrawSpriteColorRotate(
			texNo,
			x, y, w, h,
			tx, ty, tw, th,
			cl,
			rot
		);
	}

	if (CanShowCol())
	{
		for (int i = 0; i < colliderNum; i++)
		{
			Collider* pCollider = pp_colliders[i];

			int texNo = GetColTexNo();
			float x = transform.position.x + pCollider->posOffset.x;
			float y = transform.position.y + pCollider->posOffset.y;
			float w;
			float h;
			if (pCollider->type == ColliderType::rect)
			{
				w = transform.scale.x * pCollider->RectGetRectSize().x;
				h = transform.scale.y * pCollider->RectGetRectSize().y;
			}
			else if (pCollider->type == ColliderType::circle)
			{
				w = transform.scale.x * (pCollider->CircleGetRadiusRadius() * 2);
				h = transform.scale.y * (pCollider->CircleGetRadiusRadius() * 2);
			}
			else if (pCollider->type == ColliderType::capsule)
			{
				w = transform.scale.x * (pCollider->CapsuleGetRectVector().x + pCollider->CapsuleGetRectRadius() * 2);
				h = transform.scale.y * (pCollider->CapsuleGetRectRadius() * 2);
			}

			float tx = 0;
			float ty = 0;
			float tw = 1;
			float th = 1;
			D3DXCOLOR cl = { 1,0,0,0.2f };

			D3DXVECTOR2 offsetPos = pCollider->posOffset;
			float offsetRot = atan2f(offsetPos.y, offsetPos.x);
			float rot =transform.rotation + offsetRot;

			DrawSpriteColorRotate(
				texNo,
				x, y, w, h,
				tx, ty, tw, th,
				cl,
				rot
			);
		}
	}
}

Transform::Transform()
{
	position = { 0,0 };
	rotation = 0.0f;
	scale = { 1,1 };
}

Collider::Collider()
{
	posOffset = { 0,0 };
}

Collider::Collider(ColliderType _type)
{
	posOffset = { 0,0 };
	type = _type;
}

Collider_Rect::Collider_Rect()
{
	size = { 0,0 };
}

Collider_Circle::Collider_Circle()
{
	radius = 0;
}

Collider_Capsule::Collider_Capsule()
{
	rectVector = { 0,0 };
	rectRadius = 0;
}

Display::Display()
{
	posOffset = { 0,0 };
	animeID = 0;
	color = { 1,1,1,1 };
	p_animes = nullptr;
}

Display::~Display()
{
	//delete p_animes;
	p_animes = nullptr;
}

void Display::CreateAnimation(int animeNum)
{
	//if(p_animes)delete p_animes;
	p_animes = new Animation[animeNum];
}

void Display::SetAnimation(int index, int _frameMax, int _pieceMax)
{
	p_animes[index].frameMax = _frameMax;
	p_animes[index].pieceMax = _pieceMax;
}


Animation::Animation()
{
	p_pieceUVs = nullptr;
	pieceID = 0;
	frameCount = 0;
}

Animation::~Animation()
{
	//delete p_pieceUVs;
	p_pieceUVs = nullptr;
}

void Animation::CreatePieceUV(int pieceNum)
{
	//if (p_pieceUVs)delete p_pieceUVs;
	p_pieceUVs = new D3DXVECTOR4[pieceNum];
}

void Animation::SetPieceUV(int index, D3DXVECTOR4 uv)
{
	p_pieceUVs[index] = uv;
}
