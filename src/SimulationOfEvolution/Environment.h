#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "Neurons.h"
#include "Creature.h"
#include "utilites.h"
#include <ranges>
#include <cmath>

class Environment
{

public:
	Environment(const Config& config);
	bool isFree(int x, int y);
	void moveCreature(std::size_t x, std::size_t y, std::size_t new_x, std::size_t new_y);
private:
	const Config& config_;
	std::size_t numCreatures_;
	std::vector<Creature> creatures_;
	std::vector<std::vector<Creature*>> habitat_;
};
#endif