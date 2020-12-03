#pragma once

class Timer
{
private:
	unsigned int ticks_;
	unsigned int target_;
public:
	Timer(float secs);

	bool tick();
};