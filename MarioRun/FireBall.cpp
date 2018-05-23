#include "stdafx.h"

FireBall::FireBall()
{
	LoadXml();
	Object::Object();
	isRight = false;
}

FireBall::~FireBall()
{
}

void FireBall::Init(D3DXVECTOR2 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Pos, float Speed, bool isRight)
{
	Object::Init(Scale, Rotation, Pos, Speed);
	this->isRight = isRight;
	ani[0]->Play();
	ani[0]->GetTexture()->GetRealSize(&ImageSize, Scale);
	isJump = true;
}

void FireBall::Update()
{
	if (!Draw)
		return;
	if (isRight)
		Pos.x += Speed * TIMER->TimeElapsed();
	else
		Pos.x -= Speed * TIMER->TimeElapsed();

	if (!isJump)
	{
		JumpPower = 200.0f;
		isJump = true;
	}

	ani[0]->Update();
	Object::Jump(WIN_HEIGHT);
	Object::Update();
}

void FireBall::Render()
{
	if (!Draw)
		return;
	Object::Render();
	ani[0]->Render();
}

void FireBall::LoadXml()
{
	XmlDocument* doc = new XmlDocument;
	XmlError error;
	error = doc->LoadFile("Image/FireBall.xml");
	assert(error == Xml::XML_SUCCESS);

	XmlElement* atlas = doc->FirstChildElement("TextureAtlas");
	string fileName = atlas->Attribute("imagePath");
	fileName = "Image/" + fileName;
	wstring path;
	path.assign(fileName.begin(), fileName.end());

	XmlElement* Ani = atlas->FirstChildElement("Fire");

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

	SAFE_DELETE(doc);
}
