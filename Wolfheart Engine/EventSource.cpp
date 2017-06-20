#include "EventSource.h"

#include <algorithm>
#include <cassert>

void IEventSource::RegisterObserver(IEventObserver* observer)
{
	auto entry = std::find(
		m_observers.begin(),
		m_observers.end(),
		observer
	);

	assert(entry == m_observers.end());
	m_observers.push_back(observer);
}

void IEventSource::UnRegisterObserver(IEventObserver*& observer, bool bDelete)
{
	auto entry = std::remove(
		m_observers.begin(),
		m_observers.end(),
		observer
	);
	if (entry != m_observers.end())
	{
		m_observers.erase(entry);
	}
	if (bDelete) { delete observer; observer = NULL; }
}

void IEventSource::EventNotify(CEntityBase* ent, IEvent* e)
{
	for (auto& observer : m_observers)
	{
		observer->OnEventNotify(ent, e);
	}
	//After all of our observers are done being notified of the event, free up the memory that the event held
	delete e;
	e = NULL;
}
