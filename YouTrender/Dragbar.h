#pragma once

#include "Collideable.h"

class Dragbar : public Collideable
{
private:
	sf::RectangleShape visual_;
	bool isDragging_;
	float offsetX_;
	float offsetY_;
public:
	Dragbar(const sf::FloatRect &aabb);
	Dragbar(float x, float y, float width, float height);

	bool updateOnMousePress();
	void updateOnMouseRelease();
	void updateOnMouseAxes();

	void render(sf::RenderWindow &window) const;

	void setPosition(float x, float y);
	void setSize(float width, float height);

	bool isDragging() const;
};