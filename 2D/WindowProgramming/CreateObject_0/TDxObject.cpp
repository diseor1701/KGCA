#include "TDxObject.h"
#include "CStd.h"

TDxObject& TDxObject::Move(float dx, float dy)
{
    for (auto& v : m_vList)
    {
        v.p += {dx, dy};
    }
    m_vPos = { dx,dy };

    for (int i = 0; i < m_vList.size(); i++)
    {
        m_vListNDC[i].p = ConvertScreenToNDC(m_vList[i].p);
    }
    m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_vListNDC.at(0), 0, 0);
    return *this;
}

T_Math::FVector2 TDxObject::ConvertScreenToNDC(T_Math::FVector2 v)
{

}

bool TDxObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, RECT rt, wstring texName)
{
    return false;
}

bool TDxObject::CreateVertexBuffer(ID3D11Device* pd3dDevice)
{
    // ���� �Ҵ� ũ�⸦ �����Ѵ�
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = sizeof(TVertex) * m_vList.size();
    // ���ῡ �뵵�� ����?
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;


    // �Ҵ�� ���ۿ�
    // �ý��� �޸𸮰� -> GPU�޸𸮷� ä������ ������
    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = &m_vList.at(0);

    HRESULT hr = pd3dDevice->CreateBuffer(
        &bd,
        &sd,
        &this->m_pVertexBuffer);

    if (FAILED(hr)) return false;
    return true;
}

bool TDxObject::LoadShader(ID3D11Device* pd3dDevice)
{
    // HLSL(High Level shader Language) ���(������ ���) : C���� ������.
    // HLSL���� �ۼ��ؼ� �������� �ϰ� ������Ʈ�� ����Ѵ�.

    HRESULT hr;
    
    ID3DBlob* errormsg = nullptr; // ������ �� ���� �޽���
    hr = D3DCompileFromFile(
        L"VS.txt",
        nullptr,
        nullptr,
        "VSMain",
        "vs_5_0", // dx11 �������̴� �����Ϸ�
        0,
        0,
        &VS_ByteCode,
        &errormsg
    );

    if(FAILED(hr)) return false;

    // ������Ʈ ������ �����ּ�
    const void* pShaderBytecode = VS_ByteCode->GetBufferPointer();
    // ������Ʈ ������ ũ��
    SIZE_T BytecodeLength = VS_ByteCode->GetBufferSize();

    hr = pd3dDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, nullptr, &m_pVertexShader);

    if (FAILED(hr))
    {
        return false;
    }
    if (errormsg) errormsg->Release();

    // �ȼ����̴� �ε� �� ����
    hr = D3DCompileFromFile(
        L"PS.txt",
        nullptr,
        nullptr,
        "PSMain",
        "ps_5_0", // dx11 �ȼ����̴� �����Ϸ�
        0,
        0,
        &PS_ByteCode,
        &errormsg
    );
    if (FAILED(hr))
    {
        MessageBoxA(NULL,
            (char*)errormsg->GetBufferPointer(),
            "ERROR", MB_OK);
        return false;
    }

    pShaderBytecode = PS_ByteCode->GetBufferPointer();
    BytecodeLength = PS_ByteCode->GetBufferSize();
    hr = pd3dDevice->CreatePixelShader(PS_ByteCode->GetBufferPointer(),
        PS_ByteCode->GetBufferSize(), nullptr, &m_pPixelShader);
    if (FAILED(hr)) return false;

    return true;
}

// GPU �� ó���ϴ� ����
// 1) ������ �������ۿ� �����Ͽ� 
    // pContext->IASetVertexBuffers(StartSlot, NumBuffers, &m_pVertexBuffer, &pStrides, &pOffsets);
// 2) 1���� ���� ������ �ε��Ѵ�.UINT pStrides = sizeof(TVertex); // 1���� ���� ũ��
// 3) ������ ��ǲ���̾ƿ��� ���� ���� ������ �������̴��� �����Ѵ�
// �������̴��� ���������� ȣ��ȴ�.
// |x, y, r,g,b,a|,|x, y, r,g,b,a| ,|x, y, r,g,b,a| ,|x, y, r,g,b,a| 
//   0~7  8~11
// |x, y, r,g,b,a, u,v|,|x, y, r,g,b,a, u,v| ,|x, y, r,g,b,a, u,v| ,|x, y, r,g,b,a, u,v| 
//   0~7  8~11   24~32

bool TDxObject::CreateInputLayout(ID3D11Device* pd3dDevice)
{
    const D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    UINT NumElements = sizeof(layout) / sizeof(layout[0]);
    HRESULT hr = pd3dDevice->CreateInputLayout(
        layout,
        NumElements,
        VS_ByteCode->GetBufferPointer(),
        VS_ByteCode->GetBufferSize(),
        &m_pVertexLayout);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

void TDxObject::Render(ID3D11DeviceContext* pContext)
{
    // ������� �ʴ� ������������ ����Ʈ �� �Ǵ� null���ȴ�

    UINT StartSlot = 0;
    UINT NumBuffers = 1;
    UINT pStrides = sizeof(TVertex); // 1���� ���� ũ��
    UINT pOffsets = 0; // ���ۿ� ���� �ε���
    pContext->IASetVertexBuffers(StartSlot, NumBuffers, &m_pVertexBuffer, &pStrides, &pOffsets);
    pContext->IASetInputLayout(m_pVertexLayout);
    pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    pContext->VSSetShader(m_pVertexShader, nullptr, 0);
    pContext->PSSetShader(m_pPixelShader, nullptr, 0);
    pContext->Draw(m_vList.size(), 0);
}

void TDxObject::Release()
{
    if (VS_ByteCode)
    {
        VS_ByteCode->Release();
        VS_ByteCode = nullptr;
    }
    if (PS_ByteCode)
    {
        PS_ByteCode->Release();
        PS_ByteCode = nullptr;
    }

    if (m_pVertexBuffer)
    {
        m_pVertexBuffer->Release();
        m_pVertexBuffer = nullptr;
    }
    if (m_pVertexShader)
    {
        m_pVertexShader->Release();
        m_pVertexShader = nullptr;
    }
    if (m_pPixelShader)
    {
        m_pPixelShader->Release();
        m_pPixelShader = nullptr;
    }
    if (m_pVertexLayout)
    {
        m_pVertexLayout->Release();
        m_pVertexLayout = nullptr;
    }
}

