#pragma once
#include "main.h"

class GameObject
{
public:
	enum  CenterType
	{
		center,
		leftTop,
	};

	GameObject();

	virtual ~GameObject();

	void SetPosition(D3DXVECTOR2 position) { m_position = position; }
	D3DXVECTOR2 GetPosition() { return m_position; }

	void SetUVWH(D3DXVECTOR4 uvwh) { m_uvwh = uvwh; }
	D3DXVECTOR4 GetUVWH() { return m_uvwh; }

	void SetSize(D3DXVECTOR2 size) { m_size = size; }
	D3DXVECTOR2 GetSize() { return m_size; }

	void SetRotate(float rotate) { m_rotate = rotate; }
	float GetRotate() { return m_rotate; }

	void SetColor(D3DXCOLOR color) { m_color = color; }
	D3DXCOLOR GetColor() { return m_color; }

	void SetTexture(int texture) { m_texture = texture; }
	int GetTexture() { return m_texture; }

	void SetCenterType(int centerType) { m_center = centerType; }
	int GetCenterType() { return m_center; }

	virtual void Draw();
	virtual void Update();



private:
	D3DXVECTOR2 m_position;
	D3DXVECTOR2 m_size;
	//D3DXVECTOR2 m_scale;
	float m_rotate;
	D3DXVECTOR4 m_uvwh;
	D3DXCOLOR   m_color;

	int m_center;
	int m_texture;
};