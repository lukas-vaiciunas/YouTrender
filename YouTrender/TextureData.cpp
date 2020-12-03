#include "TextureData.h"
#include "Constants.h"

TextureData *TextureData::instance_ = nullptr;

TextureData::TextureData()
{
	sf::RenderTexture closeButton;
	closeButton.create(static_cast<unsigned int>(Global::BAR_HEIGHT),
		static_cast<unsigned int>(Global::BAR_HEIGHT));
	closeButton.clear(sf::Color(255, 0, 0, 255));
	closeButton.display();

	textures_.emplace(0, closeButton.getTexture());

	sf::RenderTexture minimizeButton;
	minimizeButton.create(static_cast<unsigned int>(Global::BAR_HEIGHT),
		static_cast<unsigned int>(Global::BAR_HEIGHT));
	minimizeButton.clear(sf::Color(255, 255, 0, 255));
	minimizeButton.display();

	textures_.emplace(1, minimizeButton.getTexture());

	sf::RenderTexture logo;
	logo.create(Global::SCREEN_WIDTH / 2, Global::SCREEN_HEIGHT / 2);
	logo.clear(sf::Color(255, 0, 0, 255));
	logo.display();

	textures_.emplace(2, logo.getTexture());
}

TextureData::~TextureData()
{
	delete instance_;
	instance_ = nullptr;
}

TextureData *TextureData::getInstance()
{
	if (!instance_)
		instance_ = new TextureData();

	return instance_;
}

const sf::Texture &TextureData::getTexture(unsigned int id) const
{
	return textures_.at(id);
}