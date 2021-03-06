#pragma once
#include <Entity.h>
#include <2DRenderComponent.h>
#include <MovementComponent.h>
#include <PositionComponent.h>
#include <InputControllerComponent.h>
#include <CollisionComponent.h>

#include <EngineMath.h>

class CTestEntity : public CEntityBase
{
public:

	CTestEntity(ui32 ui32EntityID, CGameWorld* pGameWorld);
	~CTestEntity();

	void InputAxis(CVector3 vecInput);

private:
	C2DRenderComponent* m_pRenderComponent;
	CMovementComponent* m_pMovementComponent;
	CPositionComponent* m_pPositionComponent;
	CInputControllerComponent* m_pInputComponent;
	CCollisionComponent* m_pCollisionComponent;
};