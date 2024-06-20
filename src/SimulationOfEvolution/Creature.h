#ifndef CREATURE_H
#define CREATURE_H
#include <string>
#include <random>
#include <ranges>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Neurons.h"
#include "utilites.h"
#include "Environment.h"

enum class ActionNeuronTypes;
enum class SensorNeuronTypes;
class InternalNeuron;
class ActionNeuron;
class SensorNeuron;
class Environment;

class Creature
{
public:
	Creature(std::pair<std::size_t, std::size_t>&& pos, const Config& config, Environment& myEnv);
	Creature(const Creature&) = delete;
	Creature& operator=(const Creature&) = delete;
	Creature(Creature&&) noexcept = default;
	Creature& operator=(Creature&&) noexcept = default;
	void step();
	void moveRight(const std::pair<int, int>& direction);
	void moveForward(const std::pair<int, int>& direction);
	void updatePosition(const std::pair<int, int>& direction);
	const std::pair<std::size_t, std::size_t>& getPosition() const;
private:
	Environment& myEnv_;
	const Config& config_;
	std::vector<std::string> genome_;
	std::unordered_map<SensorNeuronTypes, std::unique_ptr<SensorNeuron>> sensorBrain_;
	std::unordered_map<std::size_t, InternalNeuron> internalBrain_;
	std::unordered_map<ActionNeuronTypes, std::unique_ptr<ActionNeuron>> actionBrain_;
	std::pair<std::size_t, std::size_t> pos_;
	std::pair<int, int> direction_;
	void createGenome();
	void buildBrain();
	void addSensorNeuron(SensorNeuronTypes type);
	void addActionNeuron(ActionNeuronTypes type);
	void createConnection(char sourceType, char endType, int sourceID, int endID, int weight);
};
#endif