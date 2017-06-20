#include "GameWorld.h"


#include <algorithm>

CGameWorld::CGameWorld()
{

}

CGameWorld::~CGameWorld()
{

}

void CGameWorld::Tick(float flDeltaTime)
{
	for (auto& entry : m_gameSystems)
	{
		entry.second->Tick(flDeltaTime);
	}
}

void CGameWorld::DestroyEntity(CEntityBase* ent)
{
	auto entry = std::remove(
		m_pEntities.begin(),
		m_pEntities.end(),
		ent
	);

	if (entry != m_pEntities.end())
	{
		m_freeIDs.emplace(ent->GetEntityID());
		m_pEntities.erase(entry);
		delete ent; ent = NULL;
	}
}

void CGameWorld::OnEventNotify(CEntityBase* ent, IEvent* e)
{

}

ui32 CGameWorld::GenerateNextAvailableEID()
{
	ui32 ui32NewID = 0UL;
	if (!m_freeIDs.empty())
	{
		ui32NewID = m_freeIDs.front();
		m_freeIDs.pop();
		return ui32NewID;
	}

	ui32NewID = m_ui32NextEntityID;
	m_ui32NextEntityID++;

	return ui32NewID;
}
