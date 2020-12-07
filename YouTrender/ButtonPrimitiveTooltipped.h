#pragma once

#include "PrimitiveButton.h"
#include "Tooltipped.h"

class ButtonPrimitiveTooltipped :
	public PrimitiveButton,
	public Tooltipped
{
public:
	ButtonPrimitiveTooltipped(float x, float y, float width, float height, const sf::Color &color, const std::string &tip);
};