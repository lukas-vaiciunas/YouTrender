#include "Tooltip.h"
#include "FontData.h"
#include "Mouse.h"
#include "Constants.h"

Tooltip::Tooltip() :
	tex_(),
	img_()
{}

void Tooltip::synchronizePosition()
{
	const Mouse &mouse = *Mouse::getInstance();
	const sf::FloatRect &imgBounds = img_.getLocalBounds();

	float dX = 0.0f;
	float dY = mouse.getY() - imgBounds.height;
	float right = mouse.getX() + imgBounds.width;
	//float bottom = mouse.getY() + 16.0f + imgBounds.height;

	bool offScreenX = right > static_cast<float>(Global::SCREEN_WIDTH);
	//bool offScreenY = bottom > static_cast<float>(Global::SCREEN_HEIGHT);

	dX = (offScreenX ? mouse.getX() - imgBounds.width : mouse.getX());
	//dY = (offScreenY ? mouse.getY() - imgBounds.height : bottom);

	img_.setPosition(dX, dY);
}

void Tooltip::updateOnMouseAxes()
{
	this->synchronizePosition();
}

void Tooltip::render(sf::RenderWindow &window) const
{
	window.draw(img_);
}

void Tooltip::activate(const std::string &tip)
{
	constexpr unsigned int fontSize = 12U;

	const Mouse &mouse = *Mouse::getInstance();
	sf::RectangleShape outline;
	sf::Color backgroundColor(255, 255, 255, 255);
	sf::Color textColor(0, 0, 0, 255);
	float texWidth = 0.0f;
	float texHeight = 0.0f;
	float outlineThickness = 1.0f;
	float padding = 1.0f;
	float gap = padding + outlineThickness;
	
	sf::Text tipText(tip, FontData::getInstance()->getMainFont(), fontSize);
	tipText.setPosition(std::floorf(gap), std::floorf(gap));
	tipText.setFillColor(textColor);

	const sf::FloatRect &ttBounds = tipText.getLocalBounds();

	texWidth = gap * 2.0f + ttBounds.left + ttBounds.width;
	texHeight = gap * 2.0f + ttBounds.top + ttBounds.height;

	outline.setPosition(outlineThickness, outlineThickness);
	outline.setSize(sf::Vector2f(texWidth - outlineThickness * 2.0f, texHeight - outlineThickness * 2.0f));
	outline.setFillColor(sf::Color(0, 0, 0, 0));
	outline.setOutlineColor(sf::Color());
	outline.setOutlineThickness(outlineThickness);

	tex_.create(static_cast<unsigned int>(texWidth),
		static_cast<unsigned int>(texHeight));

	tex_.clear(backgroundColor);
	tex_.draw(tipText);
	tex_.draw(outline);
	tex_.display();

	img_ = sf::Sprite(tex_.getTexture());

	this->synchronizePosition();
}