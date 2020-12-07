#include "ButtonPrimitiveTooltipped.h"

ButtonPrimitiveTooltipped::ButtonPrimitiveTooltipped(float x, float y, float width, float height, const sf::Color &color, const std::string &tip) :
	PrimitiveButton(x, y, width, height, color),
	Tooltipped(x, y, width, height, tip),
	Collideable(x, y, width, height)
{}