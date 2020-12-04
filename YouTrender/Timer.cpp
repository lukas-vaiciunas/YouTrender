#include "Timer.h"

Timer::Timer() :
	startTime_(),
	endTime_()
{}

void Timer::start()
{
	startTime_ = SystemClock::now().time_since_epoch();
}

void Timer::stop()
{
	endTime_ = SystemClock::now().time_since_epoch();
}

const std::chrono::milliseconds &Timer::getMilliseconds() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime_) -
		std::chrono::duration_cast<std::chrono::milliseconds>(startTime_);
}