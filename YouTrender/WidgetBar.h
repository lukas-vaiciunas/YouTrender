#pragma once

class Widget;

#include "Dragbar.h"
#include "Button.h"

class WidgetBar
{
private:
	Dragbar dragbar_;
	Button closeButton_;
	Button minimizeButton_;
	sf::Text title_;
	//bool isClosed_;
	//bool isMinimized_;
public:
	enum class EVENT_TYPE
	{
		NONE,
		CLOSED,
		MINIMIZED,
		PRIORITIZED
	};

	WidgetBar(float x, float y, float width, const sf::String &title);

	EVENT_TYPE updateOnMousePress(unsigned int uiUID);
	void updateOnMouseRelease();
	bool updateOnMouseAxes();

	void render(sf::RenderWindow &window) const;

	void setPosition(float x, float y);
	void setWidth(float width);

	bool isDragging() const;
	//bool isClosed() const;
	float getX() const;
	float getY() const;
};