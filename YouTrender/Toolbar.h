#pragma once

class UI;

#include <SFML/Graphics.hpp>
#include <vector>
#include "Collideable.h"
#include "ButtonPrimitiveTooltipped.h"

class Toolbar : public Collideable
{
private:
	std::vector<UI *> items_;
	std::vector<ButtonPrimitiveTooltipped *> itemButtons_;
	sf::RectangleShape bar_;
	sf::RectangleShape outline_;

	void remove(size_t index);
public:
	Toolbar(float height);
	~Toolbar();

	void add(UI *item);

	void updateOnMousePress();

	void render(sf::RenderWindow &window) const;
};