#include "CWindow.h"
CWindow* g_pWindow = nullptr;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM
	lParam);
void   CWindow::CreateRegisterClass(HINSTANCE hInstance)
{
	// 1)������Ŭ������ ���ü�� ����ؾ� �Ѵ�.
	// ������ ����ü�� ü���� ����Ѵ�.
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;	// ���ּ�(�Ǵ� ��ȭ��ȣ)
	wc.hInstance = hInstance;		// �ֹι�ȣ
	wc.lpszClassName = L"SAMPLE_WINDOW";	// �̸�
	RegisterClass(&wc);

	m_hInstance = hInstance;
}
bool   CWindow::CreateWin(HINSTANCE hInstance, UINT xSize, UINT ySize)
{
	CreateRegisterClass(hInstance);
	// 2)��ϵ� ������Ŭ������ ����Ͽ� ������ �����Ѵ�.
	HWND hwnd = CreateWindowEx(
		0,
		L"SAMPLE_WINDOW",
		L"���� ������ ������Ʈ", // Window text
		WS_OVERLAPPEDWINDOW,	 // Window style
		// Size and position
		0, 0,   // position
		xSize, ySize,//Size
		NULL, // Parent window
		NULL, // Menu
		m_hInstance, // Instance handle
		NULL // Additional application data
	);
	if (hwnd == NULL)
	{
		return false;
	}
	m_hWnd = hwnd;
	ShowWindow(hwnd, SW_SHOW);
	return true;
}
bool   CWindow::WindowRun()
{
	// �޼���ť�� ����ִ� ��� �޼����� ���۾����� ���ν����� �����Ѵ�.
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
			return true;
		}
	}
	return false;
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
		// ���α׷��� Ȱ��ȭ(��Ŀ��)
	case WM_ACTIVATE:
	{
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			// ���ø����̼� ����
			if (g_pWindow != nullptr)
				g_pWindow->m_isActive = false;
		}
		else
		{
			// ���ø����̼� ����
			if (g_pWindow != nullptr)
				g_pWindow->m_isActive = true;
		}
	}return 0;
	case WM_DESTROY:
		PostQuitMessage(0);// WM_QUIT
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}