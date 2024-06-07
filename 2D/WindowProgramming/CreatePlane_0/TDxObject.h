#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

#include "T_Math.h"
#include <vector>
#pragma comment ( lib, "d3dcompiler.lib")

using namespace std;
struct TVertex
{
	T_Math::FVector2 v;
};

class TDxObject
{
public:
	// 시스템 메모리에 할당된 버퍼
	vector<TVertex> m_vList;
	TDxObject& Move(float dx, float dy);
public:
	// GPU 메모리에 할당된 버퍼
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	bool	CreateVertexBuffer(ID3D11Device* pd3dDevice);

	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3DBlob* VS_ByteCode = nullptr; // 오프젝트 파일
	ID3DBlob* PS_ByteCode = nullptr; // 오프젝트 파일
	bool	LoadShader(ID3D11Device* pd3dDevice);

	ID3D11InputLayout* m_pVertexLayout = nullptr;
	bool CreateInputLayout(ID3D11Device* pd3dDevice);

	void Render(ID3D11DeviceContext* pContext);
	void Release();
};

