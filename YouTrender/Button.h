#pragma once

#include "Collideable.h"

class Button : virtual public Collideable
{
protected:
	sf::Sprite sprite_;
public:
	//Button(const sf::FloatRect &aabb, const sf::Texture &tex);
	Button(float x, float y, float width, float height, const sf::Texture &tex);

	void render(sf::RenderWindow &window) const;

	bool isClicked() const;

	void setPosition(float x, float y);
};