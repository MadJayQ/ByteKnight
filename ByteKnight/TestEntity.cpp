#include "TestEntity.h"

#include <RenderSubsystem.h>
#include <MovementSubsystem.h>
#include <GameWorld.h>

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

	m_pRenderComponent->SetSprite(
		new CSprite(
			"Assets\\GameAssets\\Development\\test_background.png",
			SPRITE_FILE_TYPE::SPRITE_FILE_TYPE_PNG
		)
	);

	//We want to interpolate this entity
	m_bInterpolate = true; 
}

CTestEntity::~CTestEntity()
{

}
