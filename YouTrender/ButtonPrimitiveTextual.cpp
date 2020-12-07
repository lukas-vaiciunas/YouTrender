#include "ButtonPrimitiveTextual.h"
#include "FontData.h"

ButtonPrimitiveTextual::ButtonPrimitiveTextual(float x, float y, float width, float height, const std::string &text, unsigned int textSize, const sf::Color &color, const sf::Color &textColor) :
	PrimitiveButton(x, y, width, height, color),
	Collideable(x, y, width, height),
	txt_(text, FontData::getInstance()->getMainFont(), textSize)
{
	txt_.setOrigin(std::floorf(txt_.getLocalBounds().width / 2.0f), std::floorf(textSize / 2.0f));
	txt_.setFillColor(textColor);
	txt_.setPosition(std::floorf(width / 2.0f), std::floorf(height / 2.0f));

	tex_.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
	tex_.clear(color);
	tex_.draw(txt_);
	tex_.display();

	sprite_.setTexture(tex_.getTexture(), true);
}

void ButtonPrimitiveTextual::setColor(const sf::Color &color)
{
	tex_.clear(color);
	tex_.draw(txt_);
	tex_.display();
}