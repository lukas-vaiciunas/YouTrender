#pragma once

#include <vector>
#include "ListBox.h"
#include "Collideable.h"

class InputPanel : public Collideable
{
private:
	sf::Text title_;
	std::vector<sf::Text> listTitles_;
	std::vector<ListBox *> listBoxes_;
	ButtonPrimitiveTextual analyzeButton_;
public:
	InputPanel
	(
		float x, float y,
		const std::string &titleStr,
		const std::vector<std::pair<std::string, std::vector<std::string>>> &options,
		const sf::Color &defaultColor, const sf::Color &selectedColor
	);

	~InputPanel();

	void updateOnMousePress();

	void render(sf::RenderWindow &window) const;
};