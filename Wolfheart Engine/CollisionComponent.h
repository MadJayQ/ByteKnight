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

	void SetCollisionRect(Rect collisionRect) { m_collisionRect = collisionRect; }
	void SetCollisionRect(int x, int y, int w, int h) { m_collisionRect = Rect{ x, y, w, h }; }

	Rect GetCollisionRect() const { return m_collisionRect; }

	virtual void OnCollision(CEntityBase* self, CEntityBase* other) = 0;

private:
	ECollisionType m_collisionType;
	Rect m_collisionRect;
};