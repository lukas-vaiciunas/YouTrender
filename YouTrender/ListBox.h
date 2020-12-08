#pragma once

class ChoiceButton;

#include "Collideable.h"

class ListBox : public Collideable
{
protected:
	std::vector<ChoiceButton *> choiceButtons_;

	virtual void toggleSelection(size_t buttonIndex) = 0;
public:
	ListBox
	(
		float x, float y,
		float buttonWidth, float buttonHeight,
		float gapX,
		const std::vector<unsigned int> &buttonTexIds,
		const std::vector<std::string> &optionsTxt,
		const sf::Color &textColor,
		float textPosMod
	);

	~ListBox();

	void updateOnMousePress();

	void render(sf::RenderWindow &window) const;

	virtual bool somethingSelected() const = 0;
};