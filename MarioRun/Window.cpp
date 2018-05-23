#include "stdafx.h"
#include "Window.h"
#include "GameMain.h"

Window* Window::window = NULL;

Window::Window(HINSTANCE instance)
	: instance(instance), winHandle(NULL)
{
	window = this;
}

Window::~Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message
	, WPARAM wParam, LPARAM lParam)
{
	return Window::GetWindow()->MessageLoop(hwnd, message, wParam, lParam);
}

void Window::Create()
{
	//1. ������ Ŭ���� ���
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_HAND);
	wndClass.hInstance = instance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WIN_TITLE;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	WORD wHr = RegisterClass(&wndClass);
	assert(wHr != 0);


	//2. ������ ����
	winHandle = CreateWindow(
		WIN_TITLE //Ŭ������
		, WIN_TITLE //Ÿ��Ʋ��
		, WS_OVERLAPPEDWINDOW //������ ��Ÿ��
		, CW_USEDEFAULT //x
		, CW_USEDEFAULT //y
		, CW_USEDEFAULT //width
		, CW_USEDEFAULT //height
		, NULL
		, NULL
		, instance //���α׷� �ڵ�
		, NULL
	);
	assert(winHandle != NULL);


	//3. ������ �����ֱ�
	RECT rect = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow
	(
		winHandle
		, WIN_X, WIN_Y
		, rect.right - rect.left, rect.bottom - rect.top
		, TRUE
	);
	ShowWindow(winHandle, SW_SHOWNORMAL);
	ShowCursor(WIN_SHOW_CURSOR);
}

WPARAM Window::Run()
{
	MSG msg = { 0 };

	Device::Get(winHandle);
	TIMER->Start();

	Initialize();
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			KEYBOARD->Update();
			MOUSE->Update();
			TIMER->Update();
			//DX ������Ʈ �� ������
			Update();

			Device::Get()->BeginScene(0xFF555555);
			Render(); //���Ű� ����Ż��̿��� ������
			TIMER->Render();
			Device::Get()->EndScene();
		}
	}
	Destroy();

	Keyboard::Delete();
	Mouse::Delete();

	Device::Delete();
	//DX����
	/*Device::DeleteInstance();*/


	UnregisterClass(WIN_TITLE, instance);
	return msg.wParam;
}

LRESULT Window::MessageLoop(HWND hwnd
	, UINT message, WPARAM wParam, LPARAM lParam)
{
	Mouse::Get()->InputProc(message, wParam, lParam);

	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain
(
	HINSTANCE hInstance
	, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam
	, int nCmdShow
)
{
	srand((UINT)time(NULL));

	GameMain* gameMain = new GameMain(hInstance);
	gameMain->Create();

	WPARAM wParam = gameMain->Run();
	delete gameMain;

	return wParam;
}