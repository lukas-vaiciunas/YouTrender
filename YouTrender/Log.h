#pragma once

#include <deque>
#include <string>
#include "Visual.h"

class Log : public Visual
{
private:
	static constexpr unsigned int FONT_SIZE_ = 12U;

	static Log *instance_;

	std::deque<std::string> data_;

	Log();
	~Log();

	void updateVis();
public:
	Log(const Log &) = delete;
	Log &operator=(const Log &) = delete;

	static Log *getInstance();

	void push(const std::string &text);
};