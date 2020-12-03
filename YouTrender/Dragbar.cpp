#include "Dragbar.h"
#include "Mouse.h"

Dragbar::Dragbar(const sf::FloatRect &aabb) :
	Collideable(aabb),
	visual_(),
	isDragging_(false),
	offsetX_(0.0f),
	offsetY_(0.0f)
{
	visual_.setPosition(aabb_.left, aabb_.top);
	visual_.setSize(sf::Vector2f(aabb_.width, aabb_.height));
	visual_.setFillColor(sf::Color(255, 255, 255, 255));
}

Dragbar::Dragbar(float x, float y, float width, float height) :
	Collideable(x, y, width, height),
	visual_(),
	isDragging_(false),
	offsetX_(0.0f),
	offsetY_(0.0f)
{
	visual_.setPosition(x, y);
	visual_.setSize(sf::Vector2f(width, height));
	visual_.setFillColor(sf::Color(255, 255, 255, 255));
}

bool Dragbar::updateOnMousePress()
{
	Mouse *mouse = Mouse::getInstance();

	if (mouse->interactable() &&
		mouse->isPressed(Mouse::BUTTON::LEFT) &&
		Collideable::isColliding(mouse->getPosition()))
	{
		mouse->lockInteraction();

		isDragging_ = true;
		offsetX_ = mouse->getX() - aabb_.left;
		offsetY_ = mouse->getY() - aabb_.top;

		return true;
	}

	return false;
}

void Dragbar::updateOnMouseRelease()
{
	Mouse *mouse = Mouse::getInstance();

	if (isDragging_ && !mouse->isPressed(Mouse::BUTTON::LEFT))
	{
		mouse->unlockInteraction();

		isDragging_ = false;
		offsetX_ = 0.0f;
		offsetY_ = 0.0f;
	}
}

void Dragbar::updateOnMouseAxes()
{
	Mouse *mouse = Mouse::getInstance();

	if (isDragging_)
		this->setPosition(mouse->getX() - offsetX_, mouse->getY() - offsetY_);
}

void Dragbar::render(sf::RenderWindow &window) const
{
	window.draw(visual_);
}

void Dragbar::setPosition(float x, float y)
{
	Collideable::setPosition(x, y);
	visual_.setPosition(x, y);
}

void Dragbar::setSize(float width, float height)
{
	Collideable::setSize(width, height);
	visual_.setSize(sf::Vector2f(width, height));
}

bool Dragbar::isDragging() const
{
	return isDragging_;
}