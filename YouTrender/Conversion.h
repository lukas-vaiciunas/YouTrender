#pragma once

#include <string>

namespace Conversion
{
	//String to template type
	template<typename T>
	static T stot(const std::string &str);

	//Stot specializations
	template<> static std::string	stot<std::string>	(const std::string &str);
	template<> static unsigned char	stot<unsigned char>	(const std::string &str);
	template<> static unsigned int	stot<unsigned int>	(const std::string &str);
	template<> static bool			stot<bool>			(const std::string &str);
};

template<typename T>
T Conversion::stot(const std::string &str)
{
	return T();
}

template<>
std::string Conversion::stot(const std::string &str)
{
	return str;
}

template<>
unsigned char Conversion::stot<unsigned char>(const std::string &str)
{
	return static_cast<unsigned char>(std::stoul(str));
}

template<>
unsigned int Conversion::stot<unsigned int>(const std::string &str)
{
	return static_cast<unsigned int>(std::stoul(str));
}

template<>
bool Conversion::stot<bool>(const std::string &str)
{
	/*std::string newStr = "";

	for (size_t i = 0; i < str.length(); i++)
		newStr += std::toupper(str[i]);

	return newStr.compare("TRUE") == 0;*/

	return str[0] == 'T';
}