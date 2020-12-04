#include "EventQueue.h"

EventQueue *EventQueue::instance_ = nullptr;

EventQueue::~EventQueue()
{
	delete instance_;
	instance_ = nullptr;
}

EventQueue *EventQueue::getInstance()
{
	if (!instance_)
		instance_ = new EventQueue();

	return instance_;
}

void EventQueue::dispatch()
{
	if (!eventQ_.empty())
	{
		EventId ev = eventQ_.front();
		eventQ_.pop();

		for (Listener *listener : listeners_)
			if (listener->accepts(ev))
				listener->onEvent(ev);
	}
}

void EventQueue::send(EventId ev)
{
	eventQ_.push(ev);
}

void EventQueue::addListener(Listener *listener)
{
	listeners_.push_back(listener);
}