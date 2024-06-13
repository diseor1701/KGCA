#pragma once
#include "TDxObject.h"
#include "TCollision.h"

using namespace T_Math;
// ������ ����� ���� ������Ʈ
class TActor : public TDxObject
{
public:
	bool	m_bDead = false;
	RECT	m_rt;
	T_Math::FVector2	m_vPos;
public:
	float	m_fSpeed = 300.0f; // �ӷ�
	FVector2	m_vDirection = { 1.0f, 0.0f };
	FVector2	m_vOffset;
	FVector2	m_vVelocity;	// �ӵ�
public:
	virtual void SetVertexData(RECT rt) override;
	TActor& move(float dx, float dy);
};

