#pragma once

#include <fstream>
#include <map>
#include <unordered_map>
#include <limits>
#include "VideoData.h"
#include "Conversion.h"

class Loader
{
private:
	//String parsing
	std::vector<std::string> splitString(const std::string &str) const;

	//Skips to the next line in an input stream
	void skipLine(std::istream &is) const;

	std::pair<std::string, std::string> readLinePairs(std::istream &is, VideoData::CATEGORY keyCategory, VideoData::CATEGORY valueCategory) const;
public:
	Loader() {}

	/*
		Loads all data present in the specified file into a vector of
		VideoData objects (see VideoData.h)

		Slow -- takes about a minute to load 50,000 data
	*/
	std::vector<VideoData> loadAll(const char *filePath) const;

	/*
		Loads values under the specified columns into an unordered map

		Pretty fast -- takes about 10 seconds to load 50,000 data (with <string,uint>).
		This can be optimized by defining a template specilization for string keys
		that creates an unordered map that maps string keys to unique IDs
	*/
	template <typename K, typename V>
	std::unordered_map<K, V> loadPairs(const char *filePath, VideoData::CATEGORY keyCategory, VideoData::CATEGORY valueCategory) const;

	/*
		Keeps track of the amount of data under the specified countedCategory for
		each keyCategory. For instance, if 'category_id' is specified as the keyCategory
		and 'likes' is specified as the countedCategory, this function will return
		a map of the total number of likes for each category.

		Note: To receive accurate results, there should not be any duplicate
		video IDs in the data set.
	*/
	template<typename Structure>
	void loadCountPairs(Structure &structure, const char *filePath, VideoData::CATEGORY keyCategory, VideoData::CATEGORY countedCategory) const;
};

template <typename K, typename V>
std::unordered_map<K, V> Loader::loadPairs(const char *filePath, VideoData::CATEGORY keyCategory, VideoData::CATEGORY valueCategory) const
{
	std::unordered_map<K, V> videos;
	std::ifstream inFile;

	inFile.open(filePath);

	if (!inFile.is_open())
		return videos;

	this->skipLine(inFile);

	while (inFile.peek() != EOF)
	{
		std::pair<std::string, std::string> p = this->readLinePairs(inFile, keyCategory, valueCategory);
		
		videos.emplace(Conversion::stot<K>(p.first), Conversion::stot<V>(p.second));
	}

	inFile.close();

	return videos;
}

template<typename Structure>
void Loader::loadCountPairs(Structure &structure, const char *filePath, VideoData::CATEGORY keyCategory, VideoData::CATEGORY countedCategory) const
{
	std::ifstream inFile;

	typedef typename Structure::key_type KeyType;
	typedef typename Structure::mapped_type ValueType;

	inFile.open(filePath);

	if (!inFile.is_open())
		return;

	this->skipLine(inFile);

	while (inFile.peek() != EOF)
	{
		std::pair<std::string, std::string> p = this->readLinePairs(inFile, keyCategory, countedCategory);

		KeyType key = Conversion::stot<KeyType>(p.first);
		ValueType value = Conversion::stot<ValueType>(p.second);

		if (structure.find(key) == structure.cend())
			structure.emplace(key, value);
		else structure[key] += value;
	}

	inFile.close();
}