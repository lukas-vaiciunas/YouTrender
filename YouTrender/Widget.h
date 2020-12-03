#pragma once

#include <SFML/Graphics.hpp>
#include "WidgetBar.h"
#include "UI.h"
#include "Visual.h"

class Widget : public UI
{
private:
	WidgetBar widgetBar_;
	Visual *source_;
	sf::Sprite visual_;
	sf::RectangleShape outline_;
	sf::RectangleShape barSeparator_;

	float x_;
	float y_;
	unsigned int width_;
	unsigned int height_;

	void synchronizePosition();
	void constrain();
public:
	Widget(float x, float y, const std::string &title);
	Widget(float x, float y, const std::string &title, Visual *source);
	~Widget();

	void updateOnMousePress() override;
	void updateOnMouseRelease() override;
	void updateOnMouseAxes() override;

	void render(sf::RenderWindow &window) const override;

	void attach(Visual *source);

	void setPosition(float x, float y);
	void setSize(unsigned int width, unsigned int height);
};