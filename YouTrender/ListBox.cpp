#include "ListBox.h"
#include "Mouse.h"
#include "ChoiceButton.h"

ListBox::ListBox
(
	float x, float y,
	float buttonWidth, float buttonHeight,
	float gapX,
	const std::vector<unsigned int> &buttonTexIds,
	const std::vector<std::string> &optionsTxt,
	const sf::Color &textColor,
	float textPosMod
) :
	Collideable(x, y, 0.0f, 0.0f)
{
	for (size_t i = 0; i < optionsTxt.size(); i++)
	{
		choiceButtons_.push_back(
			new ChoiceButton(
				x + (buttonWidth + gapX) * i,
				y,
				buttonWidth,
				buttonHeight,
				buttonTexIds[i],
				buttonTexIds[i] + 1,
				optionsTxt[i],
				12U,
				textColor,
				textPosMod
			)
		);
	}

	Collideable::setSize((buttonWidth + gapX) * choiceButtons_.size() - gapX, buttonHeight);
}

ListBox::~ListBox()
{
	while (!choiceButtons_.empty())
	{
		delete choiceButtons_.back();
		choiceButtons_.back() = nullptr;
		choiceButtons_.pop_back();
	}
}

void ListBox::updateOnMousePress()
{
	for (size_t i = 0; i < choiceButtons_.size(); i++)
	{
		if (choiceButtons_[i]->isClicked())
		{
			this->toggleSelection(i);
			break;
		}
	}
}

void ListBox::render(sf::RenderWindow &window) const
{
	for (const ChoiceButton *b : choiceButtons_)
		b->render(window);
}