#include "stdafx.h"

FireManager::FireManager()
{
	MaxSize = 0;
}

FireManager::~FireManager()
{
}

void FireManager::Init(int MaxSize)
{
	this->MaxSize = MaxSize;
	for (int i = 0; i < MaxSize; i++)
	{
		List.push_back(new FireBall);
	}
}

void FireManager::Update()
{
	for (int i = 0; i < MaxSize; i++)
	{
		List[i]->Update();
	}
}

void FireManager::Render()
{
	for (int i = 0; i < MaxSize; i++)
	{
		List[i]->Render();
	}
}

void FireManager::SetFireBall(Rect rc, bool isRight)
{
	for (int i = 0; i < MaxSize; i++)
	{
		if (!List[i]->isDraw())
		{
			D3DXVECTOR2 pos;
			D3DXVECTOR3 rotation = BASICROTATION;
			if (isRight)
				pos.x = rc.GetRight();
			else
			{
				rotation.y = -Math::PI;
				pos.x = rc.GetLeft();
			}
			pos.y = (rc.GetTop() + rc.GetBottom()) / 2;
			List[i]->Init(BASICSCALE, rotation, pos, 400.0f, isRight);
			break;
		}
	}
}
