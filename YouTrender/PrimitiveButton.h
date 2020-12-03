#pragma once

#include "Button.h"

class PrimitiveButton : public Button
{
protected:
	sf::RenderTexture tex_;
public:
	PrimitiveButton(float x, float y, float width, float height, const sf::Color &color);
	//PrimitiveButton(float x, float y, float width, float height, const std::string &text, unsigned int textSize, const sf::Color &color, const sf::Color &textColor);

	virtual void setColor(const sf::Color &color);
};