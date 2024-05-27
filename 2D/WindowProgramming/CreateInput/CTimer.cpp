#include "CTimer.h"

void CTimer::DebugTimer()
{
#ifdef _DEBUG
	TCHAR msgKey[MAX_PATH] = { 0, };
	_stprintf_s(msgKey,
		L"FPS=%ld, GameTimer=%10.4f SPF=%d\n",
		m_dwFPS, m_fGameTimeTick,
		m_dwSecondPerFrame);
	OutputDebugString(msgKey);
#endif
}

void CTimer::Init()
{
	m_fpreTimeTick = timeGetTime();
	m_fCurrentTimeTick = 0.0f;
	m_fGameTimeTick = 0.0f;
	m_dwFPS = 0;
}

void CTimer::Frame()
{
	// 이전시간
	// 현재시간
	m_fCurrentTimeTick = timeGetTime();
	// 경과시간(초단위) =  현재시간 - 이전시간
	m_dwSecondPerFrame = m_fCurrentTimeTick - m_fpreTimeTick;
	m_fSecondPerFrame = m_dwSecondPerFrame / 1000.0f;
	m_fGameTimeTick += m_fSecondPerFrame;

	static int iFPS = 0;
	static float fSecondTime = 0.0f;
	fSecondTime += m_fSecondPerFrame;
	if (fSecondTime >= 1.0f)
	{
		m_dwFPS = iFPS;
		fSecondTime = fSecondTime - 1.0f;
		iFPS = 0;
	}
	iFPS++;

	m_fpreTimeTick = m_fCurrentTimeTick;
}
