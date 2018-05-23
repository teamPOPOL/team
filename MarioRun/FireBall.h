#pragma once

class FireBall : public Object
{
private:
	bool isRight;
public:
	FireBall();
	~FireBall();

	virtual void Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed, bool isRight);
	virtual void Update();
	virtual void Render();

	void LoadXml();
};