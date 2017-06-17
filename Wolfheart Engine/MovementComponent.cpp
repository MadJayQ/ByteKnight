#include "MovementComponent.h"

CMovementComponent::CMovementComponent()
{
	m_bAccelerates = false;
	m_vecVelocity = CVector3(0.f, 0.f, 0.f);
}

CMovementComponent::~CMovementComponent()
{

}

void CMovementComponent::ApplyMovement(CPositionComponent* pPositionComponent, float flDeltaTime, bool bAccelerates)
{
	if (bAccelerates || m_bAccelerates)
	{
		m_vecVelocity += m_vecAcceleration;
	}

	CVector3& position = pPositionComponent->GetPositon();
	position._x += m_vecVelocity._x * flDeltaTime;
	position._y += m_vecVelocity._y * flDeltaTime;
	position._z = 0.f;
}

void CMovementComponent::SetAcceleration(CVector3 vecAcceleration)
{
	m_vecAcceleration = vecAcceleration;
}

void CMovementComponent::SetVelocity(CVector3 vecVelocity)
{
	m_vecVelocity = vecVelocity;
}
