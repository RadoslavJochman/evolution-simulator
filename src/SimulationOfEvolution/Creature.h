#ifndef CREATURE_H
#define CREATURE_H
#include <string>
#include <random>
#include <ranges>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <array>
#include "Neurons.h"
#include "utilities.h"
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
	Creature(std::pair<int, int>&& pos, const Config* config, Environment* myEnv);
	Creature(std::pair<int, int>&& pos, const Config* config, Environment* myEnv, std::vector<std::string>&& genome);
	Creature();
	/**
	 * @brief Evaluates all neurons of the creature and performs actions
	 */
	void step();
	/**
	 * @brief Moves creature right or left with respect to its direction
	 */
	void moveRight(const std::pair<int, int>& direction);
	/**
	* @brief Moves creature up or down with respect to its direction
	*/
	void moveForward(const std::pair<int, int>& direction);
	/**
	 * @brief Moves creature in given direction
	 */
	void updatePosition(const std::pair<int, int>& direction);
	/**
	 * @brief Returns position of the creature
	 */
	const std::pair<int, int>& getPosition() const;
	/**
	 * @brief Add neurons based on the genome and creates connections between them based on the genome as well
	 */
	void buildBrain();
	/**
	* @brief Calculates RBG color of the creature based on its genome
	*/
	const std::array<std::size_t,3> getColor() const;
	/**
	 * @brief Kills the creature
	 */
	void die();
	/**
	 * @brief Returns true if the creature is dead otherwise returns false
	 */
	bool isKilled() const;
	/**
	 * @brief Combines genomes of two creatures and returns new creature with this genome
	 */
	Creature breed(const Creature& c1, std::pair<int, int>&& pos);
	/**
	 * @brief Mutates one random digit in random gene
	 */
	void mutate();
	/**
	 * @brief Returns pointer to creature`s environment
	 */
	const Environment* getEnv() const;
	/**
	* @brief Returns creature`s direction
	*/
	const std::pair<int, int> getDirection() const;
	Creature(const Creature&) = delete;
	Creature& operator=(const Creature&) = delete;
	Creature(Creature&&) noexcept = default;
	Creature& operator=(Creature&&) noexcept = default;
	const Config* config_;
private:
	/**
	 * @brief Creates random genome, each gene is represented by hexadecimal number with 8 digits
	 */
	void createGenome();
	/**
	 * @brief Inserts sensor neuron in sensor brain of the creature
	 */
	void addSensorNeuron(SensorNeuronTypes type);
	/**
	 * @brief Inserts action neuron in action brain of the creature
	 */
	void addActionNeuron(ActionNeuronTypes type, int activationThreshold);
	/**
	 * @brief Creates connection between two neurons with given weight
	 */
	void createConnection(char sourceType, char endType, int sourceID, int endID, int weight);
	bool killed;
	Environment* myEnv_;
	std::vector<std::string> genome_;
	std::unordered_map<SensorNeuronTypes, std::unique_ptr<SensorNeuron>> sensorBrain_;
	std::unordered_map<std::size_t, InternalNeuron> internalBrain_;
	std::unordered_map<ActionNeuronTypes, std::unique_ptr<ActionNeuron>> actionBrain_;
	std::pair<int, int> pos_;
	std::pair<int, int> direction_;

};
#endif