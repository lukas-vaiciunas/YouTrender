#include "TextureData.h"
#include "Constants.h"
#include <fstream>

TextureData *TextureData::instance_ = nullptr;

TextureData::TextureData()
{
	sf::Texture tex;
	std::ifstream inFile;
	std::string id;
	std::string filePath;

	inFile.open("loading/imgData.txt");

	if (!inFile.is_open())
		throw std::runtime_error("Failed to open imgData.txt for Texture loading in TextureData!");

	while (inFile.peek() != EOF)
	{
		inFile >> id;
		inFile >> filePath;

		tex.loadFromFile(filePath);

		textures_.emplace(std::stoul(id), tex);
	}

	inFile.close();
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