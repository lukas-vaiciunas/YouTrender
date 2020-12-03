#include "ListBoxMultiple.h"

ListBoxMultiple::ListBoxMultiple
(
	float x, float y,
	float buttonWidth, float buttonHeight,
	float gapX, float gapY,
	const std::vector<std::string> &optionsTxt,
	const sf::Color &defaultColor,
	const sf::Color &selectedColor,
	ORIENTATION orientation
) :
	ListBox
	(
		x, y,
		buttonWidth, buttonHeight,
		gapX, gapY,
		optionsTxt,
		defaultColor,
		selectedColor,
		orientation
	)
{}

void ListBoxMultiple::toggleSelection(size_t buttonIndex)
{
	auto buttonIt = selected_.find(buttonIndex);

	if (buttonIt != selected_.cend())
	{
		selected_.erase(buttonIt);
		options_[buttonIndex]->setColor(defaultColor_);
	}
	else
	{
		selected_.emplace(buttonIndex);
		options_[buttonIndex]->setColor(selectedColor_);
	}
}

bool ListBoxMultiple::somethingSelected() const
{
	return selected_.size() > 0;
}

const std::unordered_set<size_t> &ListBoxMultiple::selectedIndicies() const
{
	return selected_;
}