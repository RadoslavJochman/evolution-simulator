#pragma once
#include <string>
#include <random>
#include <ranges>
#include <sstream>
#include <vector>
#include <map>
#include "Neurons.h"

enum class ActionNeuronsType { MFR, Mrn, MRL, Mx, My, Kill, size};
enum class SensorNeuronsType { Age, Rnd, BDy, BD, Lx, Ly, Osc, size};

class Creature
{
	std::vector<std::string> genome;
	std::map<SensorNeuronsType, SensorNeuron> sensorBrain;
	std::map<int, InternalNeuron> internalBrain;
	std::map<ActionNeuronsType, std::unique_ptr<ActionNeuron>> actionBrain;
private:
	void createGenome(std::size_t numOfGenes);
	void buildBrain();
	void addSensorNeuron(SensorNeuronsType type);
};
