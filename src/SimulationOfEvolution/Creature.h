#pragma once
#include <string>
#include <random>
#include <ranges>
#include <sstream>
#include <vector>
#include <map>
#include "Neurons.h"

enum class ActionNeuronTypes { MFR, Mrn, MRL, Mx, My, Kill, size};
enum class SensorNeuronTypes { Age, Rnd, BDy, BDx, BD, Lx, Ly, Osc, size};

class Creature
{
public:
	std::vector<std::string> genome_;
	std::map<SensorNeuronTypes, std::unique_ptr<SensorNeuron>> sensorBrain_;
	std::map<int, InternalNeuron> internalBrain_;
	std::map<ActionNeuronTypes, std::unique_ptr<ActionNeuron>> actionBrain_;
	std::pair<std::size_t, std::size_t> pos_;
	Creature(std::size_t numGenes, std::pair<std::size_t, std::size_t> pos);
private:
	size_t maxNumInternal_;
	void createGenome(std::size_t numOfGenes);
	void buildBrain();
	void addSensorNeuron(SensorNeuronTypes type);
	void addActionNeuron(ActionNeuronTypes type);
	void createConnection(char sourceType, char endType, int sourceID, int endID, int weight);
};
