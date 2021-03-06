#pragma once 
#include "Window.h"

class GameMain : public Window
{
private:
	GamaManager * gm;
public:
	GameMain(HINSTANCE instance);
	~GameMain();

	void Initialize();
	void Destroy();
	void Update();
	void Render();	
};