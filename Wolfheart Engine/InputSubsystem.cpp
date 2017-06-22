#include "InputSubsystem.h"

#include "InputEvent.h"

CInputSubsystem::CInputSubsystem()
{

}

CInputSubsystem::~CInputSubsystem()
{

}

void CInputSubsystem::Tick(float flDeltaTime)
{

}

void CInputSubsystem::OnEventNotify(CEntityBase* ent, IEvent* e)
{
	if (dynamic_cast<CKeyInputEvent*>(e))
	{
		CKeyInputEvent* pKeyEvent = reinterpret_cast<CKeyInputEvent*>(e);

	}
}
