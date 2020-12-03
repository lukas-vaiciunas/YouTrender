#include "Widget.h"
#include "Constants.h"
#include "FontData.h"

Widget::Widget(float x, float y, const std::string &title) :
	UI(),
	x_(x),
	y_(y),
	width_(0),
	height_(0),
	widgetBar_(x, y, 0, title),
	source_(nullptr),
	visual_(),
	outline_()
{
	outline_.setFillColor(sf::Color(0, 0, 0, 0));
	outline_.setOutlineThickness(1.0f);
	outline_.setOutlineColor(sf::Color());

	barSeparator_.setFillColor(sf::Color());

	this->setPosition(x, y);
}

Widget::Widget(float x, float y, const std::string &title, Visual *source) :
	Widget(x, y, title)
{
	this->attach(source);
}

Widget::~Widget()
{
	delete source_;
	source_ = nullptr;
}

void Widget::synchronizePosition()
{
	this->setPosition(widgetBar_.getX(), widgetBar_.getY());
}

void Widget::constrain()
{
	float newX = x_;
	float newY = y_;

	if (x_ + width_ > Global::SCREEN_WIDTH)
		newX = static_cast<float>(Global::SCREEN_WIDTH) - width_;
	else if (x_ < 0.0f)
		newX = 0.0f;

	if (y_ + height_ > Global::SCREEN_HEIGHT)
		newY = static_cast<float>(Global::SCREEN_HEIGHT) - height_;
	else if (y_ < 0.0f)
		newY = 0.0f;

	this->setPosition(newX, newY);
}

void Widget::updateOnMousePress()
{
	typedef WidgetBar::EVENT_TYPE EventType;

	EventType ev = widgetBar_.updateOnMousePress(uID_);

	switch (ev)
	{
	case EventType::CLOSED:
		isClosed_ = true;
		break;
	case EventType::MINIMIZED:
		isMinimized_ = true;
		break;
	}
}

void Widget::updateOnMouseRelease()
{
	widgetBar_.updateOnMouseRelease();
}

void Widget::updateOnMouseAxes()
{
	if (widgetBar_.updateOnMouseAxes())
	{
		this->synchronizePosition();
		this->constrain();
	}
}

void Widget::render(sf::RenderWindow &window) const
{
	sf::RectangleShape outline;

	widgetBar_.render(window);
	window.draw(visual_);
	window.draw(outline_);
	window.draw(barSeparator_);
}

void Widget::attach(Visual *source)
{
	delete source_;
	source_ = nullptr;
	source_ = source;

	visual_.setTexture(source_->getTexture());

	this->setSize(source_->getWidth(), source_->getHeight() + static_cast<unsigned int>(Global::BAR_HEIGHT));
}

void Widget::setPosition(float x, float y)
{
	x_ = x;
	y_ = y;
	widgetBar_.setPosition(x, y);
	visual_.setPosition(x, y + Global::BAR_HEIGHT);
	outline_.setPosition(x, y);
	barSeparator_.setPosition(x, y + Global::BAR_HEIGHT);
}

void Widget::setSize(unsigned int width, unsigned int height)
{
	width_ = width;
	height_ = height;

	widgetBar_.setWidth(width - Global::BAR_HEIGHT);
	outline_.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	barSeparator_.setSize(sf::Vector2f(static_cast<float>(width), 1.0f));
}