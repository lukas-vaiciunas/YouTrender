#pragma once

#include <string>
#include "Collideable.h"

class Tooltipped : virtual public Collideable
{
private:
	std::string tip_;
	unsigned int uId_;
public:
	Tooltipped(float x, float y, float width, float height, const std::string &tip);
	~Tooltipped();

	const std::string &getTip() const;
	bool isHovered() const;
	unsigned int getUId() const;
};