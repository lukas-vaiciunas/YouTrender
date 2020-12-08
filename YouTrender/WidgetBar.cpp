#include "WidgetBar.h"
#include "TextureData.h"
#include "Mouse.h"
#include "Widget.h"
#include "Constants.h"
#include "UIPool.h"
#include "FontData.h"

WidgetBar::WidgetBar(float x, float y, float width, const sf::String &title) :
	dragbar_(x, y, width - Global::BAR_HEIGHT, Global::BAR_HEIGHT),
	closeButton_(x + width - Global::BAR_HEIGHT, y, Global::BAR_HEIGHT, Global::BAR_HEIGHT,
		TextureData::getInstance()->getTexture(1)),
	minimizeButton_(x + width - Global::BAR_HEIGHT * 2.0f, y, Global::BAR_HEIGHT, Global::BAR_HEIGHT,
		TextureData::getInstance()->getTexture(2)),
	title_(title, FontData::getInstance()->getMainFont(), 12U)
	//isClosed_(false)
{
	title_.setPosition(std::floorf(x + width / 2.0f - title_.getGlobalBounds().width / 2.0f), y);
	title_.setFillColor(sf::Color(0, 0, 0, 255));
}

/*void WidgetBar::updateMouseInteraction(Widget &parent)
{
	if (closeButtonClicked())
	{
		std::cout << "Button clicked!" << std::endl;
		isClosed_ = true;
		//send event to update ui hierarchy? (so that this will be cleaned up)
	}

	dragbar_.updateMouseInteraction();

	sf::FloatRect &barAABB = dragbar_.getAABB();

	if (dragbar_.isDragging())
	{
		closeButton_.setPosition(barAABB.left + barAABB.width, barAABB.top);
		parent.setPosition(barAABB.left, barAABB.top);
	}
}*/

WidgetBar::EVENT_TYPE WidgetBar::updateOnMousePress(unsigned int uiUID)
{
	if (closeButton_.isClicked())
	{
		//UIPool::remove(uiUID);
		//isClosed_ = true;
		UIPool::flagCleanup();
		return EVENT_TYPE::CLOSED;
		//send event to update ui hierarchy? (so that this will be cleaned up)
	}
	else if (minimizeButton_.isClicked())
	{
		UIPool::flagCleanup();
		return EVENT_TYPE::MINIMIZED;
	}

	if (dragbar_.updateOnMousePress())
	{
		UIPool::prioritize(uiUID);
		return EVENT_TYPE::PRIORITIZED;
	}
	
	return EVENT_TYPE::NONE;
}

void WidgetBar::updateOnMouseRelease()
{
	dragbar_.updateOnMouseRelease();
}

bool WidgetBar::updateOnMouseAxes()
{
	dragbar_.updateOnMouseAxes();

	return dragbar_.isDragging();
}

void WidgetBar::setPosition(float x, float y)
{
	const sf::FloatRect &barAABB = dragbar_.getAABB();

	dragbar_.setPosition(x, y);
	minimizeButton_.setPosition(x + barAABB.width - minimizeButton_.getAABB().width, y);
	closeButton_.setPosition(x + barAABB.width, y);
	title_.setPosition(std::floorf(x + (barAABB.width + closeButton_.getAABB().width) / 2.0f - title_.getGlobalBounds().width / 2.0f), y);
}

void WidgetBar::setWidth(float width)
{
	dragbar_.setSize(width, Global::BAR_HEIGHT);

	const sf::FloatRect &barAABB = dragbar_.getAABB();
	
	closeButton_.setPosition(barAABB.left + width, barAABB.top);
	minimizeButton_.setPosition(barAABB.left + width - minimizeButton_.getAABB().width, barAABB.top);
	title_.setPosition(std::floorf(barAABB.left + (barAABB.width + closeButton_.getAABB().width) / 2.0f - title_.getGlobalBounds().width / 2.0f), barAABB.top);
}

void WidgetBar::render(sf::RenderWindow &window) const
{
	dragbar_.render(window);
	closeButton_.render(window);
	minimizeButton_.render(window);
	window.draw(title_);
}

bool WidgetBar::isDragging() const
{
	return dragbar_.isDragging();
}

/*bool WidgetBar::isClosed() const
{
	return isClosed_;
}*/

float WidgetBar::getX() const
{
	return dragbar_.getAABB().left;
}

float WidgetBar::getY() const
{
	return dragbar_.getAABB().top;
}