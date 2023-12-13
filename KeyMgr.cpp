#include "KeyMgr.h"

void KeyMgr::CheckKey()
{
	dwKey = 0;

	// 0 (0x0000)	- 이전에 누른 적이 없고, 호출 시점에서 안 눌린 상태
	// 0x8000		- 이전에 누른 적이 없고, 호출 시점에서 눌린 상태
	// 0x8001		- 이전에 누른 적이 있고, 호출 시점에서 눌린 상태
	// 1 (0x0001)	- 이전에 누른 적이 있고, 호출 시점에서 안 눌린 상태

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		dwKey |= KEY_UP;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		dwKey |= KEY_DOWN;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		dwKey |= KEY_LEFT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		dwKey |= KEY_RIGHT;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		dwKey |= KEY_SPACE;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		dwKey |= KEY_LM;
	}

	if (GetAsyncKeyState('1') & 0x8000)
	{
		dwKey |= KEY_1;
	}
}

KeyMgr::KeyMgr()
{
}

KeyMgr::~KeyMgr()
{
}
