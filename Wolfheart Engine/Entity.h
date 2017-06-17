#pragma once

#include "EngineMath.h"


#include <unordered_map>
#include <typeinfo>
#include <memory>


class Entity
{
public:
	Entity(ui32 ui32EntityID);
	~Entity();


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

private:
	ui32 m_ui32EntityID;
	std::unordered_map<const std::type_info*, std::unique_ptr<void*>> m_components;

};
