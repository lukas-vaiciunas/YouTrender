#pragma once

#include <SFML/Graphics.hpp>
#include "Timer.h"

class IntroMovie
{
private:
	enum class STATE
	{
		SHOW,
		FADE
	};

	sf::Sprite img_;
	sf::Text skipText_;

	STATE state_;
	Timer showTimer_;

	unsigned char alpha_;
	unsigned char deltaAlpha_;
	bool done_;
public:
	enum class FADE_SPEED : uint8_t
	{
		SLOW = 1,
		MEDIUM = 3,
		FAST = 5
	};

	IntroMovie(float showSecs, unsigned char deltaAlpha, const sf::Texture &imgTexture);
	IntroMovie(float showSecs, FADE_SPEED fadeSpeed, const sf::Texture &imgTexture);

	void updateOnTick();
	void updateOnMousePress();
	void updateOnKeyPress();
	void render(sf::RenderWindow &window) const;

	bool done() const;
};