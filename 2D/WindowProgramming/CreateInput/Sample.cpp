#include "CDevice.h"
#include "CTimer.h"
#include "CInput.h"


class Sample : public CDevice
{
public:
	CInput m_Input;
	CTimer m_Timer;
public:
	virtual void GameRun() override
	{
		m_Timer.Frame();
		m_Timer.DebugTimer();

		if (m_isActive)
		{
			m_Input.Frame(m_hWnd);
			m_Input.DebugMousePos();
			m_Input.KeyTest();
		}
		else
		{
			Sleep(10);
		}

		CDevice::GameRun();
	}
};

int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow)
{

	Sample win;
	win.CreateRegisterClass(hInstance);
	if (win.CreateWin(1024, 768))
	{
		// 그래픽 처리를 위한 초기화 작업
		if (win.CreateDevice(win.m_hWnd))
		{
			// 블럭상태
			win.WindowRun();
		}
		// 그래픽 처리를 위한 소멸 작업
		win.DeleteDevice();
	}
	return 0;
}
