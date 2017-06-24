#include "InputSubsystem.h"
#include "InputEvent.h"

#include "MovementComponent.h"
#include "PositionComponent.h"

CInputSubsystem::CInputSubsystem()
{

}

CInputSubsystem::~CInputSubsystem()
{

}

void CInputSubsystem::Tick(float flDeltaTime)
{
	for (auto& ent : m_registeredEntities)
	{
		CPositionComponent* pPositionComponent = ent->GetComponent<CPositionComponent>();
		CMovementComponent* pMovementComponent = ent->GetComponent<CMovementComponent>();

		if (pPositionComponent && pMovementComponent)
		{

		}

	}
}

void CInputSubsystem::OnEventNotify(CEntityBase* ent, IEvent* e)
{
	if (dynamic_cast<CKeyInputEvent*>(e))
	{

	}
}
