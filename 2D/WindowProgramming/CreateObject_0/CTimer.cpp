#include "CTimer.h"
double   g_fSecondPerFrame = 0.0f;

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
	m_dwpreTimeTick = timeGetTime();
	m_dwCurrentTimeTick = 0.0f;
	m_fGameTimeTick = 0.0f;
	m_dwFPS = 0;
}

void CTimer::Frame()
{
	// �����ð�
	// ����ð�
	m_dwCurrentTimeTick = timeGetTime();
	// ����ð�(�ʴ���) =  ����ð� - �����ð�
	m_dwSecondPerFrame = m_dwCurrentTimeTick - m_dwpreTimeTick;
	m_fSecondPerFrame = m_dwSecondPerFrame / 1000.0f;
	m_fGameTimeTick += m_fSecondPerFrame;

	g_fSecondPerFrame = m_fSecondPerFrame;

	fSecondTime += m_fSecondPerFrame;
	if (fSecondTime >= 1.0f)
	{
		m_dwFPS = iFPS;
		fSecondTime = fSecondTime - 1.0f;
		iFPS = 0;
	}
	iFPS++;

	m_dwpreTimeTick = m_dwCurrentTimeTick;

	TCHAR msgKey[MAX_PATH] = { 0, };
	_stprintf_s(msgKey,
		L"FPS=%ld, GameTimer=%10.4f SPF=%d\n",
		m_dwFPS, m_fGameTimeTick,
		m_dwSecondPerFrame);
	m_csBuffer = msgKey;
}
