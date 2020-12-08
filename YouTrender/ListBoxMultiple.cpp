#include "ListBoxMultiple.h"
#include "ChoiceButton.h"

ListBoxMultiple::ListBoxMultiple
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
	)
{}

void ListBoxMultiple::toggleSelection(size_t buttonIndex)
{
	auto buttonIt = selected_.find(buttonIndex);

	if (buttonIt != selected_.cend())
		selected_.erase(buttonIt);
	else selected_.emplace(buttonIndex);

	choiceButtons_[buttonIndex]->toggle();
}

bool ListBoxMultiple::somethingSelected() const
{
	return selected_.size() > 0;
}

const std::unordered_set<size_t> &ListBoxMultiple::selectedIndicies() const
{
	return selected_;
}