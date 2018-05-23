#pragma once

class ItemManager
{
public:
	enum ItemType
	{
		COIN,
		MUSHROOM,
		FLOWER
	};
	ItemManager();
	~ItemManager();

	void Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed, ItemType Type);
	void Update();
	void Render();

	void CollisionCheck(Player* player);
private:
	vector<Object*> ItemList;
	vector<ItemType> TypeList;
};