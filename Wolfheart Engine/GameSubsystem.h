#pragma once
#include "Entity.h"

#include <vector>
#include <memory>

class IGameSubsystem
{
public:
	virtual ~IGameSubsystem() {}
	virtual void Tick(float flDeltaTime) = 0;

protected:
	void RegisterEntity(CEntityBase* ent);
	void UnRegisterEntity(CEntityBase* ent);

	std::vector<CEntityBase*> m_registeredEntities;
};


class CGameSubsystemManager
{

}; 

CGameSubsystemManager* GetSubsystemManager();
