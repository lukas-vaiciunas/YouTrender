#include "ListBoxSingle.h"

ListBoxSingle::ListBoxSingle
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
	),
	selected_(-1)
{}

void ListBoxSingle::toggleSelection(size_t buttonIndex)
{
	if (selected_ != -1)
		options_[selected_]->setColor(defaultColor_);

	if (selected_ == buttonIndex)
		selected_ = -1;
	else
	{
		selected_ = buttonIndex;
		options_[buttonIndex]->setColor(selectedColor_);
	}
}

bool ListBoxSingle::somethingSelected() const
{
	return selected_ != -1;
}

int ListBoxSingle::selectedIndex() const
{
	return selected_;
}