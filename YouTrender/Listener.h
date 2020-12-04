#pragma once

#include <unordered_set>
#include "Event.h"

class Listener
{
private:
	typedef Event::EVENT EventId;
	typedef std::unordered_set<EventId> EventIdSet;

	EventIdSet acceptedEvents_;
public:
	Listener(const EventIdSet &acceptedEvents);

	virtual void onEvent(EventId ev) = 0;

	bool accepts(EventId ev) const;
};