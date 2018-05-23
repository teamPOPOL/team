#pragma once

class GamaManager
{
private:
	Player * player;
	MobManager * Mm;
	ItemManager * Im;
public:
	GamaManager();
	~GamaManager();

	void Update();
	void Render();
};