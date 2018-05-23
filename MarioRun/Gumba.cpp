#include "stdafx.h"

Gumba::Gumba()
{
	LoadXml();
	state = RUN;
	ani[state]->Play();
	isRight = true;
	DieTime = 0.0f;
}

Gumba::~Gumba()
{
}

void Gumba::Update()
{
	if (state != DIE)
	{
		if (rc.GetRight() >= WIN_WIDTH)
			isRight = false;
		else if (rc.GetLeft() <= 0.0f)
			isRight = true;

		if (isRight)
			Pos.x += Speed * TIMER->TimeElapsed();
		else
			Pos.x -= Speed * TIMER->TimeElapsed();
	}
	else
	{
		DieTime -= TIMER->TimeElapsed();
		if (DieTime <= 0.0f)
			Draw = false;
	}
	ani[state]->Update();
	ani[state]->GetTexture()->GetRealSize(&ImageSize, Scale);
	WallCheck();
	Object::Update();
}

void Gumba::Render()
{
	if (!Draw)
		return;
	Object::Render();
	ani[state]->Render();
}

void Gumba::Damage()
{
	state = DIE;
	DieTime = 1.0f;
	Pos.y += ImageSize.y / 2;
}

bool Gumba::isDraw()
{
	if (state == DIE || !Draw)
		return false;
	return true;
}

void Gumba::LoadXml()
{
	XmlDocument* doc = new XmlDocument;
	XmlError error;
	error = doc->LoadFile("Image/Gumba.xml");
	assert(error == Xml::XML_SUCCESS);

	XmlElement* atlas = doc->FirstChildElement("TextureAtlas");
	string fileName = atlas->Attribute("imagePath");
	fileName = "Image/" + fileName;
	wstring path;
	path.assign(fileName.begin(), fileName.end());

	XmlElement* Ani = atlas->FirstChildElement();

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
	SAFE_DELETE(doc);
}
