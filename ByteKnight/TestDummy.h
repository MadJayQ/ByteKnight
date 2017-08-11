#pragma once
#include <Entity.h>
#include <2DRenderComponent.h>
#include <PositionComponent.h>
#include <CollisionComponent.h>

class CTestDummy : public CEntityBase
{
public:

	CTestDummy(ui32 ui32EntityID, CGameWorld* pGameWorld);
	~CTestDummy();

private:
	C2DRenderComponent* m_pRenderComponent;
	CPositionComponent* m_pPositionComponent;
	CCollisionComponent* m_pCollisionComponent;
	
};