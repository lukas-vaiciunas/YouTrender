#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

class TextureData
{
private:
	static TextureData *instance_;

	std::unordered_map<unsigned int, sf::Texture> textures_;

	TextureData();
	~TextureData();
public:
	TextureData(const TextureData &) = delete;
	TextureData &operator=(const TextureData &) = delete;

	static TextureData *getInstance();

	const sf::Texture &getTexture(unsigned int id) const;
};