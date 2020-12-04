#include "Listener.h"
#include "EventQueue.h"

Listener::Listener(const EventIdSet &acceptedEvents) :
	acceptedEvents_(acceptedEvents)
{
	EventQueue::getInstance()->addListener(this);
}

bool Listener::accepts(EventId ev) const
{
	return acceptedEvents_.find(ev) != acceptedEvents_.cend();
}