#pragma once

#include <unordered_map>
#include <queue>
#include "Visual.h"

class BarChart : public Visual
{
private:
	static std::vector<sf::Color> colors_;

	std::queue<size_t> unusedColors_;

	std::string newlineify(const std::string &str);
	void updateOutput(const std::vector<std::pair<std::string, unsigned int>> &data);
public:
	BarChart(unsigned int width, unsigned int height, const std::vector<std::pair<std::string, unsigned int>> &data);
};