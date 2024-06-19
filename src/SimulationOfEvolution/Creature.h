#pragma once
#include <string>
#include <random>
#include <ranges>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Neurons.h"



class Creature
{
public:
	Creature(std::pair<std::size_t, std::size_t>&& pos, const Config& config);
private:
	Config config_;
	std::vector<std::string> genome_;
	std::unordered_map<SensorNeuronTypes, std::unique_ptr<SensorNeuron>> sensorBrain_;
	std::unordered_map<int, InternalNeuron> internalBrain_;
	std::unordered_map<ActionNeuronTypes, std::unique_ptr<ActionNeuron>> actionBrain_;
	std::pair<std::size_t, std::size_t> pos_;
	void createGenome();
	void buildBrain();
	void addSensorNeuron(SensorNeuronTypes type);
	void addActionNeuron(ActionNeuronTypes type);
	void createConnection(char sourceType, char endType, int sourceID, int endID, int weight);
};
