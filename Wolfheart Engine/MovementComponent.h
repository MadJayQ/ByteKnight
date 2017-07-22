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

	bool Accelerates() const { return m_bAccelerates; }

	void SetMaxSpeed(float flMaxSpeed) { m_flMaxSpeed = flMaxSpeed; }
	float GetMaxSpeed() const { return m_flMaxSpeed; }

	float GetCurrentSpeed() const { return m_flSpeed; }

	CVector3 GetVelocity() const { return m_vecVelocity; }
	CVector3 GetAcceleration() const { return m_vecAcceleration; }

private:
	float m_flSpeed;
	float m_flMaxSpeed;

	CVector3 m_vecVelocity;
	CVector3 m_vecAcceleration;

	bool m_bAccelerates;
};
