#pragma once
#include "GameSubsystem.h"
#include "EventObserver.h"
#include "InputEvent.h"

#include <queue>

class CInputSubsystem : public IGameSubsystem, public IEventObserver
{
public:
	CInputSubsystem();
	~CInputSubsystem();

	virtual void Tick(float flDeltaTime) override;
	virtual void OnEventNotify(CEntityBase* ent, IEvent* e) override;

private:
	std::queue<CKeyInputEvent*> m_aggregatedInput;
};