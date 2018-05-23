#pragma once

class Turtle : public Object
{
private:
	bool isdie;	//����� �������� true
	bool isRun;
public:
	Turtle();
	~Turtle();

	virtual void Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed);
	virtual void Update();
	virtual void Render();

	void Die();
};