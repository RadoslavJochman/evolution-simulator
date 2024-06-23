#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "Neurons.h"
#include "Creature.h"
#include "utilities.h"
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
	/**
	* @brief Returns true if there is no creature at [x,y] or if the creature is dead
	*/
	bool isFree(int x, int y);
	/**
	 * @brief Moves creature to new position in habitat
	 */
	void moveCreature(std::size_t x, std::size_t y, std::size_t new_x, std::size_t new_y);
	/**
	* @brief Returns vector of creatures
	*/
	const std::vector<Creature>& getCreatures() const;
	/**
	 * @brief Makes every creature that is not dead make a move
	 */
	void step();
	/**
	 * @brief Generates new generation either by breeding existing population or by creating new random population
	 */
	void newGeneration();
	/**
	 * @brief Kills creature based on the environment type
	 */
	void killCreatures();
	/**
	 * @brief Returns pointer to habitat
	 */
	const std::vector<std::vector<Creature*>>* getHabitat() const;
private:
	/**
	 * @brief Kills all creatures that are in square area in the center of the habitat
	 */
	void killSquare(std::size_t size);
	/**
	 * @brief Kills all creatures that are close to the left border
	 */
	void killWest(std::size_t size);
	/**
	 * @brief Kills all creatures that are close to the top border
	 */
	void killNorth(std::size_t size);
	/**
	 * @brief Kills all creatures that are surrounded by other creature
	 */
	void killDense(std::size_t size);
	const Config* config_;
	std::size_t numCreatures_;
	std::vector<Creature> creatures_;
	std::vector<std::vector<Creature*>> habitat_;
};
#endif