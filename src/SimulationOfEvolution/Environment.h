#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "Neurons.h"
#include "Creature.h"
#include "utilites.h"
#include <ranges>
#include <cmath>

enum class ActionNeuronTypes;
enum class SensorNeuronTypes;
class SensorNeuron;
class Creature;

class Environment
{

public:
	Environment(const Config* config);
	bool isFree(int x, int y);
	void moveCreature(std::size_t x, std::size_t y, std::size_t new_x, std::size_t new_y);
	const std::vector<Creature>& getCreatures() const;
	void step();
	void newGeneration();
	void killCreatures();
	const std::vector<std::vector<Creature*>>* getHabitat() const;
private:
	const Config* config_;
	std::size_t numCreatures_;
	std::vector<Creature> creatures_;
	std::vector<std::vector<Creature*>> habitat_;
	void killSquare(std::size_t size);
	void killWest(std::size_t size);
	void killSouth(std::size_t size);
	void killDense(std::size_t size);
};
#endif