#pragma once

#define MAX_INPUT_MOUSE 8

class Mouse
{
public:
	static Mouse* Get();
	static void Delete();

	void Update();

	LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);

	Point GetPosition() { return position; }

	bool ButtonDown(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_DOWN;
	}

	bool ButtonUp(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_UP;
	}

	bool ButtonPress(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_PRESS;
	}

private:
	Mouse();
	~Mouse();

	static Mouse* instance;

	HWND handle;
	Point position; //���콺 ��ġ

	byte buttonStatus[MAX_INPUT_MOUSE];
	byte buttonOldStatus[MAX_INPUT_MOUSE];
	byte buttonMap[MAX_INPUT_MOUSE];

	DWORD timeDblClk;
	DWORD startDblClk[MAX_INPUT_MOUSE];
	int buttonCount[MAX_INPUT_MOUSE];

	enum
	{
		MOUSE_ROTATION_NONE = 0,
		MOUSE_ROTATION_LEFT,
		MOUSE_ROTATION_RIGHT
	};

	enum
	{
		BUTTON_INPUT_STATUS_NONE = 0,
		BUTTON_INPUT_STATUS_DOWN,
		BUTTON_INPUT_STATUS_UP,
		BUTTON_INPUT_STATUS_PRESS,
		BUTTON_INPUT_STATUS_DBLCLK
	};
};

