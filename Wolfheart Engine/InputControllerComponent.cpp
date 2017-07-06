#include "InputControllerComponent.h"
#include "InputEvent.h"
#include "InputMapping.h"

CInputControllerComponent::CInputControllerComponent()
{

}

CInputControllerComponent::~CInputControllerComponent()
{

}

bool KeystateDown(CKeyInputEvent* pEvent)
{
	return (pEvent->GetKeyState() == ButtonState::KeyState_Pressed 
		   || pEvent->GetKeyState() == ButtonState::KeyState_Held);
}

void CInputControllerComponent::ProcessInput(CKeyInputEvent* pInputEvent)
{
	/*
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
	*/
	ui32 ui32KeyCode = pInputEvent->GetKeyNum();
	auto pInputMapping = CInputMapping::Instance()->GetInputAxis(ui32KeyCode);
	if (pInputMapping == NULL) return;
	v3 vecInputAxis = pInputMapping->second * (KeystateDown(pInputEvent) ? 1.f : 0.f); //Hack??
	auto pBindingFunc = m_axisMap[pInputMapping->first];
	if (pBindingFunc)
	{
		pBindingFunc(vecInputAxis);
	}
}
