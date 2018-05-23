#pragma once

class FireManager
{
private:
	vector<FireBall*> List;
	int MaxSize;
public:
	FireManager();
	~FireManager();

	void Init(int MaxSize);
	void Update();
	void Render();

	void SetFireBall(Rect rc, bool isRight);
	vector<FireBall*> GetList() { return List; }
};