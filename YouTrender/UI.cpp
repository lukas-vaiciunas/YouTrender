#include "UI.h"
#include "UIPool.h"
#include <iostream>

UI::UI() :
	uID_(UIPool::getNewUID()),
	isClosed_(false),
	isMinimized_(false)
{
	//UIPool::add(this);
}

UI::~UI()
{
	//UIPool::remove(uID_);
	std::cout << "UI Destructor Called!" << std::endl;
}

void UI::maximize()
{
	isMinimized_ = false;
}

unsigned int UI::getUID() const
{
	return uID_;
}

bool UI::isClosed() const
{
	return isClosed_;
}

bool UI::isMinimized() const
{
	return isMinimized_;
}