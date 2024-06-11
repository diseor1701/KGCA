#include "CWindow.h"
#include <d3d11.h> // DirectX 기능
//1번방법 : 속성->링커->입력->추가종속성->d3d11.lib 추가
//2번방법
#pragma comment ( lib, "d3d11.lib")

class CDevice : public CWindow
{
public:
	//인터페이스 획득(할당, 생성)
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRTV = nullptr;

	bool  CreateDevice(HWND hWnd);
	void  DeleteDevice();

	virtual void   GameRun() override;
};




int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow)
{
	CDevice win;
	win.CreateRegisterClass(hInstance);
	if (win.CreateWin(1024, 768))
	{
		// 그래픽 처리를 위한 초기화 작업
		if (win.CreateDevice(win.m_hWnd))
		{
			win.WindowRun();
		}
		// 그래픽 처리를 위한 소멸 작업
		win.DeleteDevice();
	}
	return 0;
}

bool  CDevice::CreateDevice(HWND hWnd)
{
	IDXGIAdapter* pAdapter = nullptr;
	D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;
	HMODULE Software = nullptr;
	UINT Flags = 0;
	CONST D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	UINT FeatureLevels = 1;
	UINT SDKVersion = D3D11_SDK_VERSION;

	DXGI_SWAP_CHAIN_DESC pSwapChainDesc;
	ZeroMemory(&pSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	pSwapChainDesc.BufferDesc.Width = 1024;
	pSwapChainDesc.BufferDesc.Height = 768;
	pSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	pSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	pSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	pSwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	pSwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	pSwapChainDesc.SampleDesc.Count = 1;
	pSwapChainDesc.SampleDesc.Quality = 0;
	pSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	pSwapChainDesc.BufferCount = 1;
	pSwapChainDesc.OutputWindow = hWnd;
	pSwapChainDesc.Windowed = true;
	pSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	pSwapChainDesc.Flags = 0;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		pAdapter,
		DriverType,
		Software,
		Flags,
		&pFeatureLevels,
		FeatureLevels,
		SDKVersion,
		&pSwapChainDesc,

		&m_pSwapChain,
		&m_pd3dDevice,
		nullptr,
		&m_pContext);

	if (FAILED(hr))
	{
		return false;
	}

	//ID3D11RenderTargetView* g_pRTV = nullptr;
	if (m_pd3dDevice != nullptr && m_pSwapChain != nullptr)
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

		ID3D11Resource* pResource = pBackBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC* pDesc = nullptr;
		hr = m_pd3dDevice->CreateRenderTargetView(
			pResource,
			pDesc,
			&m_pRTV);
		if (FAILED(hr))
		{
			return false;
		}

		pBackBuffer->Release();

	}

	if (m_pContext != nullptr)
	{
		m_pContext->OMSetRenderTargets(1, &m_pRTV, nullptr);
	}
	return true;
}
void  CDevice::DeleteDevice()
{
	m_pSwapChain->Release();
	m_pd3dDevice->Release();
	m_pContext->Release();
	m_pRTV->Release();
}

void   CDevice::GameRun()
{
	float clearColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_pContext->ClearRenderTargetView(m_pRTV, clearColor);

	m_pSwapChain->Present(0, 0);
}