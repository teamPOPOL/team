#pragma once

class Player : public Object
{
private:
	enum AniState
	{
		BIGIDLE,
		BIGJUMP,
		BIGRUN,
		CROUCH,
		SMALLIDLE,
		SMALLJUMP,
		SMALLRUN,
		DIE,
		FIDLE,
		FJUMP,
		FRUN,
		FCROUCH,
		ATTACK,
		BIGGER,
		BIGFLOWER,
		SMALLER,
		NOTFLOWER
	};
	AniState state;
	float coin;
	bool isBig; //플레이어가 버섯먹고 커지면 true
	bool isFlower; //플레이어가 꽃을 먹었는지
	bool isAttack;
	float AttackTime;

	FireManager * fm;
public:
	Player();
	~Player();
	virtual void Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed, int Coin);
	virtual void Update();
	virtual void Render();
	virtual void SetRc();
	virtual bool isDraw();

	void Jump(float LandY);
	void Damage();
	void Reaction();
	void LoadXml();

	void Big();
	void EatFlower();
	void CoinUp() { coin++; }
	bool ChangePlayer()
	{
		if (state == BIGGER || state == SMALLER || state == BIGFLOWER || state == NOTFLOWER)
			return true;
		return false;
	}

	vector<FireBall*> GetFireList() { return fm->GetList(); }
};