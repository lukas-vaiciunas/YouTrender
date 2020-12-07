#include "PrimitiveButton.h"

PrimitiveButton::PrimitiveButton(float x, float y, float width, float height, const sf::Color &color) :
	tex_(),
	Button(x, y, width, height, tex_.getTexture()),
	Collideable(x, y, width, height)
{
	tex_.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
	tex_.clear(color);
	tex_.display();

	sprite_.setTexture(tex_.getTexture(), true);
}

/*PrimitiveButton::PrimitiveButton(float x, float y, float width, float height, const std::string &text, unsigned int textSize, const sf::Color &color, const sf::Color &textColor) :
	tex_(),
	Button(x, y, width, height, tex_.getTexture())
{
	sf::Text txt(text, FontData::getInstance()->getMainFont(), textSize);
	txt.setOrigin(std::floorf(txt.getLocalBounds().width / 2.0f), std::floorf(textSize / 2.0f));
	txt.setFillColor(textColor);
	txt.setPosition(std::floorf(width / 2.0f), std::floorf(height / 2.0f));

	tex_.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
	tex_.clear(color);
	tex_.draw(txt);
	tex_.display();

	sprite_.setTexture(tex_.getTexture(), true);
}*/

void PrimitiveButton::setColor(const sf::Color &color)
{
	tex_.clear(color);
	tex_.display();
}