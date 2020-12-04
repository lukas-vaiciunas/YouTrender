#pragma once

#include <SFML/Graphics.hpp>

class Overlay
{
private:
	sf::RenderTexture tex_;
	sf::Sprite img_;
public:
	Overlay(const std::string &txt, unsigned int txtSize, const sf::Color &txtColor, const sf::Color &backgroundColor);

	void render(sf::RenderWindow &window) const;
};