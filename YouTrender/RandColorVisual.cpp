#include "RandColorVisual.h"
#include <random>

RandColorVisual::RandColorVisual(unsigned int width, unsigned int height) :
	Visual(width, height)
{
	this->updateOutput();
}

void RandColorVisual::updateOutput()
{
	std::random_device dev;
	std::mt19937 eng(dev());
	std::uniform_int_distribution<unsigned int> dis(0, 255);

	unsigned char r = dis(eng);
	unsigned char g = dis(eng);
	unsigned char b = dis(eng);

	//clear
	tex_.clear(sf::Color(r, g, b, 255));

	//flush to sprite
	tex_.display();
}