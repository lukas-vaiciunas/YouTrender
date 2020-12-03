#pragma once

#include "PrimitiveButton.h"

class ButtonPrimitiveTextual : public PrimitiveButton
{
private:
	sf::Text txt_;
public:
	ButtonPrimitiveTextual(float x, float y, float width, float height, const std::string &text, unsigned int textSize, const sf::Color &color, const sf::Color &textColor);

	void setColor(const sf::Color &color) override;
};

/*
	Graph appears large next to data input, but there is a button to
	export to a widget. Then, widget may be minimized to the bottom of the screen
	and reopened with a click
*/