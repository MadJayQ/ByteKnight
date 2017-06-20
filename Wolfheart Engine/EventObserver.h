#pragma once

#include "Event.h"
#include "Entity.h"

class IEventObserver
{
public:
	virtual ~IEventObserver() {}
	virtual void OnEventNotify(CEntityBase* ent, IEvent* e) = 0;
};