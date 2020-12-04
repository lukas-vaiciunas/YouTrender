#include "Overlay.h"
#include "Constants.h"
#include "FontData.h"

Overlay::Overlay(const std::string &txt, unsigned int txtSize, const sf::Color &txtColor, const sf::Color &backgroundColor) :
	tex_(),
	img_()
{
	unsigned int width = Global::SCREEN_WIDTH;
	unsigned int height = Global::SCREEN_HEIGHT;

	sf::Text txtOutput(txt, FontData::getInstance()->getMainFont(), txtSize);
	txtOutput.setOrigin(txtOutput.getLocalBounds().width / 2.0f, txtSize / 2.0f);
	txtOutput.setPosition(width / 2.0f, height / 2.0f);
	txtOutput.setFillColor(txtColor);

	tex_.create(width, height);
	tex_.clear(backgroundColor);
	tex_.draw(txtOutput);
	tex_.display();

	img_.setTexture(tex_.getTexture());
}

void Overlay::render(sf::RenderWindow &window) const
{
	window.draw(img_);
}