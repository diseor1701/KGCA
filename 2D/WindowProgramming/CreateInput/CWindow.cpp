#include "CWindow.h"
CWindow* g_pWindow = nullptr;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM
	lParam);
const wchar_t CLASS_NAME[] = L"Sample Window Class";

void CWindow::CreateRegisterClass(HINSTANCE hInstance)
{
	

	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc; // 집주소(또는 전화번호) / 콜백함수
	wc.hInstance = hInstance;	// 주민번호
	wc.lpszClassName = CLASS_NAME;	// 이름
	RegisterClass(&wc);

	m_hInstance = hInstance;
}

bool CWindow::CreateWin(UINT xSize, UINT ySize)
{
	HWND hwnd = CreateWindowEx(
		0, // Optional window styles
		CLASS_NAME, // window class
		L"Learn to program Windows", // Window Text
		WS_OVERLAPPEDWINDOW,	// Window style
		0, 0, // position
		xSize, ySize, // Size
		NULL, // Parent window
		NULL, // Menu
		m_hInstance, // Instance handle
		NULL // Additional application data
	);

	if (hwnd == NULL) {
		return false;
	}
	m_hWnd = hwnd;
	ShowWindow(hwnd, SW_SHOW);
	return true;

}

void CWindow::WindowRun()
{
	// 메세지큐에 담겨있는 모든 메세지를 수작업으로 프로시져에 전달한다.
	MSG msg = { };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 게임 로직을 가동한다. 1프레임
			GameRun();
		}
	}
}

void CWindow::GameRun()
{

}
CWindow::CWindow() 
{
	g_pWindow = this;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM
	lParam)
{
	switch (uMsg)
	{
		// 프로그램의 활성화(포커스)
	case WM_ACTIVATE:
	{
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			// 어플리케이션 비선택
			if (g_pWindow != nullptr)
				g_pWindow->m_isActive = false;
		}
		else
		{
			// 어플리케이션 선택
			if (g_pWindow != nullptr)
				g_pWindow->m_isActive = true;
		}
	}return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}