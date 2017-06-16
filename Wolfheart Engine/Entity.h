#pragma once

#include "ObjectMetadata.h"
#include "EngineMath.h"

class Entity
{
public:
	Entity(ui32 ui32EntityID);
	~Entity();

	template<typename T>
	T* AddComponent()
	{

	}

	template<typename T>
	bool HasComponent()
	{

	}

	template<typename T>
	T* GetComponent()
	{

	}

	ui32 GetEntityID() const { return m_ui32EntityID; }
	virtual ObjectMetadata GetEntityMetadata() = 0;

private:
	ui32 m_ui32EntityID;
};
