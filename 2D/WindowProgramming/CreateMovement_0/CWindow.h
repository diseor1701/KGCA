#pragma once
#include "Cstd.h"

class CWindow
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	bool		m_isActive;

	RECT		m_rtWindow;
	RECT		m_rtClient;

public:
	void CreateRegisterClass(HINSTANCE hInstance);
	bool CreateWin(HINSTANCE hInstance, UINT xSize, UINT ySize);
	bool WindowRun();
	CWindow();
};

