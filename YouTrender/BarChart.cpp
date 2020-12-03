#include "BarChart.h"
#include "FontData.h"
#include "NumMod.h"
#include <iostream> //

std::vector<sf::Color> BarChart::colors_ =
std::vector<sf::Color>
{
	sf::Color(0, 104, 132),
	sf::Color(0, 144, 158),
	sf::Color(137, 219, 236),
	sf::Color(237, 0, 38),
	sf::Color(250, 157, 0),
	sf::Color(255, 208, 141),
	sf::Color(176, 0, 81),
	sf::Color(246, 131, 112),
	sf::Color(254, 171, 185),
	sf::Color(110, 0, 108),
	sf::Color(145, 39, 143),
	sf::Color(207, 151, 215)
};

BarChart::BarChart(unsigned int width, unsigned int height, const std::vector<std::pair<std::string, unsigned int>> &data) :
	Visual(width, height)
{
	for (size_t i = 0; i < colors_.size(); i++)
		unusedColors_.push(i);

	this->updateOutput(data);
}

void BarChart::updateOutput(const std::vector<std::pair<std::string, unsigned int>> &data)
{
	if (data.size() > unusedColors_.size())
		throw std::runtime_error("Cannot build BarChart! Too many data values, not enough colors.");

	sf::Color backgroundColor(255, 255, 255, 255);
	sf::Color accentColor(0, 0, 0, 255);

	std::vector<sf::RectangleShape> bars;
	std::vector<sf::RectangleShape> yTicks;
	std::vector<sf::Text> amtTxts;
	std::vector<sf::Text> independentTxts;
	std::vector<sf::Text> dependentTxts;
	sf::RectangleShape verticalAxis;
	sf::RectangleShape horizontalAxis;
	NumMod<uint64_t> numMod;

	unsigned int txtSize = 12U;
	float minBarX = 96.0f;
	float minBarY = 32.0f;
	float maxBarHeight = height_ - minBarY * 2.0f;
	float barWidth = width_ / data.size() / 4.0f;
	float spacing = barWidth * 2.5f;
	unsigned int numDependentTicks = 5;
	float dependentSpacing = maxBarHeight / numDependentTicks;

	uint64_t maxVal = 0;
	uint64_t maxDependent = 0;

	for (auto it = data.cbegin(); it != data.cend(); it++)
		if (maxVal < it->second)
			maxVal = it->second;

	maxDependent = numMod.roundUp(maxVal);

	std::cout << "Max Value: " << maxVal << std::endl;
	std::cout << "Max Dependent: " << maxDependent << std::endl;

	for (size_t i = 0; i < data.size(); i++)
	{
		float scale = data[i].second / static_cast<float>(maxDependent);
		float barHeight = maxBarHeight * scale;
		float dX = minBarX + (barWidth + spacing) * i;
		float dY = height_ - barHeight - minBarY;

		std::cout << "Scale: " << scale << ". Bar Height: " << barHeight << std::endl;

		const sf::Color &nextBarColor = colors_[unusedColors_.front()];

		bars.push_back(sf::RectangleShape());
		bars[i].setPosition(dX, dY);
		bars[i].setSize(sf::Vector2f(barWidth, barHeight));
		bars[i].setFillColor(nextBarColor);
		bars[i].setOutlineColor(sf::Color());
		bars[i].setOutlineThickness(1.0f);

		unusedColors_.pop();

		amtTxts.push_back(sf::Text(std::to_string(data[i].second), FontData::getInstance()->getMainFont(), txtSize));
		amtTxts[i].setOrigin(std::floorf(amtTxts[i].getLocalBounds().width / 2.0f), std::floorf(amtTxts[i].getLocalBounds().height / 2.0f));
		amtTxts[i].setPosition(std::floorf(dX + barWidth / 2.0f), std::floorf(dY - txtSize));
		amtTxts[i].setFillColor(accentColor);
	
		independentTxts.push_back(sf::Text(data[i].first, FontData::getInstance()->getMainFont(), txtSize));
		independentTxts[i].setOrigin(std::floorf(independentTxts[i].getLocalBounds().width / 2.0f), std::floorf(independentTxts[i].getLocalBounds().height / 2.0f));
		independentTxts[i].setPosition(std::floorf(dX + barWidth / 2.0f), std::floorf(dY + barHeight + minBarY / 2.0f));
		independentTxts[i].setFillColor(accentColor);
	}

	uint64_t deltaDependent = maxDependent / numDependentTicks;

	for (unsigned int i = 0; i <= numDependentTicks; i++)
	{
		float dY = std::floorf((maxBarHeight + minBarY) - dependentSpacing * i);

		dependentTxts.push_back(sf::Text(numMod.toShorthand(deltaDependent * i), FontData::getInstance()->getMainFont(), txtSize));
		dependentTxts[i].setOrigin(std::floorf(dependentTxts[i].getLocalBounds().width), std::floorf(txtSize / 2.0f + 1.0f));
		dependentTxts[i].setPosition(std::floorf(minBarX / 2.5f), dY);
		dependentTxts[i].setFillColor(accentColor);

		float tickWidth = minBarX / 5.0f;
		float tickHeight = 2.0f;

		yTicks.push_back(sf::RectangleShape());
		yTicks[i].setOrigin(tickWidth / 2.0f, tickHeight / 2.0f);
		yTicks[i].setPosition(minBarX / 2.0f, dY);
		yTicks[i].setSize(sf::Vector2f(tickWidth, tickHeight));
		yTicks[i].setFillColor(accentColor);
	}

	verticalAxis.setPosition(minBarX / 2.0f, 0.0f);
	verticalAxis.setSize(sf::Vector2f(2.0f, maxBarHeight + minBarY));
	verticalAxis.setFillColor(accentColor);

	horizontalAxis.setOrigin(0.0f, 2.0f / 2.0f);
	horizontalAxis.setPosition(minBarX / 2.0f, maxBarHeight + minBarY);
	horizontalAxis.setSize(sf::Vector2f(width_ - minBarX / 2.0f, 2.0f));
	horizontalAxis.setFillColor(accentColor);

	//clear
	tex_.clear(backgroundColor);

	//draw to tex
	for (size_t i = 0; i < bars.size(); i++)
	{
		tex_.draw(bars[i]);
		tex_.draw(amtTxts[i]);
		tex_.draw(independentTxts[i]);
	}

	for (size_t i = 0; i < yTicks.size(); i++)
	{
		tex_.draw(yTicks[i]);
		tex_.draw(dependentTxts[i]);
	}

	tex_.draw(verticalAxis);
	tex_.draw(horizontalAxis);
	
	//flush to sprite
	tex_.display();
}