#pragma once

class TickClock
{
private:
	unsigned int ticks_;
	unsigned int target_;
public:
	TickClock(float secs);

	bool tick();
};