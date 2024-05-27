
#include "CWindow.h"
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM
	lParam);
const wchar_t CLASS_NAME[] = L"Sample Window Class";

void CWindow::CreateRegisterClass(HINSTANCE hInstance)
{
	

	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc; // ���ּ�(�Ǵ� ��ȭ��ȣ) / �ݹ��Լ�
	wc.hInstance = hInstance;	// �ֹι�ȣ
	wc.lpszClassName = CLASS_NAME;	// �̸�
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
			// ���� ������ �����Ѵ�. 1������
			GameRun();
		}
	}
}

void CWindow::GameRun()
{

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM
	lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}