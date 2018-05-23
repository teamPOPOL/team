#include "stdafx.h"
#include "GameMain.h"

GameMain::GameMain(HINSTANCE instance)
	: Window(instance)
{

}

GameMain::~GameMain()
{

}

void GameMain::Initialize()
{
	gm = new GamaManager;
}

void GameMain::Destroy()
{
	
}

void GameMain::Update()
{
	gm->Update();
}

void GameMain::Render()
{
	gm->Render();
}
