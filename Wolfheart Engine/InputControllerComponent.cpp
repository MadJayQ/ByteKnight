#include "InputControllerComponent.h"
#include "InputEvent.h"

CInputControllerComponent::CInputControllerComponent()
{

}

CInputControllerComponent::~CInputControllerComponent()
{

}

void CInputControllerComponent::ProcessInput(CKeyInputEvent* pInputEvent)
{
	if (pInputEvent->GetKeyNum() == 0x44)
	{
		float flXModifier = (pInputEvent->GetKeyState() == ButtonState::KeyState_Pressed || pInputEvent->GetKeyState() == ButtonState::KeyState_Held) ? 1.f : 0.f;
		v3 vecInputAxis = v3(flXModifier, 0.f, 0.f);
		auto pBindingFunc = m_axisMap["MOVEMENT_LEFTRIGHT"];
		if (pBindingFunc)
		{
			pBindingFunc(vecInputAxis);
		}
	}
}
