#pragma once

#include <unordered_set>
#include "ListBox.h"

class ListBoxMultiple : public ListBox
{
private:
	std::unordered_set<size_t> selected_;

	void toggleSelection(size_t buttonIndex) override;
public:
	ListBoxMultiple
	(
		float x, float y,
		float buttonWidth, float buttonHeight,
		float gapX,
		const std::vector<unsigned int> &buttonTexIds,
		const std::vector<std::string> &optionsTxt,
		const sf::Color &textColor,
		float textPosMod
	);

	bool somethingSelected() const override;
	const std::unordered_set<size_t> &selectedIndicies() const;
};