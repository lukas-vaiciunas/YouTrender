#pragma once

#include <SFML/Graphics.hpp>

class UI
{
protected:
	unsigned int uID_;
	bool isClosed_;
	bool isMinimized_;
public:
	UI();
	~UI();

	virtual void updateOnMousePress() = 0;
	virtual void updateOnMouseRelease() = 0;
	virtual void updateOnMouseAxes() = 0;

	virtual void render(sf::RenderWindow &window) const = 0;

	void maximize();

	unsigned int getUID() const;
	bool isClosed() const;
	bool isMinimized() const;
};