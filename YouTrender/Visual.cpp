#include "Visual.h"

Visual::Visual(unsigned int width, unsigned int height) :
	width_(width),
	height_(height),
	tex_()
{
	if (!tex_.create(width, height))
		throw std::runtime_error("Failed to create texture!");
}

const sf::Texture &Visual::getTexture() const
{
	return tex_.getTexture();
}

unsigned int Visual::getWidth() const
{
	return width_;
}

unsigned int Visual::getHeight() const
{
	return height_;
}