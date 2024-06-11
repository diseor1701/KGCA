#include "CWindow.h"
#include <d3d11.h> // DirectX ���

#pragma comment ( lib, "d3d11.lib")

class CDevice : public CWindow
{
public:
	// �������̽� ȹ��(�Ҵ�, ����)
	// �Ҵ�, ����
	ID3D11Device* m_pd3dDevice = nullptr;
	// ����, �
	ID3D11DeviceContext* m_pContext = nullptr;

	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRTV = nullptr;

	D3D11_VIEWPORT	m_ViewPort;
public:
	bool  CreateDevice(HWND hWnd);
	void  DeleteDevice();

	void  SetViewport();
};