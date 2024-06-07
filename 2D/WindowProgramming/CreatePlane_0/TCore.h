#pragma once
#include "CDevice.h"
#include "CTimer.h"
#include "CInput.h"
#include "CWriterFont.h"

class TCore : public CDevice, CBaseCore
{
public:
	CInput m_Input;
	CTimer m_Timer;
	CWriterFont  m_font;
public:
	virtual void Init();
	virtual void Frame();
	virtual void Render();
	virtual void Release();

	void   GameRun();
	
private:
	void GamePreFrame();
	void GameFrame();
	void GamePostFrame();

	void GamePreRender();	
	void GameRender();
	void GamePostRender();

	void DebugRender();

	void   GameInit();
	void   GameRelease();
};
