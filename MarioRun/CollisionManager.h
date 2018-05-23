#pragma once
class Object;

class CollisionManager
{
private:
	vector<POINT> WallFrame;	//타일 비교할때 바닥이나 벽인 타일의 프레임
	CALL_FUNC PlayerDamage;

	static CollisionManager * instance;

	CollisionManager();
	~CollisionManager();
public:
	static CollisionManager* Get();

	float GetLandY(vector<Rect*> Tiles, Object * obj);
	bool IntersectRect(Object * obj1, Object * obj2);
	Direction IntersectRectDir(Object * obj1, Object * obj2);

	void SetPlayerDamage(CALL_FUNC func) { PlayerDamage = func; }
};