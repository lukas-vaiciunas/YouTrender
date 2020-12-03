#pragma once

#include <SFML/Graphics.hpp>

class FontData
{
private:
	static FontData *instance_;

	sf::Font mainFont_;

	FontData();
	~FontData();
public:
	FontData(const FontData &) = delete;
	FontData &operator=(const FontData &) = delete;

	static FontData *getInstance();

	const sf::Font &getMainFont() const;
};