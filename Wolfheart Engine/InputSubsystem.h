#pragma once

#include "GameSubsystem.h"
#include "EventObserver.h"

class CInputSubsystem : public IGameSubsystem, public IEventObserver
{
public:
	CInputSubsystem();
	~CInputSubsystem();

	virtual void Tick(float flDeltaTime) override;
	virtual void OnEventNotify(CEntityBase* ent, IEvent* e) override;

private:
	ui64 m_ui64MovementBitflags;
};