#pragma once

#include "EngineMath.h"
#include "EntityComponent.h"
#include <unordered_map>
#include <typeinfo>
#include <memory>


class CGameWorld;

class CEntityBase
{
public:
	CEntityBase(ui32 ui32EntityID, CGameWorld* pGameWorld);
	~CEntityBase();


	template<typename T>
	T* AddComponent()
	{
		auto typeID = &typeid(T);
		m_components.insert(
			std::make_pair(
				typeID, 
				std::make_unique<T>()
			)
		);
		return static_cast<T*>(m_components[typeID].get());
	}

	template<typename T>
	bool HasComponent()
	{
		auto typeID = &typeid(T);
		return m_components.count(typeID) != 0;
	}

	template<typename T>
	T* GetComponent()
	{
		if (HasComponent<T>())
		{
			auto typeID = &typeid(T);
			return static_cast<T*>(m_components[typeID].get());
		}

		return NULL;
	}

	ui32 GetEntityID() const { return m_ui32EntityID; }
	bool ShouldInterpolate() const { return m_bInterpolate; }

	CGameWorld* GetGameWorld() const { return m_pGameWorld; }

protected:
	bool m_bInterpolate = false;
private:
	ui32 m_ui32EntityID;
	CGameWorld* m_pGameWorld;
	std::unordered_map<const std::type_info*, std::unique_ptr<IEntityComponent>> m_components;

};
