#pragma once
#include <Windows.h>
#include <string>
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

	DWORD m_dwpreTimeTick;
	DWORD m_dwCurrentTimeTick;

	int		iFPS = 0;
	float	fSecondTime = 0.0f;
public:
	std::wstring   m_csBuffer;
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

