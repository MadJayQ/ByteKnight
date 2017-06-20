#pragma once
#include "EventObserver.h"

#include <vector>

class IEventSource
{
public:
	void RegisterObserver(IEventObserver* observer);
	void UnRegisterObserver(IEventObserver*& observer, bool bDelete = false);

protected:
	void EventNotify(CEntityBase* ent, IEvent* e);

private:
	std::vector<IEventObserver*> m_observers;
};