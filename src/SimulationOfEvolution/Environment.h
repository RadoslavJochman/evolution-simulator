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
		habitat_.resize(config.envSize_);
		for (int i = 0; i < config.envSize_; ++i)
		{
			habitat_[i].resize(config.envSize_, nullptr);
		}
		auto iotaRange = std::views::iota(0, static_cast<int>(pow(config.envSize_, 2)));
		std::vector<int> positions(std::ranges::begin(iotaRange), std::ranges::end(iotaRange));
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(positions.begin(), positions.end(), g);
		for (int i : positions | std::views::take(config.numCreatures_))
		{
			auto pos = std::div(i, config.envSize_);
			creatures_.push_back(Creature({ pos.rem,pos.quot }, config));
			habitat_[pos.rem][pos.quot] = &(creatures_.back());
		}
	}

private:
	std::size_t numCreatures_;
	std::vector<Creature> creatures_;
	std::vector<std::vector<Creature*>> habitat_;
};