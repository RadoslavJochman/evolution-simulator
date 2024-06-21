#include "Environment.h"


Environment::Environment(const Config* config)
	:
	config_(config),
	numCreatures_(config->numCreatures_)
{
	habitat_.resize(config->envSize_);
	for (int i = 0; i < config->envSize_; ++i)
	{
		habitat_[i].resize(config->envSize_, nullptr);
	}
	auto iotaRange = std::views::iota(0, static_cast<int>(pow(config->envSize_, 2)));
	std::vector<int> positions(std::ranges::begin(iotaRange), std::ranges::end(iotaRange));
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(positions.begin(), positions.end(), g);
	creatures_.resize(config->numCreatures_);
	std::size_t counter = 0;
	for (int i : positions | std::views::take(config->numCreatures_))
	{
		auto pos = std::div(i, config->envSize_);
		creatures_[counter] = Creature({ pos.rem,pos.quot }, config, this);
		counter++;
		habitat_[pos.rem][pos.quot] = &(creatures_.back());
	}
	for (auto&& creature : creatures_)
	{
		creature.buildBrain();
	}
}
bool Environment::isFree(int x, int y)
{
	if (x >= 0 && y >= 0 && x < config_->envSize_ && y < config_->envSize_)
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

const std::vector<Creature>& Environment::getCreatures() const
{
	return creatures_;
}

void Environment::step()
{
	for (auto&& creature : creatures_)
	{
		creature.step();
	}
}

