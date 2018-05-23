#pragma once

//enum �ߺ� �ذ���
//1. namespace �̿�
/*
namespace ANI
{
	enum Type
	{
		END,
		LOOP,
		REVERSE
	};
}*/

//2. enum class ���
enum class Type
{
	END,
	LOOP,
	REVERSE
};

struct AnimationClip
{
	DWORD time;
	Texture* texture;

	AnimationClip()
	{
		texture = NULL;
		time = 0;
	}
	AnimationClip(Texture* texture, DWORD time)
	{
		this->texture = texture;
		this->time = time;
	}
};

class Animator
{
private:
	vector<AnimationClip> clips;

	Type repeatType;
	bool isReverseRight;
	bool isPlay;
	DWORD playTime;
	UINT curClipNumber;

public:
	Animator(vector<AnimationClip>* srcClips,
		Type type = Type::END);

	void Play();
	void Pause();
	void Stop();

	void Update();
	void Render(bool Alpha = true);

	void SetClipInit() { curClipNumber = 0; }
	Texture* GetTexture()
	{
		return clips[curClipNumber].texture;
	}
	LPDIRECT3DTEXTURE9 GetDxTexture()
	{
		return clips[curClipNumber].texture->GetTexture();
	}
	bool isEnd()
	{
		if (curClipNumber == clips.size() - 1)
			return true;
		return false;
	}
};