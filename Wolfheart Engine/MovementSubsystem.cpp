#include "MovementSubsystem.h"

#include "PositionComponent.h"
#include "MovementComponent.h"
#include "InputControllerComponent.h"

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
		pMovementComponent->ApplyMovement(
			pPositionComponent, 
			flDeltaTime
		);

		pPositionComponent->SetOldPosition(vecOldPosition);

	}
}
