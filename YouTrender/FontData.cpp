#include "FontData.h"

FontData *FontData::instance_ = nullptr;

FontData::FontData()
{
	if (!mainFont_.loadFromFile("font/Roboto/Roboto-Regular.ttf"))
		throw std::runtime_error("Failed to load mainFont_!");
}

FontData::~FontData()
{
	delete instance_;
	instance_ = nullptr;
}

FontData *FontData::getInstance()
{
	if (!instance_)
		instance_ = new FontData();

	return instance_;
}

const sf::Font &FontData::getMainFont() const
{
	return mainFont_;
}