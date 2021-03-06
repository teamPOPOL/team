#pragma once

#include "targetver.h"

#include <Windows.h>
#include <assert.h>
#include <Math.h>
#include <time.h>

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <functional>
using namespace std;

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma comment(lib, "winmm.lib")

#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}
#define SAFE_DELETE(p) { if (p) { delete (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p)=NULL; } }

#define DEVICE Device::GetDevice()
#define KEYBOARD Keyboard::Get()
#define MOUSE Mouse::Get()
#define TIMER Frames::Get()
#define CAMERA MainCamera::Get()
#define COLLISION CollisionManager::Get()

#define COLOR_R 0xffff0000
#define COLOR_G 0xff00ff00
#define COLOR_B 0xff0000ff
#define COLOR_W 0xffffffff

#define GRAVITY 1

#define BASICSCALE D3DXVECTOR2{1.0f, 1.0f}
#define BASICROTATION D3DXVECTOR3{0.0f, 0.0f, 0.0f}
#define BASICPOS D3DXVECTOR2{0.0f, 0.0f}

typedef function<void()> CALL_FUNC;

//Core Header File
#include "Math.h"
#include "Size.h"
#include "Point.h"
#include "Rect.h"

//Camera Header File
#include "Camera.h"
#include "FreeView.h"
#include "FollowView.h"
#include "Factory.h"
#include "MainCamera.h"

//System Header File
#include "Device.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Frames.h"
#include "Xml.h"

//Render Header File
#include "Texture.h"
#include "Animator.h"

//Util Header File
#include "World.h"
#include "SRT.h"
#include "CollisionManager.h"

#define WIN_X 100 //시작 X위치
#define WIN_Y 100 //시작 Y위치
#define WIN_WIDTH 1024 //시작 윈도우 크기
#define WIN_HEIGHT 768 //시작 윈도우 크기
#define WIN_TITLE L"Win32 Game" //윈도우 타이틀 및 클래스명
#define WIN_SHOW_CURSOR TRUE //윈도우 커서를 보여줄지?

//GameObject Header File
#include "Object.h"
#include "FireBall.h"
#include "FireManager.h"
#include "Player.h"
#include "Gumba.h"
#include "Turtle.h"
#include "MobManager.h"
#include "Coin.h"
#include "MushRoom.h"
#include "Flower.h"
#include "ItemManager.h"

//GameManager
#include "GameManager.h"