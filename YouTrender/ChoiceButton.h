#pragma once

#include "Button.h"

class ChoiceButton : public Button
{
private:
	sf::RenderTexture tex_;
	sf::Text text_;
	unsigned int currentTexId_;
	unsigned int defaultTexId_;
	unsigned int activeTexId_;

	void updateTexture(unsigned int texId);
public:
	ChoiceButton(float x, float y, float width, float height, unsigned int defaultTexId, unsigned int activeTexId, const std::string &text, unsigned int fontSize, const sf::Color &textColor, float textPosMod);

	void toggle();
};