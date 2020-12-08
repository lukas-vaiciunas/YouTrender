#pragma once

#include "PrimitiveButton.h"
#include "Tooltipped.h"

class TooltippedButton :
	public Button,
	public Tooltipped
{
public:
	TooltippedButton(float x, float y, float width, float height, const sf::Texture &tex, const std::string &tip);
};