#pragma once

#include "EngineMath.h"
#include "Entity.h"
#include "GameSubsystem.h"
#include "PositionComponent.h"
#include "EventObserver.h"
#include "EventSource.h"

#include <vector>
#include <queue>

class CGameWorld : public IEventObserver, public IEventSource
{
public:
	CGameWorld();
	~CGameWorld();

	void Tick(float flDeltaTime);

	template<class Entity>
	Entity* SpawnEntity(CVector3 vecSpawnPos)
	{
		Entity* ent = new Entity(
			GenerateNextAvailableEID(),
			this
		);
		CPositionComponent* pPositionComponent = ent->GetComponent<CPositionComponent>();
		if (!pPositionComponent) pPositionComponent = ent->AddComponent<CPositionComponent>();
		pPositionComponent->SetPosition(vecSpawnPos);
		pPositionComponent->SetOldPosition(vecSpawnPos);
		m_pEntities.push_back(ent);
		return ent;
	}

	template<class Entity>
	Entity* SpawnEntity()
	{
		Entity* ent = new Entity(
			GenerateNextAvailableEID(),
			this
		);
		m_pEntities.push_back(ent);
		return ent;
	}

	template<class Subsystem>
	Subsystem* CreateSubsystem()
	{
		auto typeID = &typeid(Subsystem);
		m_gameSystems.insert(
			std::make_pair(
				typeID, 
				std::make_unique<Subsystem>()
			)
		);

		return static_cast<Subsystem*>(m_gameSystems[typeID].get());
	}

	template<class Subsystem>
	Subsystem* GetSubsystem()
	{
		auto typeID = &typeid(Subsystem);
		if (m_gameSystems.count(typeID) != 0)
		{
			return static_cast<Subsystem*>(m_gameSystems[typeID].get());
		}

		return NULL;
	}

	template<typename... Subsystems>
	void RegisterEntityToSubsystems(CEntityBase* ent)
	{
		RegisterEntToSubsystem_Helper<Subsystems...>::exec(this, ent);
	}

	void DestroyEntity(CEntityBase* ent);

	virtual void OnEventNotify(CEntityBase* ent, IEvent* e) override;

private:
		template<typename T, typename... Targs>
		struct RegisterEntToSubsystem_Helper;

		template<typename T>
		struct RegisterEntToSubsystem_Helper<T>
		{
			static void exec(CGameWorld* pThis, CEntityBase* ent)
			{
				auto pSubsystem = pThis->GetSubsystem<T>();
				if (!pSubsystem) pThis->CreateSubsystem<T>();
				pSubsystem->RegisterEntity(ent);
			}
		};
		template<typename T, typename... Targs>
		struct RegisterEntToSubsystem_Helper
		{
			static void exec(CGameWorld* pThis, CEntityBase* ent)
			{
				RegisterEntToSubsystem_Helper<T>::exec(pThis, ent);
				RegisterEntToSubsystem_Helper<Targs...>::exec(pThis, ent);
			}
		};

	ui32 GenerateNextAvailableEID();

	std::unordered_map<const std::type_info*, std::unique_ptr<IGameSubsystem>> m_gameSystems;
	std::vector<CEntityBase*> m_pEntities;
	std::queue<ui32> m_freeIDs;
	ui32 m_ui32NextEntityID = 0UL;
};
