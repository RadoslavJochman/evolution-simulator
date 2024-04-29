#pragma once
#include "Neurons.h"
#include "Creature.h"



template<std::size_t size>
class Environment
{

public:
	Environment(std::size_t numCreature, std::size_t numGenes) :
		numCreatures_(numCreature)
	{
		for (auto&& pos : habitat_)
		{
			std::fill(pos.begin(), pos.end(), nullptr);
		}
		auto iotaRange = std::views::iota(0, size**2);
		std::vector<int> positions(iotaRange.begin(), iotaRange.end());
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(positions.begin(), positions.end(), g);
		for (int i : positions | std::views::take(numCreature))
		{
			auto pos = std::div(i, size);
			creatures_.push_back(Creature(numGenes, {pos.rem,pos.quot}));
			habitat_[pos.rem][pos.quot] = creatures_.back();
		}
	}

private:
	std::size_t numCreatures_;
	std::vector<Creature> creatures_;
	std::array<std::array<Creature*, size>, size> habitat_;
};