#pragma once

class Mushroom : public Object
{
private:
	Texture * texture;
	bool isRight;
public:
	Mushroom();
	~Mushroom();

	virtual void Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed); 
	virtual void Update();
	virtual void Render();
};