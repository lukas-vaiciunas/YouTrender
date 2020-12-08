#include "TooltippedButton.h"

TooltippedButton::TooltippedButton(float x, float y, float width, float height, const sf::Texture &tex, const std::string &tip) :
	Button(x, y, width, height, tex),
	Tooltipped(x, y, width, height, tip),
	Collideable(x, y, width, height)
{}