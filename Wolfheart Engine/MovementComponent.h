#pragma once

#include "EntityComponent.h"
#include "Vector3.h"
#include "PositionComponent.h"

#include "EngineMath.h"

class CMovementComponent : public IEntityComponent
{
public:
	CMovementComponent();
	~CMovementComponent();

	void ApplyMovement(CPositionComponent* pPositionComponent, float flDeltaTime, bool bAccelerates = false);
	void SetAcceleration(CVector3 vecAcceleration);
	void SetVelocity(CVector3 vecVelocity);
	void SetAccelerates(bool bAccelerates) { m_bAccelerates = bAccelerates; }

private:
	ui16 ui16LinearSpeed;

	CVector3 m_vecVelocity;
	CVector3 m_vecAcceleration;

	bool m_bAccelerates;
};
