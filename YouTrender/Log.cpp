#include "Log.h"
#include "Constants.h"
#include "FontData.h"

Log *Log::instance_ = nullptr;

Log::Log() :
	tex_(),
	vis_(tex_.getTexture())
{
	tex_.create(Global::SCREEN_WIDTH / 4, Global::SCREEN_HEIGHT / 2);
	vis_ = sf::Sprite(tex_.getTexture());
	this->updateVis();
	this->setPosition(Global::SCREEN_WIDTH * 3.0f / 4.0f, 0.0f);
}

Log::~Log()
{
	delete instance_;
	instance_ = nullptr;
}

void Log::updateVis()
{
	sf::Color backgroundColor(255, 255, 255, 125);
	sf::Color textColor(0, 0, 0, 255);
	sf::RectangleShape outline;

	unsigned int width = tex_.getSize().x;
	unsigned int height = tex_.getSize().y;

	float maxY = height - FONT_SIZE_ * 2.0f;

	unsigned int lineCap = static_cast<unsigned int>(maxY) / FONT_SIZE_;
	unsigned int numLines = (lineCap > data_.size() ? data_.size() : lineCap);

	std::vector<sf::Text> lines_;

	for (unsigned int i = 0; i < numLines; i++)
	{
		lines_.push_back(sf::Text(data_[i], FontData::getInstance()->getMainFont(), FONT_SIZE_));
		lines_[i].setPosition(0.0f, maxY - FONT_SIZE_ * i);
		lines_[i].setFillColor(textColor);
	}

	float outlineThickness = 1.0f;

	outline.setFillColor(sf::Color(0, 0, 0, 0));
	outline.setPosition(outlineThickness, outlineThickness);
	outline.setSize(sf::Vector2f(width - outlineThickness * 2.0f, height - outlineThickness * 2.0f));
	outline.setOutlineThickness(outlineThickness);
	outline.setOutlineColor(sf::Color());

	tex_.clear(backgroundColor);

	for (const sf::Text &line : lines_)
		tex_.draw(line);

	tex_.draw(outline);

	tex_.display();
}

Log *Log::getInstance()
{
	if (!instance_)
		instance_ = new Log();

	return instance_;
}

void Log::render(sf::RenderWindow &window) const
{
	window.draw(vis_);
}

void Log::push(const std::string &text)
{
	data_.push_front(text);

	this->updateVis();
}

void Log::setPosition(float x, float y)
{
	vis_.setPosition(x, y);
}