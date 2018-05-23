#include "stdafx.h"

Animator::Animator(vector<AnimationClip>* srcClips, Type type)
{
	repeatType = type;
	curClipNumber = 0;
	isPlay = false;
	isReverseRight = false;

	for (size_t i = 0; i < srcClips->size(); i++)
	{
		//AnimationClip clip = (*srcClips)[i];
		AnimationClip clip = srcClips->at(i);
		clip.time = clip.time < 1 ? 100 : clip.time;
		clips.push_back(clip);
	}
}

void Animator::Play()
{
	isPlay = true;
	playTime = timeGetTime();
}

void Animator::Pause()
{
	isPlay = false;
}

void Animator::Stop()
{
	isPlay = false;
	curClipNumber = 0;
}

void Animator::Update()
{
	if (!isPlay)
		return;

	AnimationClip clip = clips[curClipNumber];

	if (timeGetTime() - playTime > clip.time)
	{
		switch (repeatType)
		{
		case Type::END:
			curClipNumber++;
			if (curClipNumber >= clips.size())
				curClipNumber--;
			break;
		case Type::LOOP:
			curClipNumber++;
			curClipNumber %= clips.size();
			break;
		case Type::REVERSE:
			if (isReverseRight)
			{
				curClipNumber++;
				if (curClipNumber >= clips.size())
					isReverseRight = false;
			}
			else
			{				
				if (curClipNumber <= 0)
					isReverseRight = true;
				curClipNumber--;
			}
			break;
		default:
			break;
		}
		playTime = timeGetTime();
	}
}

void Animator::Render(bool Alpha)
{
	AnimationClip clip = clips[curClipNumber];
	Device::StartAlphaRender();
	clip.texture->Render();
	Device::EndAlphaRender();
}
