#pragma once

#include <SFML/Graphics.hpp>

class Tooltip
{
private:
	sf::RenderTexture tex_;
	sf::Sprite img_;

	void synchronizePosition();
public:
	Tooltip();

	void updateOnMouseAxes();

	void render(sf::RenderWindow &window) const;

	void activate(const std::string &tip);
};