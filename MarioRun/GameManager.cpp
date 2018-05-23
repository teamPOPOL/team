#include "stdafx.h"

GamaManager::GamaManager()
{
	CAMERA->SetFollowCamera();
	player = new Player;
	player->Init(D3DXVECTOR2{ 1.0f, 1.0f }, BASICROTATION, D3DXVECTOR2{ WIN_WIDTH - 100 , 0.0f }, 300.0f, 300);
	Mm = new MobManager;
	Mm->Init(D3DXVECTOR2{ 2.0f, 2.0f }, BASICROTATION, BASICPOS, 100.0f, MobManager::GUMBA);
	Mm->Init(D3DXVECTOR2{ 2.0f, 2.0f }, BASICROTATION, BASICPOS, 10.0f, MobManager::GUMBA);
	Mm->Init(D3DXVECTOR2{ 2.0f, 2.0f }, BASICROTATION, BASICPOS, 50.0f, MobManager::GUMBA);
	Im = new ItemManager;
	for (float i = 0; i < 2; i++)
	{
		Im->Init(D3DXVECTOR2{ 2.0f, 2.0f }, BASICROTATION, D3DXVECTOR2{ WIN_WIDTH / 2 - 100 * i, WIN_HEIGHT / 2 }, 0.0f, ItemManager::COIN);
		Im->Init(D3DXVECTOR2{ 2.0f, 2.0f }, BASICROTATION, D3DXVECTOR2{ WIN_WIDTH / 2 - 100 * i, WIN_HEIGHT / 2 }, 100.0f, ItemManager::ItemType::MUSHROOM);
		Im->Init(BASICSCALE, BASICROTATION, D3DXVECTOR2{ WIN_WIDTH / 2 - 100 * i, WIN_HEIGHT / 2 }, 100.0f, ItemManager::ItemType::FLOWER);
	}
}

GamaManager::~GamaManager()
{
}

void GamaManager::Update()
{
	player->Update();
	if (!player->ChangePlayer())
	{
		Mm->Update();
		Mm->CollisionCheck(player);
		Mm->FireballCheck(player->GetFireList());
		Im->Update();
		Im->CollisionCheck(player);
	}

	CAMERA->Update();
}

void GamaManager::Render()
{
	player->Render();
	Mm->Render();
	Im->Render();;
}
