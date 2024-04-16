#pragma once
#include <string>
#include <random>
#include <ranges>
#include <sstream>
#include <vector>
#include <map>
#include "Neurons.h"

enum class ActionNeuronTypes { MFR, Mrn, MRL, Mx, My, Kill, size};
enum class SensorNeuronTypes { Age, Rnd, BDy, BD, Lx, Ly, Osc, size};

class Creature
{
	std::vector<std::string> genome;
	std::map<SensorNeuronTypes, std::unique_ptr<SensorNeuron>> sensorBrain;
	std::map<int, InternalNeuron> internalBrain;
	std::map<ActionNeuronTypes, std::unique_ptr<ActionNeuron>> actionBrain;
private:
	void createGenome(std::size_t numOfGenes);
	void buildBrain();
	void addSensorNeuron(SensorNeuronTypes type);
	void addActionNeuron(ActionNeuronTypes type);
};
