#pragma once

#include "Entity.h"
#include "EventObserver.h"
#include "EventSource.h"
#include "Rectangle.h"

class CCollisionWorld : public IEventObserver, public IEventSource
{
public:
	CCollisionWorld();
	~CCollisionWorld();

	CRectangle GetBoundingRectangle() const { return m_boundingRectangle; }
	void SetBoundingRectangle(CRectangle boundingRectangle) { m_boundingRectangle = boundingRectangle; }
	
	void ApplyMovementWithCollision(CEntityBase* ent, float flDeltaTime);
	virtual void OnEventNotify(CEntityBase* ent, IEvent* e) override; //Do I need this?

private:
	void AdjustPositionToMapBounds(CVector3& vec, CRectangle boundingRect);
private:
	CRectangle m_boundingRectangle;
};
