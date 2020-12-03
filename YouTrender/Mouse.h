#pragma once

#include <SFML/Window.hpp>

class Mouse
{
private:
	static constexpr unsigned int NUM_BUTTONS = 2;

	static Mouse *instance_;

	int x_;
	int y_;
	bool buttons_[NUM_BUTTONS];
	bool interactable_;

	Mouse();
	~Mouse();

	void releaseAll();
public:
	enum BUTTON
	{
		LEFT,
		RIGHT
	};

	Mouse(const Mouse &) = delete;
	Mouse &operator=(const Mouse &) = delete;
	
	static Mouse *getInstance();

	void updatePresses(const sf::Event &ev);
	void updateReleases(const sf::Event &ev);
	void updateAxes(const sf::Window &relativeTo);

	bool isPressed(BUTTON button) const;
	void release(BUTTON button);

	void lockInteraction();
	void unlockInteraction();

	int getX() const;
	int getY() const;
	sf::Vector2i getPosition() const;
	bool interactable() const;
};