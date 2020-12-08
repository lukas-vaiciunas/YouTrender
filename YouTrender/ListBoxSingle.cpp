#include "ListBoxSingle.h"
#include "ChoiceButton.h"

ListBoxSingle::ListBoxSingle
(
	float x, float y,
	float buttonWidth, float buttonHeight,
	float gapX,
	const std::vector<unsigned int> &buttonTexIds,
	const std::vector<std::string> &optionsTxt,
	const sf::Color &textColor,
	float textPosMod
) :
	ListBox
	(
		x, y,
		buttonWidth, buttonHeight,
		gapX,
		buttonTexIds,
		optionsTxt,
		textColor,
		textPosMod
	),
	selected_(-1)
{}

void ListBoxSingle::toggleSelection(size_t buttonIndex)
{
	if (selected_ != -1)
		choiceButtons_[selected_]->toggle();

	if (selected_ == buttonIndex)
		selected_ = -1;
	else
	{
		selected_ = buttonIndex;
		choiceButtons_[buttonIndex]->toggle();
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