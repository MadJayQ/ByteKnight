#pragma once

#include "Entity.h"
#include "QuadTree.h"
#include "EventObserver.h"

class CCollisionWorld : public IEventObserver
{
public:
	CCollisionWorld();
	~CCollisionWorld();

	virtual void OnEventNotify(CEntityBase* ent, IEvent* e) override;

private:
	CQuadTree<CEntityBase*> m_CollisionTree;
	AABB m_boundingBox;
};
