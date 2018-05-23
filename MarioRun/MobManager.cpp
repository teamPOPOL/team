#include "stdafx.h"

MobManager::MobManager()
{
}

MobManager::~MobManager()
{
}

void MobManager::Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed, MobType Type)
{
	Object* mob = NULL;
	switch (Type)
	{
	case MobManager::GUMBA:
		mob = new Gumba;
		break;
	default:
		break;
	}
	mob->Init(Scale, Rotation, Pos, Speed);
	MobList.push_back(mob);
	TypeList.push_back(Type);
}

void MobManager::Update()
{
	for (size_t i = 0; i < MobList.size(); i++)
	{
		MobList[i]->Update();
	}
}

void MobManager::Render()
{
	for (size_t i = 0; i < MobList.size(); i++)
	{
		MobList[i]->Render();
	}
}

void MobManager::CollisionCheck(Player * player)
{
	for (size_t i = 0; i < MobList.size(); i++)
	{
		if (MobList[i]->isDraw())
		{
			Direction test = COLLISION->IntersectRectDir(player, MobList[i]);
			if (test != Direction::None)
			{
				if (test == Direction::Top)
				{
					if (player->isDraw())
					{
						player->Reaction();
						MobList[i]->Damage();
					}
				}
				else
					player->Damage();
			}
		}
	}
}

void MobManager::FireballCheck(vector<FireBall*> List)
{
	
	for (size_t i = 0; i < List.size(); i++)
	{
		if (List[i]->isDraw())
		{
			for (size_t j = 0; j < MobList.size(); j++)
			{
				if (MobList[j]->isDraw())
				{
					if (Rect::Intersect(MobList[j]->GetRc(), List[i]->GetRc()))
					{
						MobList[j]->DrawFalse();
						List[i]->DrawFalse();
					}
				}
			}
		}
	}
}
