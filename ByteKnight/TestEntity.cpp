#include "TestEntity.h"

#include <RenderSubsystem.h>
#include <MovementSubsystem.h>
#include <InputSubsystem.h>

#include <GameWorld.h>

#include <iostream>
CTestEntity::CTestEntity(ui32 ui32EntityID, CGameWorld* pGameWorld) : CEntityBase(ui32EntityID, pGameWorld)
{
	m_pRenderComponent = AddComponent<C2DRenderComponent>();
	m_pMovementComponent = AddComponent<CMovementComponent>();
	m_pPositionComponent = AddComponent<CPositionComponent>();
	m_pInputComponent = AddComponent<CInputControllerComponent>();

	m_pInputComponent->CreateAxisBinding("MOVEMENT_LEFTRIGHT", this, &CTestEntity::InputAxis);

	pGameWorld->RegisterEntityToSubsystems<CRenderSubsystem, CMovementSubsystem, CInputSubsystem>(this);

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

void CTestEntity::InputAxis(CVector3 vecNormalizedInput)
{
	std::cout << "Swag\n";
}
