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
	float DieTime;	//�״� �ִϸ��̼� �����ִ� �ð�
public:
	Gumba();
	~Gumba();
	virtual void Update();
	virtual void Render();

	void Damage();
	bool isDraw();
	void LoadXml();
};