#pragma
#include <string>
#include <sstream>
#include <bitset>

template<std::size_t hexSize>
std::string hexTobin(std::string hexNumber)
{
	std::stringstream ss;
	unsigned tmp;
	ss << hexNumber;
	ss >> tmp;
	return std::bitset<4*hexSize>(tmp).to_string();
}