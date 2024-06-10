#include "TCore.h"
#include "TDxObject.h"

using namespace std;
class Sample : public TCore 
{
	TDxObject objScreen; // �ﰢ��
	vector<TDxObject> objList;
	TDxObject hero;
public:
	void Init() override
	{
		RECT rtBk = { 0, 0, g_xClientSize, g_yClientSize };
		objScreen.Create

		// ȭ����ǥ��
		// 0,0[0,0]			-		800,0[1,0]

		//	| 				X				|

		// 0,600[0,1]		-		800,600[1,1]

		objScreen.m_vList.resize(6);
		// �ð�������� ����Ǿ�� �Ѵ�.
		objScreen.m_vList[0].p = T_Math::FVector2(m_rtClient.left, m_rtClient.top);
		objScreen.m_vList[1].p = T_Math::FVector2(m_rtClient.right/2, m_rtClient.top);
		objScreen.m_vList[2].p = T_Math::FVector2(m_rtClient.right/2, m_rtClient.bottom/2);
		objScreen.m_vList[0].c = T_Math::FVector4(1, 0, 0, 1);
		objScreen.m_vList[1].c = T_Math::FVector4(0, 1, 0, 1);
		objScreen.m_vList[2].c = T_Math::FVector4(0, 0, 1, 1);
		objScreen.m_vList[0].t = T_Math::FVector2(0, 0);
		objScreen.m_vList[1].t = T_Math::FVector2(1, 0);
		objScreen.m_vList[2].t = T_Math::FVector2(1, 1);


		objScreen.m_vList[3].p = T_Math::FVector2(m_rtClient.right/2, m_rtClient.bottom/2);
		objScreen.m_vList[4].p = T_Math::FVector2(m_rtClient.left, m_rtClient.bottom/2);
		objScreen.m_vList[5].p = T_Math::FVector2(m_rtClient.left / 2, m_rtClient.top);
		objScreen.m_vList[3].c = T_Math::FVector4(1, 0, 0, 1);
		objScreen.m_vList[4].c = T_Math::FVector4(0, 1, 0, 1);
		objScreen.m_vList[5].c = T_Math::FVector4(0, 0, 1, 1);
		objScreen.m_vList[3].t = T_Math::FVector2(1, 1);
		objScreen.m_vList[4].t = T_Math::FVector2(0, 1);
		objScreen.m_vList[5].t = T_Math::FVector2(0, 0);

		// ȭ����ǥ�踦 NDC��ǥ �����Ѵ�
		for (auto& V : objScreen.m_vList)
		{
			// ȭ����ǥ��
			T_Math::FVector2 v = V.p;
			// 0 ~ 800 -> 0 ~ 1
			v.X = v.X / m_rtClient.right;
			v.Y = v.Y / m_rtClient.bottom;
			// NDC ��ǥ��
			// 0 ~ 1 -> -1 ~ +1
			V.p.X = v.X * 2.0f - 1.0f;
			V.p.Y = -(v.Y * 2.0f - 1.0f);

			int k = 0;
			// -1 ~ 1 -> 0 ~ +1
			/* v.X = v.X * 0.5f + 0.5f;
			v.Y = v.Y * 0.5f + 0.5f;*/
		}

		if (objScreen.CreateVertexBuffer(g_pd3dDevice) == false)
		{
			objScreen.Release();
			return;
		}
		if (objScreen.LoadShader(g_pd3dDevice) == false)
		{
			objScreen.Release();
			return;
		}
		if (objScreen.CreateInputLayout(g_pd3dDevice) == false)
		{
			objScreen.Release();
			return;
		}

		// ����ȭ�� ��ġ ��ǥ��(NDC) : (������ǥ�� ���)
		// *� ��ǥ�踦 ����ϴ��� �������
		// ���������δ� NDC ������ �Ǿ�� ȭ�鿡 �������ȴ�.
		
		// -1 ~ +1 ������ �����ϴ� ��ǥ��
		// -1, +1		-		+1,+1
		//		-0.5		+0.5
		//			  0,0
		//
		//
		// -1,-1		-		+1,-1
		/*
		objNDC.v[0] = T_Math::FVector2(-1.0f, +1.0f);
		objNDC.v[1] = T_Math::FVector2( 1.0f, +1.0f);
		objNDC.v[2] = T_Math::FVector2( 1.0f, -1.0f);
		objNDC.v[3] = T_Math::FVector2(-1.0f, -1.0f);*/
		/*T_Math::FVector2 v1(1,1);
		T_Math::FVector2 v2 = v1;
		T_Math::FVector2 v3 = v1 * 10.0f;
		T_Math::FVector2 v4;
		float fLength1 = v4.Length();
		bool  bNorm = v4.IsZero();
		float fLength2= v1.Length();
		float fLength3 = v3.Length();
		T_Math::FVector2 vNormalize = v1.Normalize();
		float fLength4 = vNormalize.Length();*/

		int k = 0;
	}
	void Render() override
	{
		// 0�� �������� �ؽ�ó ����
		g_pContext->PSSetShaderResources(0, 1, &m_pSRV);
		//Texture2D g_txTexture : register(t0);
		objScreen.Render(g_pContext);
	}
	void   Release() override
	{
		if (m_pSRV)
		{
			m_pSRV->Release();
			m_pSRV = nullptr;
		}
		if (m_pTexture)
		{
			m_pTexture->Release();
			m_pTexture = nullptr;
		}
		objScreen.Release();
	}
};

T_GAME_START(1024, 768);