#pragma once
#include "CStd.h"

using namespace std;
struct TVertex
{
	T_Math::FVector2 p; // 정점위치
	T_Math::FVector4 c; // 정점컬러
	T_Math::FVector2 t; // 정점텍스처좌표
	TVertex() = default;
	TVertex(T_Math::FVector2 p, T_Math::FVector4 c, T_Math::FVector2 t)
	{
		this->p = p;
		this->c = c;
		this->t = t;
	}
	TVertex(float x, float y, float r, float g, float b, float a, float u, float v)
	{
		this->p = { x,y };
		this->c = { r,g,b,a };
		this->t = { u,v };
	}
};

class TDxObject
{
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;

	// 렌더링 파이브라인(픽쉘쉐이더)에 전송 데이터
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV = nullptr;
	// 텍스처(이미지) 로드 데이터
	ComPtr<ID3D11Resource> m_pTexture = nullptr;
public:
	T_Math::FVector2 m_vPos;
	// 시스템 메모리에 할당된 버퍼
	vector<TVertex> m_vList;
	vector<TVertex> m_vListNDC;
	TDxObject& Move(float dx, float dy);
public:
	T_Math::FVector2 ConvertScreenToNDC(T_Math::FVector2 v);

	virtual bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, RECT rt, wstring texName);

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

