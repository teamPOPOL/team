#pragma once

class Flower : public Object
{
private:
	Texture * texture;

public:
	Flower();
	~Flower();

	virtual void Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed);
	virtual void Update();
	virtual void Render();
};