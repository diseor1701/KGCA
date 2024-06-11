#include "CDevice.h"

bool  CDevice::CreateDevice(HWND hWnd)
{
	CONST D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC pSwapChainDesc;
	ZeroMemory(&pSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	pSwapChainDesc.BufferDesc.Width = 1024;
	pSwapChainDesc.BufferDesc.Height = 768;
	pSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	pSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	pSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	pSwapChainDesc.SampleDesc.Count = 1;
	pSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	pSwapChainDesc.BufferCount = 1;
	pSwapChainDesc.OutputWindow = hWnd;
	pSwapChainDesc.Windowed = true;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
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
	if (m_pSwapChain)m_pSwapChain->Release();
	if (m_pd3dDevice)m_pd3dDevice->Release();
	if (m_pContext)m_pContext->Release();
	if (m_pRTV)m_pRTV->Release();
}

void   CDevice::GameRun()
{
	float clearColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_pContext->ClearRenderTargetView(m_pRTV, clearColor);

	m_pSwapChain->Present(0, 0);
}