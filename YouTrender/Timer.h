#pragma once

#include <chrono>

class Timer
{
private:
	typedef std::chrono::system_clock SystemClock;
	typedef SystemClock::duration Duration;

	Duration startTime_;
	Duration endTime_;
public:
	Timer();

	void start();
	void stop();

	const std::chrono::milliseconds &getMilliseconds() const;
};