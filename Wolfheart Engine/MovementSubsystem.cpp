#include "MovementSubsystem.h"

#include "PositionComponent.h"
#include "MovementComponent.h"

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

		if (!pPositionComponent || !pMovementComponent)
			continue;

		v3 vecOldPosition = pPositionComponent->GetPositon();
		pMovementComponent->ApplyMovement(
			pPositionComponent, 
			flDeltaTime
		);

		pPositionComponent->SetOldPosition(vecOldPosition);

	}
}
