#include "Environment.h"


Environment::Environment(const Config& config)
	:
	numCreatures_(config.numCreatures_),
	config_(config)
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
		creatures_.push_back(Creature({ pos.rem,pos.quot }, config, *this));
		habitat_[pos.rem][pos.quot] = &(creatures_.back());
	}
}
bool Environment::isFree(int x, int y)
{
	if (x >= 0 && y >= 0 && x < config_.envSize_ && y < config_.envSize_)
	{
		return habitat_[x][y] == nullptr;
	}
	else return false;
	
}
void Environment::moveCreature(std::size_t x, std::size_t y, std::size_t new_x, std::size_t new_y)
{
	habitat_[new_x][new_y] = habitat_[x][y];
	habitat_[x][y] = nullptr;
}

