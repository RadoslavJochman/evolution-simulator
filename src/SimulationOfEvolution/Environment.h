#pragma once
#include "Neurons.h"
#include "Creature.h"
#include "utilites.h"


class Environment
{

public:
	Environment(const Config& config) :
		numCreatures_(config.numCreatures_)
	{
		for (auto&& pos : habitat_)
		{
			std::fill(pos.begin(), pos.end(), nullptr);
		}
		auto iotaRange = std::views::iota(0, config.envSize_**2);
		std::vector<int> positions(iotaRange.begin(), iotaRange.end());
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(positions.begin(), positions.end(), g);
		for (int i : positions | std::views::take(numCreature))
		{
			auto pos = std::div(i, config.envSize_);
			creatures_.push_back(Creature({pos.rem,pos.quot}, config));
			habitat_[pos.rem][pos.quot] = creatures_.back();
		}
	}

private:
	std::size_t numCreatures_;
	std::vector<Creature> creatures_;
	std::vector<std::vector<Creature*>> habitat_;
};