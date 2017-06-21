#include "TestEntity.h"

#include <RenderSubsystem.h>
#include <MovementSubsystem.h>

CTestEntity::CTestEntity(ui32 ui32EntityID, CGameWorld* pGameWorld) : CEntityBase(ui32EntityID, pGameWorld)
{
	m_pRenderComponent = AddComponent<C2DRenderComponent>();
	m_pMovementComponent = AddComponent<CMovementComponent>();
	m_pPositionComponent = AddComponent<CPositionComponent>();

	CRenderSubsystem* pRenderSubsystem = pGameWorld->GetSubsystem<CRenderSubsystem>();
	CMovementSubsystem* pMovementSubsystem = pGameWorld->GetSubsystem<CMovementSubsystem>();
	if (pRenderSubsystem && pMovementSubsystem)
	{
		pRenderSubsystem->RegisterEntity(this);
		pMovementSubsystem->RegisterEntity(this);
	}
}

CTestEntity::~CTestEntity()
{

}
