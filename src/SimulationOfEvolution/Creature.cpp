#pragma once
#include "Creature.h"

void Creature::createGenome(std::size_t numOfGenes)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 15);

	for (auto&& i : std::ranges::iota_view<std::size_t, std::size_t>{ 0,numOfGenes })
	{
		std::stringstream gene;
		for (auto&& j : std::ranges::iota_view{ 0,8 })
		{
			int randNumb = dis(gen);
			gene << std::hex << randNumb;
		}
		genome.push_back(gene.str());
	}

}
