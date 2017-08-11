#pragma once

#include "EntityComponent.h"
#include "EngineMath.h"

class CEntityBase;

enum ECollisionType
{
	COLLISION_TYPE_SOLID,
	COLLISION_TYPE_TRIGGER,
	COLLISION_TYPE_PICKUP,
	COLLISION_TYPE_ENTITY
};

class CCollisionComponent : public IEntityComponent
{
public:
	CCollisionComponent();
	~CCollisionComponent();

	void SetCollisionType(ECollisionType type) { m_collisionType = type; }
	ECollisionType GetCollisionType() const{ return m_collisionType; }


	virtual void OnCollision(CEntityBase* self, CEntityBase* other) {}

private:
	ECollisionType m_collisionType;
};