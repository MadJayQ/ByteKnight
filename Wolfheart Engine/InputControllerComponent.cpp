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
		v3 vecInputAxis = v3(1.f, 0.f, 0.f);
		auto pBindingFunc = m_axisMap["MOVEMENT_LEFTRIGHT"];
		if (pBindingFunc)
		{
			pBindingFunc(vecInputAxis);
		}
	}
}
