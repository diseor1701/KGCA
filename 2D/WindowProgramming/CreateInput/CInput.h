#pragma once
#include <windows.h>
#include <tchar.h>

enum KeyState
{
	KEY_FREE = 0,	// ����
	KEY_UP,			// �ٷ� �����ٰ� ���»���
	KEY_PUSH,		// ���»��¿��� ������ ��
	KEY_HOLD,		// ������ ���� ��(������ ������ ���ݵ� ������.)
};

class CInput
{
private:
	DWORD g_dwKeyState[256];
	POINT m_ptMousePos;
public:
	void DebugPrint(int ikey);
	void DebugMousePos();
	void Frame(HWND hWnd);
	DWORD KeyCheck(DWORD dwKey);
	void KeyTest();
public:
	CInput() 
	{
		ZeroMemory(&g_dwKeyState, sizeof(DWORD) * 256);
	}
};

