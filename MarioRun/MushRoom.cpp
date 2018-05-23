#include "stdafx.h"

Mushroom::Mushroom()
{
	Object::Object();
	texture = Texture::Add(L"Image/mushroom.png");
}

Mushroom::~Mushroom()
{
}

void Mushroom::Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed)
{
	Object::Init(Scale, Rotation, Pos, Speed);
	texture->GetRealSize(&ImageSize, Scale);
}

void Mushroom::Update()
{
	if (isRight)
		Pos.x += Speed * TIMER->TimeElapsed();
	else
		Pos.x -= Speed * TIMER->TimeElapsed();

	if (rc.GetRight() >= WIN_WIDTH)
		isRight = false;
	if (rc.GetLeft() <= 0.0f)
		isRight = true;
	Jump(WIN_HEIGHT);
	Object::Update();
}

void Mushroom::Render()
{
	if (!Draw)
		return;
	Object::Render();
	Device::StartAlphaRender();
	texture->Render();
	Device::EndAlphaRender();
}
