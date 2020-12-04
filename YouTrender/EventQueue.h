#pragma once

#include <queue>
#include "Listener.h"
#include "Event.h"

class EventQueue
{
private:
	typedef Event::EVENT EventId;

	static EventQueue *instance_;

	std::queue<EventId> eventQ_;
	std::vector<Listener *> listeners_;

	EventQueue() {}
	~EventQueue();
public:
	EventQueue(const EventQueue &) = delete;
	EventQueue &operator=(const EventQueue &) = delete;

	static EventQueue *getInstance();

	void dispatch();

	void send(EventId ev);

	void addListener(Listener *listener);
};