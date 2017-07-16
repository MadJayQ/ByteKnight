#include "InputSubsystem.h"
#include "MovementComponent.h"
#include "PositionComponent.h"
#include "InputControllerComponent.h"
#include "InputMapping.h"

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
			for (auto& key : m_pressedAxisKeys)
			{
				pInputControllerComponent->ProcessKeyInputAxis(key);
			}
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
		ui32 ui32KeyCode = pEvent->GetKeyNum();
		if (!CInputMapping::Instance()->HasInputAxis(ui32KeyCode))
		{
			m_aggregatedInput.emplace(*pEvent);
			return;
		}
		auto axisMapping = CInputMapping::Instance()->GetInputAxis(ui32KeyCode);
		if (ButtonState::Pressed(pEvent->GetKeyState()))
		{
			m_pressedAxisKeys.emplace(ui32KeyCode);
		}
		else
		{
			if (m_pressedAxisKeys.find(ui32KeyCode) != m_pressedAxisKeys.end())
			{
				m_pressedAxisKeys.erase(ui32KeyCode);
			}
		}

	}
}