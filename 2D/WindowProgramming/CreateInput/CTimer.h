#pragma once
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

class CTimer
{
	// ���� ��� �ð�
	float m_fGameTimeTick;
	// 1�������� ����ð�
	float m_fSecondPerFrame = 0.0f;
	DWORD m_dwSecondPerFrame = 0;
	// 1�ʿ� ����� ������ ī����
	DWORD m_dwFPS;

	float m_fpreTimeTick;
	float m_fCurrentTimeTick;
public:
	void DebugTimer();
	void Init();
	void Frame();
public:
	CTimer()
	{
		Init();
	}
};

