#pragma once

class Object : public ISpotPoint
{
protected:
	vector<Animator*> ani;
	//World* world;
	SRT* srt;

	D3DXVECTOR2 Pos;
	D3DXVECTOR2 Scale;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR2 * Center;

	D3DXVECTOR2 ImageSize;
	Rect rc;

	float Speed;
	float JumpPower;

	bool isJump;
	bool Draw;
public:
	Object();
	~Object();

	virtual void Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed);
	virtual void Update();
	virtual void Render();

	virtual void WallCheck(/*타일이 들어간 벡터 매개변수 넣기 ex)Tile* tile*/);
	virtual void Jump(float LandY);
	virtual void SetRc();
	virtual void LoadXml();
	virtual void Damage();
	virtual bool isDraw();
	virtual void DrawFalse() { Draw = false; }
	void GetSpotPoint(D3DXVECTOR2* position,
		D3DXVECTOR2* size)
	{
		*position = Pos;
		*size = ImageSize;
	}

	Rect GetRc() { return rc; }
};