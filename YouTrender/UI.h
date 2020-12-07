#pragma once

#include <SFML/Graphics.hpp>

class UI
{
protected:
	std::string title_;
	unsigned int uID_;
	bool isClosed_;
	bool isMinimized_;
public:
	UI(const std::string &title);
	~UI();

	virtual void updateOnMousePress() = 0;
	virtual void updateOnMouseRelease() = 0;
	virtual void updateOnMouseAxes() = 0;

	virtual void render(sf::RenderWindow &window) const = 0;

	void maximize();

	const std::string &getTitle() const;
	unsigned int getUID() const;
	bool isClosed() const;
	bool isMinimized() const;
};