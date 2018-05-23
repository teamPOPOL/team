#include "stdafx.h"

Coin::Coin()
{
	Object::Object();
	texture = Texture::Add(L"Image/CoinIdle.png");
	texture->GetRealSize(&ImageSize);
}

Coin::~Coin()
{
}


void Coin::Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed)
{
	Object::Init(Scale, Rotation, Pos, Speed);
	texture->GetRealSize(&ImageSize, Scale);
}

void Coin::Render()
{
	if (!Draw)
		return;
	Object::Render();
	Device::StartAlphaRender();
	texture->Render();
	Device::EndAlphaRender();
}
