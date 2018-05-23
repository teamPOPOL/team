#include "stdafx.h"

Flower::Flower()
{
	Object::Object();
	texture = Texture::Add(L"Image/Flower.png");
}

Flower::~Flower()
{
}

void Flower::Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed)
{
	Object::Init(Scale, Rotation, Pos, Speed);
	texture->GetRealSize(&ImageSize, Scale);
}

void Flower::Update()
{
	Jump(WIN_HEIGHT);
	Object::Update();
}

void Flower::Render()
{
	if (!Draw)
		return;
	Object::Render();
	Device::StartAlphaRender();
	texture->Render();
	Device::EndAlphaRender();
}
