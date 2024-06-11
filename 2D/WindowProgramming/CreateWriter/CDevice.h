#include "CWindow.h"
#include <d3d11.h>

#pragma comment ( lib, "d3d11.lib")

class CDevice : public CWindow
{
public:
	//인터페이스 획득(할당, 생성)
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRTV = nullptr;

public:
	bool  CreateDevice(HWND hWnd);
	void  DeleteDevice();
};