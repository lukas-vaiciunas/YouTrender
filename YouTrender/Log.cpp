#include "Log.h"
#include "Constants.h"
#include "FontData.h"

Log *Log::instance_ = nullptr;

Log::Log() :
	Visual(Global::SCREEN_WIDTH / 4, Global::SCREEN_HEIGHT / 2)
{
	this->updateVis();
}

Log::~Log()
{
	delete instance_;
	instance_ = nullptr;
}

void Log::updateVis()
{
	sf::Color backgroundColor(40, 40, 40, 255);
	sf::Color textColor(255, 255, 255, 255);

	unsigned int height = tex_.getSize().y;

	unsigned int lineCap = height / FONT_SIZE_;
	unsigned int numLines = (lineCap > data_.size() ? data_.size() : lineCap);

	std::vector<sf::Text> lines;

	for (unsigned int i = 0; i < numLines; i++)
	{
		lines.push_back(sf::Text(data_[numLines - 1 - i], FontData::getInstance()->getMainFont(), FONT_SIZE_));
		lines[i].setPosition(0.0f, std::floorf(static_cast<float>(FONT_SIZE_ * i)));
		lines[i].setFillColor(textColor);
	}

	tex_.clear(backgroundColor);

	for (const sf::Text &line : lines)
		tex_.draw(line);

	tex_.display();
}

Log *Log::getInstance()
{
	if (!instance_)
		instance_ = new Log();

	return instance_;
}

void Log::push(const std::string &text)
{
	data_.push_front(text);

	this->updateVis();
}