#pragma once
#include "Cstd.h"

class CWindow
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	bool		m_isActive;

public:
	void CreateRegisterClass(HINSTANCE hInstance);
	bool CreateWin(HINSTANCE hInstance, UINT xSize, UINT ySize);
	bool WindowRun();
	CWindow();
};

