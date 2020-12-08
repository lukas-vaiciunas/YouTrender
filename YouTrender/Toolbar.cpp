#include "Toolbar.h"
#include "Constants.h"
#include "Mouse.h"
#include "UIPool.h"
#include "TextureData.h"
#include "TooltippedButton.h"

Toolbar::Toolbar(float height) :
	Collideable(
		0.0f, Global::SCREEN_HEIGHT - height,
		static_cast<float>(Global::SCREEN_WIDTH), height)
{
	bar_.setPosition(Collideable::aabb_.left, Collideable::aabb_.top);
	bar_.setSize(sf::Vector2f(Collideable::aabb_.width, Collideable::aabb_.height));
	bar_.setFillColor(sf::Color(50, 110, 176, 255));

	outline_.setPosition(bar_.getPosition());
	outline_.setSize(sf::Vector2f(bar_.getLocalBounds().width, 1.0f));
	outline_.setFillColor(sf::Color());
}

Toolbar::~Toolbar()
{
	while (!items_.empty())
	{
		delete items_.back();
		items_.back() = nullptr;
		items_.pop_back();

		delete itemButtons_.back();
		itemButtons_.back() = nullptr;
		itemButtons_.pop_back();
	}
}

void Toolbar::remove(size_t index)
{
	items_.erase(items_.cbegin() + index);

	delete itemButtons_[index];
	itemButtons_[index] = nullptr;
	itemButtons_.erase(itemButtons_.cbegin() + index);

	for (size_t i = index; i < itemButtons_.size(); i++)
	{
		float offset = 8.0f;
		float size = 32.0f;
		float dX = Collideable::aabb_.left + (size + offset) * i;
		float dY = Collideable::aabb_.top;

		itemButtons_[i]->setPosition(dX, dY);
	}		
}

void Toolbar::add(UI *item)
{
	float offset = 8.0f;
	float size = 32.0f;
	float dX = Collideable::aabb_.left + (size + offset) * items_.size();
	float dY = Collideable::aabb_.top;

	items_.push_back(item);
	itemButtons_.push_back(new TooltippedButton(dX, dY, size, size, TextureData::getInstance()->getTexture(23), item->getTitle()));
}

void Toolbar::updateOnMousePress()
{
	const Mouse &mouse = *Mouse::getInstance();

	if (mouse.interactable() &&
		mouse.isPressed(Mouse::BUTTON::LEFT) &&
		Collideable::isColliding(mouse.getPosition()))
	{
		for (size_t i = 0; i < itemButtons_.size(); i++)
		{
			if (itemButtons_[i]->isClicked())
			{
				items_[i]->maximize();
				UIPool::add(items_[i]);
				this->remove(i);
			}
		}
	}
}

void Toolbar::render(sf::RenderWindow &window) const
{
	window.draw(bar_);

	for (const TooltippedButton *pb : itemButtons_)
		pb->render(window);

	window.draw(outline_);
}