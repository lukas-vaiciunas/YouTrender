#include "ListBox.h"
#include "Mouse.h"

ListBox::ListBox
(
	float x, float y,
	float buttonWidth, float buttonHeight,
	float gapX, float gapY,
	const std::vector<std::string> &optionsTxt,
	const sf::Color &defaultColor,
	const sf::Color &selectedColor,
	ORIENTATION orientation
) :
	Collideable(x, y, 0.0f, 0.0f),
	defaultColor_(defaultColor),
	selectedColor_(selectedColor)
{
	typedef ListBox::ORIENTATION ORIENT;

	float dX = (orientation == ORIENT::HORIZONTAL ? buttonWidth + gapX : 0.0f);
	float dY = (orientation == ORIENT::VERTICAL ? buttonHeight + gapY : 0.0f);

	for (size_t i = 0; i < optionsTxt.size(); i++)
	{
		options_.push_back(
			new ButtonPrimitiveTextual(
				x + dX * i,
				y + dY * i,
				buttonWidth,
				buttonHeight,
				optionsTxt[i],
				static_cast<unsigned int>(buttonHeight / 2.0f),
				defaultColor,
				sf::Color()
			)
		);
	}

	Collideable::setSize((buttonWidth + gapX) * options_.size() - gapX, buttonHeight);
}

ListBox::~ListBox()
{
	while (!options_.empty())
	{
		delete options_.back();
		options_.back() = nullptr;
		options_.pop_back();
	}
}

void ListBox::updateOnMousePress()
{
	for (size_t i = 0; i < options_.size(); i++)
	{
		if (options_[i]->isClicked())
		{
			this->toggleSelection(i);
			break;
		}
	}
}

void ListBox::render(sf::RenderWindow &window) const
{
	for (const PrimitiveButton *b : options_)
		b->render(window);
}