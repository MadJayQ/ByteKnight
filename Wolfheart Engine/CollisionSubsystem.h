#pragma once
#include "GameSubsystem.h"
#include "EventSource.h"
#include "CollisionComponent.h"

class CCollisionSubsystem : public IGameSubsystem, public IEventSource
{
public:
	CCollisionSubsystem();
	~CCollisionSubsystem();

	virtual void RegisterEntity(CEntityBase* ent) override;
	virtual void UnRegisterEntity(CEntityBase* ent) override;
};