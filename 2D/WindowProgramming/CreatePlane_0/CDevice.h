#include "CWindow.h"
#include <d3d11.h> // DirectX 기능

#pragma comment ( lib, "d3d11.lib")

class CDevice : public CWindow
{
public:
	// 인터페이스 획득(할당, 생성)
	// 할당, 생성
	ID3D11Device* g_pd3dDevice = nullptr;
	// 관리, 운영
	ID3D11DeviceContext* g_pContext = nullptr;

	IDXGISwapChain* g_pSwapChain = nullptr;
	ID3D11RenderTargetView* g_pRTV = nullptr;

	D3D11_VIEWPORT	m_ViewPort;
public:
	bool  CreateDevice(HWND hWnd);
	void  DeleteDevice();

	void  SetViewport();
};