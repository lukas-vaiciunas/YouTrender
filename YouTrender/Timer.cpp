#include "Timer.h"
#include "Constants.h"

Timer::Timer(float secs) :
	ticks_(0),
	target_(static_cast<unsigned int>(secs * Global::FPS_CAP))
{}

bool Timer::tick()
{
	if (++ticks_ > target_)
	{
		ticks_ = 0;
		return true;
	}

	return false;
}