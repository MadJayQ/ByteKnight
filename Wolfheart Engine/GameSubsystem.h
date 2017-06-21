#pragma once
#include "Entity.h"

#include <vector>
#include <memory>

class IGameSubsystem
{
public:
	virtual ~IGameSubsystem() {}
	virtual void Tick(float flDeltaTime) = 0;

	void RegisterEntity(CEntityBase* ent);
	void UnRegisterEntity(CEntityBase* ent);

protected:
	std::vector<CEntityBase*> m_registeredEntities;
};
