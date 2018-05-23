#pragma once

class MobManager
{
public:
	enum MobType
	{
		GUMBA,
	};
	MobManager();
	~MobManager();

	void Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed, MobType Type);
	void Update();
	void Render();

	void CollisionCheck(Player * player);
	void FireballCheck(vector<FireBall*> List);
private:
	vector<Object*> MobList;
	vector<MobType> TypeList;
};