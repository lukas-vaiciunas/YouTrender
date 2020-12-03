#pragma once

#include <SFML/Graphics.hpp>

class Visual
{
protected:
	sf::RenderTexture tex_;
	unsigned int width_;
	unsigned int height_;
public:
	Visual(unsigned int width, unsigned int height);

	const sf::Texture &getTexture() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
};