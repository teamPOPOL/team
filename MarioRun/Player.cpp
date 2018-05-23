#include "stdafx.h"

Player::Player()
{
	LoadXml();
	Object::Object();
	fm = new FireManager;
	coin = 0;
	AttackTime = 0.0f;
	isBig = false;
	isFlower = false;
	isAttack = false;
}

Player::~Player()
{
}

void Player::Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed, int Coin)
{
	Object::Init(Scale, Rotation, Pos, Speed);
	coin = Coin;
	ani[state]->Play();
	fm->Init(50);
}

void Player::Update()
{
	AttackTime += TIMER->TimeElapsed();
	if (AttackTime >= 0.5f)
		isAttack = false;

	if ( state < BIGGER)
	{
		if (state != DIE)
		{
			if (!isJump && !isAttack)
			{
				if (isFlower)
					state = FIDLE;
				else if (isBig)
					state = BIGIDLE;
				else
					state = SMALLIDLE;
			}

			if (KEYBOARD->KeyDown(VK_RIGHT))
			{
				if (isFlower)
					ani[FRUN]->Play();
				else if (isBig)
					ani[BIGRUN]->Play();
				else
					ani[SMALLRUN]->Play();
				Rotation.y = 0.0f;
			}

			if (KEYBOARD->KeyDown(VK_LEFT))
			{
				if (isFlower)
					ani[FRUN]->Play();
				else if (isBig)
					ani[BIGRUN]->Play();
				else
					ani[SMALLRUN]->Play();
				Rotation.y = -Math::PI;
			}

			if (KEYBOARD->KeyPress(VK_RIGHT))
			{
				Pos.x += Speed * TIMER->TimeElapsed();
				if (!isJump&& state != CROUCH)
				{
					if (isFlower)
						state = FRUN;
					else if (isBig)
						state = BIGRUN;
					else
						state = SMALLRUN;
				}
			}

			if (KEYBOARD->KeyPress(VK_LEFT))
			{
				Pos.x -= Speed * TIMER->TimeElapsed();
				if (!isJump && state != CROUCH)
				{
					if (isFlower)
						state = FRUN;
					else if (isBig)
						state = BIGRUN;
					else
						state = SMALLRUN;
				}
			}

			if (KEYBOARD->KeyDown(VK_SPACE))
			{
				if (!isJump)
				{
					JumpPower = 700;
					isJump = true;
					if (isFlower)
						state = FJUMP;
					else if (isBig)
						state = BIGJUMP;
					else
						state = SMALLJUMP;
				}
			}

			if (KEYBOARD->KeyDown(VK_LSHIFT))
			{
				if (!isAttack && isFlower)
				{
					state = ATTACK;
					if (Rotation.y == -Math::PI)	//¿ÞÂÊ
						fm->SetFireBall(rc, false);
					else
						fm->SetFireBall(rc, true);
					isAttack = true;
					AttackTime = 0.0f;
				}
			}
		}
		WallCheck();
	}
	if (ani[state]->isEnd() && ChangePlayer())
	{
		switch (state)
		{
		case Player::BIGGER:
			isBig = true;
			ani[state]->SetClipInit();
			state = BIGIDLE;
			break;
		case Player::BIGFLOWER:
			ani[state]->SetClipInit();
			state = FIDLE;
			isFlower = true;
			isBig = true;
			break;
		case Player::SMALLER:
			isBig = false;
			ani[state]->SetClipInit();
			state = SMALLIDLE;
			Pos.y += ImageSize.y / 2 - 100;
			break;
		case Player::NOTFLOWER:
			ani[state]->SetClipInit();
			state = BIGIDLE;
			isFlower = false;
			break;
		default:
			break;
		}
	}
	fm->Update();
	ani[state]->Update();
	Object::Update();
}

void Player::Render()
{
	Object::Render();
	ani[state]->Render();
	fm->Render();
}

void Player::SetRc()
{
	if (isBig)
		ani[BIGIDLE]->GetTexture()->GetRealSize(&ImageSize, Scale);
	else
		ani[SMALLIDLE]->GetTexture()->GetRealSize(&ImageSize, Scale);
		
	
	Object::SetRc();
}

bool Player::isDraw()
{
	if (state == DIE)
		return false;
	return true;
}

void Player::Jump(float LandY)
{
	if (isJump)
	{
		JumpPower -= GRAVITY;
		Pos.y -= JumpPower * TIMER->TimeElapsed();
		SetRc();
		if (rc.GetBottom() >= LandY && isDraw())
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

void Player::Damage()
{
	if (isFlower)
	{
		state = NOTFLOWER;
		ani[state]->Play();
	}
	else if (isBig)
	{
		state = SMALLER;
		ani[state]->Play();
		ani[SMALLIDLE]->GetTexture()->GetRealSize(&ImageSize, Scale);
	}
	else
	{
		if (state != DIE)
		{
			JumpPower = 1000.0f;
			isJump = true;
			state = DIE;
		}
	}
}

void Player::Reaction()
{
	JumpPower = 300.0f;
	isJump = true;
}

void Player::LoadXml()
{
	XmlDocument* doc = new XmlDocument;
	XmlError error;
	error = doc->LoadFile("Image/Mario.xml");
	assert(error == Xml::XML_SUCCESS);

	XmlElement* atlas = doc->FirstChildElement("TextureAtlas");
	string fileName = atlas->Attribute("imagePath");
	fileName = "Image/" + fileName;
	wstring path;
	path.assign(fileName.begin(), fileName.end());

	XmlElement* Size = NULL;
	Size = atlas->FirstChildElement("Big");
	for (; Size != NULL; Size = Size->NextSiblingElement())
	{
		XmlElement* Ani = Size->FirstChildElement();
		for (; Ani != NULL; Ani = Ani->NextSiblingElement())
		{
			UINT repeat = Ani->UnsignedAttribute("Repeat");
			DWORD time = Ani->UnsignedAttribute("Time");

			vector<AnimationClip> clips;

			XmlElement* frame = Ani->FirstChildElement();
			for (; frame != NULL; frame = frame->NextSiblingElement())
			{
				D3DXVECTOR2 startPos;
				startPos.x = frame->FloatAttribute("x");
				startPos.y = frame->FloatAttribute("y");
				D3DXVECTOR2 endPos;
				endPos.x = frame->FloatAttribute("w");
				endPos.y = frame->FloatAttribute("h");
				endPos += startPos;

				Texture* texture = Texture::Add(path, startPos, endPos);
				clips.push_back(AnimationClip(texture, time));
			}

			Animator* animator = new Animator(&clips, (Type)repeat);
			ani.push_back(animator);
		}
	}

	SAFE_DELETE(doc);
}

void Player::Big()
{
	if (!isBig)
	{
		state = BIGGER;
		ani[state]->Play();
		ani[BIGIDLE]->GetTexture()->GetRealSize(&ImageSize, Scale);
		Pos.y -= ImageSize.y / 2 + 2;
	}
}

void Player::EatFlower()
{
	if (!isFlower)
	{
		isFlower = true;
		state = BIGFLOWER;
		ani[state]->Play();
		ani[BIGIDLE]->GetTexture()->GetRealSize(&ImageSize, Scale);
		if(!isBig)
			Pos.y -= ImageSize.y / 2 + 2;
	}
}
