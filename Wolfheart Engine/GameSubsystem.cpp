#include "GameSubsystem.h"


#include <algorithm>
#include <cassert>

void IGameSubsystem::RegisterEntity(CEntityBase * ent)
{
	auto entry = std::find(
		m_registeredEntities.begin(),
		m_registeredEntities.end(), 
		ent
	);

	assert(entry == m_registeredEntities.end());
	m_registeredEntities.push_back(ent);
}

void IGameSubsystem::UnRegisterEntity(CEntityBase* ent)
{
	auto entry = std::remove(
		m_registeredEntities.begin(),
		m_registeredEntities.end(),
		ent
	);

	if (entry != m_registeredEntities.end())
	{
		m_registeredEntities.erase(entry);
	}

}
