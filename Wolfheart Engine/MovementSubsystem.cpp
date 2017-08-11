#include "MovementSubsystem.h"
#include "CollisionSubsystem.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "InputControllerComponent.h"
#include "CollisionComponent.h"
#include "GameWorld.h"

CMovementSubsystem::CMovementSubsystem()
{

}

CMovementSubsystem::~CMovementSubsystem()
{

}

void CMovementSubsystem::Tick(float flDeltaTime)
{
	for (auto& ent : m_registeredEntities)
	{
		CPositionComponent* pPositionComponent = ent->GetComponent<CPositionComponent>();
		CMovementComponent* pMovementComponent = ent->GetComponent<CMovementComponent>();
		CInputControllerComponent* pInputComponent = ent->GetComponent<CInputControllerComponent>();

		if (!pPositionComponent || !pMovementComponent)
			continue;

		if (pInputComponent)
		{
			float flSpeedModifier = pMovementComponent->GetMaxSpeed();
			CVector3 vecInput = pInputComponent->ConsumeInputVector();
			pMovementComponent->SetVelocity(vecInput * flSpeedModifier);
		}

		v3 vecOldPosition = pPositionComponent->GetPositon();

		//This is the insertion point for our collision-system
		if (CCollisionComponent* pCollisionComponent = ent->GetComponent<CCollisionComponent>())
		{
			CCollisionSubsystem* pCollisionSubsystem = ent->GetGameWorld()->GetSubsystem<CCollisionSubsystem>();
			if (pCollisionSubsystem)
			{
				//Apply movement with collision
			}
		}
		else
		{
			pMovementComponent->ApplyMovement(
				pPositionComponent,
				flDeltaTime
				);
		}
		pPositionComponent->SetOldPosition(vecOldPosition);

	}
}
