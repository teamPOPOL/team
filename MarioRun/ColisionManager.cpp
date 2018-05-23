#include "stdafx.h"

CollisionManager* CollisionManager::instance = NULL;

CollisionManager::CollisionManager()
{
	PlayerDamage = NULL;
}

CollisionManager::~CollisionManager()
{
}

CollisionManager * CollisionManager::Get()
{
	if (instance == NULL)
		instance = new CollisionManager;

	return instance;
}

float CollisionManager::GetLandY(vector<Rect*> Tiles, Object * obj)
{
	return WIN_HEIGHT;
}

bool CollisionManager::IntersectRect(Object * obj1, Object * obj2)
{
	if (Rect::Intersect(obj1->GetRc(), obj2->GetRc()))
		return true;
	return false;
}

Direction CollisionManager::IntersectRectDir(Object * obj1, Object * obj2)
{
	return Rect::IntersectDir(obj1->GetRc(), obj2->GetRc());
}
