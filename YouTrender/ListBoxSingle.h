#pragma once

#include "ListBox.h"

class ListBoxSingle : public ListBox
{
private:
	int selected_;

	void toggleSelection(size_t buttonIndex) override;
public:
	ListBoxSingle
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
	int selectedIndex() const;
};