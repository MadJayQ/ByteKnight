#pragma once
#include "GameSubsystem.h"
#include "EventSource.h"
#include "CollisionComponent.h"
#include "CollisionWorld.h"

class CCollisionSubsystem : public IGameSubsystem, public IEventSource
{
public:
	CCollisionSubsystem();
	~CCollisionSubsystem();

	void ApplyMovement(CEntityBase* ent, float flDeltaTime);

	virtual void Tick(float flDeltaTime) override;

	virtual void RegisterEntity(CEntityBase* ent) override;
	virtual void UnRegisterEntity(CEntityBase* ent) override;

private:
	std::unique_ptr<CCollisionWorld> m_pCollisionWorld;
};