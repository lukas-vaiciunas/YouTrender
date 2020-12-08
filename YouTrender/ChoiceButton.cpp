#include "ChoiceButton.h"
#include "FontData.h"
#include "TextureData.h"

ChoiceButton::ChoiceButton(float x, float y, float width, float height, unsigned int defaultTexId, unsigned int activeTexId, const std::string &text, unsigned int fontSize, const sf::Color &textColor, float textPosMod) :
	Button(x, y, width, height, TextureData::getInstance()->getTexture(defaultTexId)),
	Collideable(x, y, width, height),
	tex_(),
	text_(text, FontData::getInstance()->getMainFont(), fontSize),
	currentTexId_(defaultTexId),
	defaultTexId_(defaultTexId),
	activeTexId_(activeTexId)
{
	const sf::FloatRect &txtBounds = text_.getLocalBounds();

	text_.setOrigin(std::floorf(txtBounds.left + txtBounds.width / 2.0f), std::floorf(txtBounds.top + txtBounds.height / 2.0f));
	text_.setPosition(std::floorf(width * textPosMod), std::floorf(height / 2.0f));
	text_.setFillColor(textColor);

	tex_.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height));

	this->updateTexture(defaultTexId);
}

void ChoiceButton::updateTexture(unsigned int texId)
{
	sf::Sprite background(TextureData::getInstance()->getTexture(texId));

	tex_.clear(sf::Color(0, 0, 0, 0));
	tex_.draw(background);
	tex_.draw(text_);
	tex_.display();

	sprite_.setTexture(tex_.getTexture());
}

void ChoiceButton::toggle()
{
	currentTexId_ = (currentTexId_ == defaultTexId_ ? activeTexId_ : defaultTexId_);

	//sprite_.setTexture(TextureData::getInstance()->getTexture(currentTexId_));
	this->updateTexture(currentTexId_);
}