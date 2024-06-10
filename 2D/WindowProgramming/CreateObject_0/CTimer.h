#pragma once
#include <Windows.h>
#include <string>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

class CTimer
{
	// 게임 경과 시간
	float m_fGameTimeTick;
	// 1프레임의 경과시간
	float m_fSecondPerFrame = 0.0f;
	DWORD m_dwSecondPerFrame = 0;
	// 1초에 경과한 프레임 카운터
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

