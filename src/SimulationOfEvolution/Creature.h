#pragma once
#include <string>
#include <random>
#include <ranges>
#include <sstream>
#include <vector>
class Creature
{
	std::vector<std::string> genome;

private:
	void createGenome(std::size_t numOfGenes);
	void buildBrain();
};
