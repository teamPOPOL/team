#pragma once


class Gumba : public Object
{
private:
	enum AniState
	{
		RUN,
		DIE
	};
	AniState state;
	bool isRight;
	float DieTime;	//죽는 애니메이션 보여주는 시간
public:
	Gumba();
	~Gumba();
	virtual void Update();
	virtual void Render();

	void Damage();
	bool isDraw();
	void LoadXml();
};