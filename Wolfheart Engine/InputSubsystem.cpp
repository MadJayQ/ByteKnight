#include "InputSubsystem.h"
#include "MovementComponent.h"
#include "PositionComponent.h"
#include "InputControllerComponent.h"

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
		CInputControllerComponent* pInputControllerComponent = ent->GetComponent<CInputControllerComponent>();

		if (pInputControllerComponent)
		{
			while (!m_aggregatedInput.empty())
			{
				auto pInputEvent = m_aggregatedInput.back();
				pInputControllerComponent->ProcessInput(&pInputEvent);
				m_aggregatedInput.pop();
			}
		}

	}
}

void CInputSubsystem::OnEventNotify(CEntityBase* ent, IEvent* e)
{
	if (CKeyInputEvent* pEvent = dynamic_cast<CKeyInputEvent*>(e))
	{
		m_aggregatedInput.emplace(*pEvent);
	}
}
