#include "TestDummy.h"

#include <RenderSubsystem.h>
#include <CollisionSubsystem.h>

#include <GameWorld.h>
CTestDummy::CTestDummy(ui32 ui32EntityID, CGameWorld * pGameWorld) : CEntityBase(ui32EntityID, pGameWorld)
{
	m_pRenderComponent = AddComponent<C2DRenderComponent>();
	m_pPositionComponent = AddComponent<CPositionComponent>();
	m_pCollisionComponent = AddComponent<CCollisionComponent>();

	pGameWorld->RegisterEntityToSubsystems<CRenderSubsystem, CCollisionSubsystem>(this);

	m_pRenderComponent->SetSprite(
		new CSprite(
			"Assets\\GameAssets\\Development\\test_background.png",
			SPRITE_FILE_TYPE::SPRITE_FILE_TYPE_PNG
		)
	);

	m_bInterpolate = false;
}

CTestDummy::~CTestDummy()
{
}
