#include "Loader.h"
#include <iostream>

std::vector<std::string> Loader::splitString(const std::string &str) const
{
	std::vector<std::string> tokens;
	bool inQuotes = false;

	tokens.push_back("");

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '\"')
			inQuotes = !inQuotes;

		else if (!inQuotes && str[i] == ',')
			tokens.push_back("");

		else tokens.back() += str[i];
	}

	return tokens;
}

void Loader::skipLine(std::istream &is) const
{
	is.ignore(INT_MAX, '\n');
}

std::pair<std::string, std::string> Loader::readLinePairs(std::istream &is, VideoData::CATEGORY keyCategory, VideoData::CATEGORY valueCategory) const
{
	char c;
	bool inQuotes = false;
	unsigned int numCommas = 0;
	bool readKey = (keyCategory == 0);
	bool readValue = (valueCategory == 0);
	std::string keyInput = "";
	std::string valueInput = "";

	while (is >> std::noskipws >> c)
	{
		if (c == '\"')
			inQuotes = !inQuotes;

		else if (!inQuotes && c == ',')
		{
			numCommas++;

			if (readKey)
			{
				readKey = false;
				if (numCommas > valueCategory)
				{
					this->skipLine(is);
					break;
				}
			}
			else if (numCommas == keyCategory)
				readKey = true;

			if (readValue)
			{
				readValue = false;
				if (numCommas > keyCategory)
				{
					this->skipLine(is);
					break;
				}
			}
			else if (numCommas == valueCategory)
				readValue = true;
		}

		else if (readKey)
			keyInput += c;

		else if (readValue)
			valueInput += c;
	}

	return std::make_pair(keyInput, valueInput);
}

std::vector<VideoData> Loader::loadAll(const char *filePath) const
{
	std::vector<VideoData> videos;

	std::ifstream inFile;
	std::string inputLine = "";
	std::vector<std::string> parsed;

	inFile.open(filePath);

	if (!inFile.is_open())
		return videos;

	this->skipLine(inFile);

	/*std::getline(inFile, inputLine);

	std::cout << inputLine << std::endl;
	std::vector<std::string> parsed = this->splitString(inputLine);
	for (const std::string &str : parsed)
		std::cout << str << std::endl;*/

	while (inFile.peek() != EOF)
	{
		std::getline(inFile, inputLine);
		videos.push_back(VideoData(this->splitString(inputLine)));
	}

	inFile.close();

	return videos;
}