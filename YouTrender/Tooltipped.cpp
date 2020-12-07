#include "Tooltipped.h"
#include "Mouse.h"
#include "UIPool.h"
#include <iostream>

Tooltipped::Tooltipped(float x, float y, float width, float height, const std::string &tip) :
	Collideable(x, y, width, height),
	tip_(tip),
	uId_(UIPool::getNewUID())
{
	UIPool::addTooltipped(this);
}

Tooltipped::~Tooltipped()
{
	UIPool::removeTooltipped(uId_);
	std::cout << "Tooltipped destructor called!\n";
}

const std::string &Tooltipped::getTip() const
{
	return tip_;
}

bool Tooltipped::isHovered() const
{
	return Collideable::isColliding(Mouse::getInstance()->getPosition());
}

unsigned int Tooltipped::getUId() const
{
	return uId_;
}