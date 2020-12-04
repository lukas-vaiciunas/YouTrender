#include "TickClock.h"
#include "Constants.h"

TickClock::TickClock(float secs) :
	ticks_(0),
	target_(static_cast<unsigned int>(secs * Global::FPS_CAP))
{}

bool TickClock::tick()
{
	if (++ticks_ > target_)
	{
		ticks_ = 0;
		return true;
	}

	return false;
}