#pragma once

#include <deque>
#include <string>
#include "SFML/Graphics.hpp"

class Log
{
private:
	static constexpr unsigned int FONT_SIZE_ = 12U;

	static Log *instance_;

	std::deque<std::string> data_;

	sf::RenderTexture tex_;
	sf::Sprite vis_;

	Log();
	~Log();

	void updateVis();
public:
	Log(const Log &) = delete;
	Log &operator=(const Log &) = delete;

	static Log *getInstance();

	void render(sf::RenderWindow &window) const;

	void push(const std::string &text);

	void setPosition(float x, float y);
};