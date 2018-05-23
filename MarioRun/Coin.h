#pragma once

class Coin : public Object
{
private:
	Texture * texture;
public:
	Coin();
	~Coin();

	virtual void Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed);
	virtual void Render();
};