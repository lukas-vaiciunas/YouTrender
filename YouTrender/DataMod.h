#pragma once

#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include "VideoData.h"

template<typename T, typename U>

class DataMod
{
private:
	struct PairSecondMaxComp
	{
		constexpr bool operator()
			(std::pair<T, U> const &lhs, std::pair<T, U> const &rhs)
			const noexcept
		{
			return lhs.second < rhs.second;
		}
	};
public:
	DataMod() {}

	std::vector<std::pair<T, U>> getLargest(const std::unordered_map<T, U> &data, unsigned int num) const;
	std::vector<std::pair<T, U>> getLargest(const std::map<T, U> &data, unsigned int num) const;
	std::vector<std::pair<std::string, U>> keysToStrings(const std::vector<std::pair<T, U>> &data) const;
	std::vector<std::pair<std::string, U>> categoryIdKeysToStrings(const std::vector<std::pair<unsigned int, U>> &data) const;
};

template<typename T, typename U>
std::vector<std::pair<T, U>> DataMod<T, U>::getLargest(const std::unordered_map<T, U> &data, unsigned int num) const
{
	std::priority_queue<std::pair<T, U>, std::vector<std::pair<T, U>>, PairSecondMaxComp> pq;
	std::vector<std::pair<T, U>> result;

	for (auto it = data.cbegin(); it != data.cend(); it++)
		pq.push(std::make_pair(it->first, it->second));

	while (result.size() < num)
	{
		result.push_back(pq.top());
		pq.pop();
	}

	return result;
}

template<typename T, typename U>
std::vector<std::pair<T, U>> DataMod<T, U>::getLargest(const std::map<T, U> &data, unsigned int num) const
{
	std::priority_queue<std::pair<T, U>, std::vector<std::pair<T, U>>, PairSecondMaxComp> pq;
	std::vector<std::pair<T, U>> result;

	for (auto it = data.cbegin(); it != data.cend(); it++)
		pq.push(std::make_pair(it->first, it->second));

	while (result.size() < num)
	{
		result.push_back(pq.top());
		pq.pop();
	}

	return result;
}

template<typename T, typename U>
std::vector<std::pair<std::string, U>> DataMod<T, U>::keysToStrings(const std::vector<std::pair<T, U>> &data) const
{
	std::vector<std::pair<std::string, U>> result;

	for (auto it = data.cbegin(); it != data.cend(); it++)
		result.push_back(std::make_pair(std::to_string(it->first), it->second));

	return result;
}

template<typename T, typename U>
std::vector<std::pair<std::string, U>> DataMod<T, U>::categoryIdKeysToStrings(const std::vector<std::pair<unsigned int, U>> &data) const
{
	std::vector<std::pair<std::string, U>> result;

	for (auto it = data.cbegin(); it != data.cend(); it++)
		result.push_back(std::make_pair(VideoData::categoryIdMap().at(it->first), it->second));

	return result;
}