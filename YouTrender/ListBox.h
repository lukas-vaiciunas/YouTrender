#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ButtonPrimitiveTextual.h"
#include "Collideable.h"

class ListBox : public Collideable
{
protected:
	std::vector<ButtonPrimitiveTextual *> options_;
	sf::Color defaultColor_;
	sf::Color selectedColor_;

	virtual void toggleSelection(size_t buttonIndex) = 0;
public:
	enum class ORIENTATION : uint8_t
	{
		HORIZONTAL,
		VERTICAL
	};

	ListBox
	(
		float x, float y,
		float buttonWidth, float buttonHeight,
		float gapX, float gapY,
		const std::vector<std::string> &optionsTxt,
		const sf::Color &defaultColor,
		const sf::Color &selectedColor,
		ORIENTATION orientation
	);

	~ListBox();

	void updateOnMousePress();

	void render(sf::RenderWindow &window) const;

	virtual bool somethingSelected() const = 0;
};