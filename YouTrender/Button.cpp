#include "Button.h"
#include "Mouse.h"

/*Button::Button(const sf::FloatRect &aabb, const sf::Texture &tex) :
	Collideable(aabb),
	sprite_(tex)
{
	sprite_.setPosition(aabb.left, aabb.top);
}*/

Button::Button(float x, float y, float width, float height, const sf::Texture &tex) :
	Collideable(x, y, width, height),
	sprite_(tex)
{
	float scaleX = width / tex.getSize().x;
	float scaleY = height / tex.getSize().y;

	sprite_.setPosition(x, y);
	sprite_.setScale(scaleX, scaleY);
}

void Button::render(sf::RenderWindow &window) const
{
	window.draw(sprite_);
}

bool Button::isClicked() const
{
	Mouse *mouse = Mouse::getInstance();

	if(mouse->interactable() &&
		mouse->isPressed(Mouse::BUTTON::LEFT) &&
		Collideable::isColliding(mouse->getPosition()))
	{
		mouse->release(Mouse::BUTTON::LEFT);
		return true;
	}

	return false;
}

void Button::setPosition(float x, float y)
{
	Collideable::setPosition(x, y);
	sprite_.setPosition(x, y);
}