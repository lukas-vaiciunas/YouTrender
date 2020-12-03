#include "Mouse.h"
#include <iostream>

Mouse *Mouse::instance_ = nullptr;

Mouse::Mouse() :
	interactable_(true)
{
	this->releaseAll();
}

Mouse::~Mouse()
{
	delete instance_;
	instance_ = nullptr;
}

void Mouse::releaseAll()
{
	for (unsigned int i = 0; i < NUM_BUTTONS; i++)
		buttons_[i] = false;
}

Mouse *Mouse::getInstance()
{
	if (!instance_)
		instance_ = new Mouse();

	return instance_;
}

void Mouse::updatePresses(const sf::Event &ev)
{
	switch (ev.mouseButton.button)
	{
	case sf::Mouse::Button::Left:
		buttons_[LEFT] = true;
		break;
	case sf::Mouse::Button::Right:
		buttons_[RIGHT] = true;
		break;
	}
}

void Mouse::updateReleases(const sf::Event &ev)
{
	switch (ev.mouseButton.button)
	{
	case sf::Mouse::Button::Left:
		buttons_[LEFT] = false;
		break;
	case sf::Mouse::Button::Right:
		buttons_[RIGHT] = false;
		break;
	}
}

void Mouse::updateAxes(const sf::Window &relativeTo)
{
	x_ = sf::Mouse::getPosition(relativeTo).x;
	y_ = sf::Mouse::getPosition(relativeTo).y;
}

bool Mouse::isPressed(BUTTON button) const
{
	return buttons_[button];
}

void Mouse::release(BUTTON button)
{
	buttons_[button] = false;
}

void Mouse::lockInteraction()
{
	if (!interactable_)
		throw std::runtime_error("Mouse is already uninteractable!");

	interactable_ = false;
}

void Mouse::unlockInteraction()
{
	if (interactable_)
		throw std::runtime_error("Mouse is already interactable!");

	interactable_ = true;
}

int Mouse::getX() const
{
	return x_;
}

int Mouse::getY() const
{
	return y_;
}

sf::Vector2i Mouse::getPosition() const
{
	return sf::Vector2i(x_, y_);
}

bool Mouse::interactable() const
{
	return interactable_;
}