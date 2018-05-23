#include "stdafx.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed, ItemType Type)
{
	Object * item = NULL;

	switch (Type)
	{
	case ItemManager::COIN:
		item = new Coin;
		break;
	case ItemManager::MUSHROOM:
		item = new Mushroom;
		break;
	case ItemManager::FLOWER:
		item = new Flower;
		break;
	default:
		break;
	}
	item->Init(Scale, Rotation, Pos, Speed);
	ItemList.push_back(item);
	TypeList.push_back(Type);
}

void ItemManager::Update()
{
	for (size_t i = 0; i < ItemList.size(); i++)
	{
		ItemList[i]->Update();
	}
}

void ItemManager::Render()
{
	for (size_t i = 0; i < ItemList.size(); i++)
	{
		ItemList[i]->Render();
	}
}

void ItemManager::CollisionCheck(Player * player)
{
	for (size_t i = 0; i < ItemList.size(); i++)
	{
		if (ItemList[i]->isDraw())
		{
			if (COLLISION->IntersectRect(player, ItemList[i]))
			{
				switch (TypeList[i])
				{
				case ItemType::COIN:
					player->CoinUp();
					ItemList[i]->DrawFalse();
					break;
				case ItemType::MUSHROOM:
					player->Big();
					ItemList[i]->DrawFalse();
					break;
				case ItemType::FLOWER:
					player->EatFlower();
					ItemList[i]->DrawFalse();
					break;
				default:
					break;
				}
			}
		}
	}
}
