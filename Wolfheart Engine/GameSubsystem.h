#pragma once
#include "Entity.h"

#include <vector>
class IGameSubsystem
{
public:
	virtual ~IGameSubsystem() {}
	virtual void Tick(float flDeltaTime) = 0;

protected:
	void RegisterEntity(Entity* ent);
	void UnRegisterEntity(Entity* ent);

	std::vector<Entity*> m_registeredEntities;
};
