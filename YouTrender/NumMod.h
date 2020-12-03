#pragma once

#include <unordered_map>
#include <string>

template<typename T>

class NumMod
{
private:
	enum PLACE : uint8_t
	{
		THOUSAND,
		MILLION,
		BILLION,
		TRILLION,
		QUADRILLION,
		QUINTILLION
	};

	static std::unordered_map<uint8_t, char> placeMap_;
public:
	NumMod() {}

	std::string toShorthand(T val) const;

	T roundUp(T val) const;
};

template<typename T>
std::unordered_map<uint8_t, char> NumMod<T>::placeMap_ =
std::unordered_map<uint8_t, char>
{
	{ THOUSAND, 'K' },
	{ MILLION, 'M' },
	{ BILLION, 'B' },
	{ TRILLION, 'T' },
	{ QUADRILLION, 'P' },
	{ QUINTILLION, 'E' }
};

template<typename T>
std::string NumMod<T>::toShorthand(T val) const
{
	if (val == T())
		return std::to_string(T());

	uint8_t place = 0;
	T old = val;
	std::string prefix = "";

	val /= 1000U;

	while (val / 1000U > 0)
	{
		val /= 1000U;
		place++;
	}

	prefix = std::to_string(val);

	if (place != 0 && prefix.length() == 1)
	{
		char addon = std::to_string(old / 1000U * (place - 1))[1];

		if (addon >= 49 && addon <= 57)
		{
			prefix.push_back('.');
			prefix.push_back(addon);
		}
	}

	return prefix + (place == 0 ? char() : placeMap_[place]);
}

template<typename T>
T NumMod<T>::roundUp(T val) const
{
	T coefficient = T();
	T exponent = T();

	while (val / 10U > 0)
	{
		val /= 10U;
		exponent++;
	}

	coefficient = val + 1;

	return static_cast<T>(coefficient * std::pow(10U, exponent));
}