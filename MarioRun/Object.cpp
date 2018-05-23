#include "stdafx.h"

Object::Object()
{
	Scale = BASICSCALE;
	Rotation = BASICROTATION;
	Pos = BASICPOS;
	Center = NULL;

	JumpPower = 0.0f;
	rc = { 0, 0, 0, 0 };

	isJump = false;
	Draw = false;

	//world = new World;
	srt = new SRT;
}

Object::~Object()
{
}

void Object::Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed)
{
	this->Scale = Scale;
	this->Rotation = Rotation;
	this->Pos = Pos;
	this->Speed = Speed;
	Draw = true;
}

void Object::Update()
{
	SetRc();
}

void Object::Render()
{
	//Device::SetWorld(&world->GetSRT(&Scale, &Rotation, &Pos, Center));
	srt->RenderSetting();
}

void Object::WallCheck()
{
	//for문 돌리면서 오브젝트 x좌표를 포함한 타일 찾기
	//오브젝트 밑 타일 찾기

	//Jump(/*오브젝트 밑 타일*/);
	Jump(WIN_HEIGHT);
}

void Object::Jump(float LandY)
{
	if (isJump)
	{
		JumpPower -= GRAVITY;
		Pos.y -= JumpPower * TIMER->TimeElapsed();
		SetRc();
		if (rc.GetBottom() >= LandY)
		{
			Pos.y = LandY - ImageSize.y;
			JumpPower = 0.0f;
			isJump = false;
		}
	}
	else
	{
		if (rc.GetBottom() < LandY)
			isJump = true;
	}
}

void Object::SetRc()
{
	rc = Rect(Pos.x, Pos.y, ImageSize.x, ImageSize.y);
	srt->SetSRT(&Scale, &Rotation, &Pos, ImageSize, false);
}

void Object::LoadXml()
{
}

void Object::Damage()
{
}

bool Object::isDraw()
{
	return Draw;
}
