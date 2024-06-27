#include "Environment.h"


Environment::Environment(const Config& config)
	:
	config_(config),
	numCreatures_(config_.numCreatures_)
{
	newGeneration();
}

bool Environment::isFree(int x, int y)
{
	if (x >= 0 && y >= 0 && x < config_.envSize_ && y < config_.envSize_)
	{
		return habitat_[x][y] == nullptr || habitat_[x][y]->isKilled();
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
		if (!creature.isKilled())
		{
			creature.step();
		}
		
	}
}

void Environment::newGeneration()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<Creature> oldGen = std::move(creatures_);
	creatures_.clear();
	oldGen.erase(std::remove_if(oldGen.begin(), oldGen.end(), [](Creature& x) {
		return x.isKilled();
		}), oldGen.end());
	habitat_.clear();
	habitat_.resize(config_.envSize_);
	for (int i = 0; i < config_.envSize_; ++i)
	{
		habitat_[i].resize(config_.envSize_, nullptr);
	}
	auto iotaRange = std::views::iota(0, static_cast<int>(pow(config_.envSize_, 2)));
	std::vector<int> positions(std::ranges::begin(iotaRange), std::ranges::end(iotaRange));
	std::shuffle(positions.begin(), positions.end(), gen);
	if (oldGen.size() != 0)
	{
		std::uniform_int_distribution<> dis(0, oldGen.size() - 1);
		for (int i : positions | std::views::take(config_.numCreatures_))
		{
			auto pos = std::div(i, config_.envSize_);
			int firstCreatureIndex = dis(gen);
			int secondCreatureIndex = dis(gen);
			creatures_.push_back(oldGen[firstCreatureIndex].breed(oldGen[secondCreatureIndex], { pos.rem,pos.quot }));
		}
	}
	else
	{
		for (int i : positions | std::views::take(config_.numCreatures_))
		{
			auto pos = std::div(i, config_.envSize_);
			creatures_.emplace_back(std::make_pair(pos.rem,pos.quot), &config_, this);
		}
	}
	std::uniform_real_distribution mutRate;
	for (auto&& creature : creatures_)
	{
		if (mutRate(gen) > config_.mutRate_)
		{
			creature.mutate();
		}
		auto [x, y] = creature.getPosition();
		habitat_[x][y] = &(creature);
		creature.buildBrain();
	}
}

void Environment::killCreatures()
{
	if (config_.envType_ == "Square Killzone")
	{
		killSquare(config_.killZoneSize_);
	}
	else if (config_.envType_ == "West Killzone")
	{
		killWest(config_.killZoneSize_);
	}
	else if (config_.envType_ == "North Killzone")
	{
		killNorth(config_.killZoneSize_);
	}
	else if (config_.envType_ == "Dense Killzone")
	{
		killDense(config_.killZoneSize_);
	}
}

const std::vector<std::vector<Creature*>>& Environment::getHabitat() const
{
	return habitat_;
}

void Environment::killSquare(std::size_t size)
{
	for (auto&& creature : creatures_)
	{
		auto [x, y] = creature.getPosition();
		int survivalLimit = (config_.envSize_ - size) / 2;
		if (x > survivalLimit && x < config_.envSize_ - survivalLimit && y > survivalLimit && y < config_.envSize_ - survivalLimit)
		{
			creature.die();
		}
	}
}

void Environment::killWest(std::size_t size)
{
	for (auto&& creature : creatures_)
	{
		auto x = creature.getPosition().first;
		if (x < size)
		{
			creature.die();
		}
	}
}

void Environment::killNorth(std::size_t size)
{
	for (auto&& creature : creatures_)
	{
		auto y = creature.getPosition().second;
		if (y < size)
		{
			creature.die();
		}
	}
}

void Environment::killDense(std::size_t size)
{
	for (auto&& creature : creatures_)
	{
		if (!creature.isKilled())
		{
			auto [x_pos, y_pos] = creature.getPosition();
			for (auto x : std::views::iota(std::max(0, (int)(x_pos - size)), std::min((int)config_.envSize_, (int)(x_pos + size + 1))))
			{
				for (auto y : std::views::iota(std::max(0, (int)(y_pos - size)), std::min((int)config_.envSize_, (int)(y_pos + size + 1))))
				{
					if (habitat_[x][y] != nullptr && (x!=x_pos || y!=y_pos))
					{
						creature.die();
						habitat_[x][y]->die();
					}
				}
			}
		}
	}
}

