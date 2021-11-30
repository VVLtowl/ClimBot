#include "gameobject.h"
#include "sprite.h"

//クラスに必要++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GameObject::GameObject()
{
	this->m_position = { 0,0 };
	this->m_uvwh = { 0,0,1,1};
	this->m_size = { 10,10 };
	this->m_color = { 1.0,1.0,1.0,1.0 };

	this->m_center = this->CenterType::center;
	this->m_texture = -1;
}

GameObject::~GameObject()
{

}

//gameobjectクラス特有++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void GameObject::Draw()
{
	int texID = this->m_texture;
	float x = this->m_position.x;
	float y = this->m_position.y;
	float w = this->m_size.x;
	float h = this->m_size.y;
	float tx = this->m_uvwh.x;
	float ty = this->m_uvwh.y;
	float tw = this->m_uvwh.z;
	float th = this->m_uvwh.w;

	DrawSpriteLeftTop(texID,
		x, y, w, h,
		tx, ty, tw, th);
}

void GameObject::Update()
{
}
