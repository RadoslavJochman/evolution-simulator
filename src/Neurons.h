#ifndef NEURONS_H
#define NEURONS_H
#include <vector>
#include <memory>
#include <ranges>
#include <iostream>
#include <random>
enum class ActionNeuronTypes;
enum class SensorNeuronTypes; 
class Creature;


class SensorNeuron
{
public:
	virtual double getActivation() const = 0;
	virtual ~SensorNeuron() = default;
};

class InternalNeuron
{
public:
	double getActivation() const;
	void createConnection(double weight, SensorNeuron* source);
protected:
	std::vector<SensorNeuron*> sensorInputs_;
	std::vector<double> sensorWeights_;
};

class ActionNeuron
{
public:
	virtual void step() = 0;
	virtual ~ActionNeuron() = default;
	/**
	* @brief Creates connection between internal and action neuron
	*/
	void createConnection(int weight, InternalNeuron* source);
	/**
	 * @brief Creates connection between sensor and action neuron
	 */
	void createConnection(int weight, SensorNeuron* source);
	ActionNeuron(Creature& owner, int activationTreshold);
protected:
	Creature& owner_;
	std::vector<InternalNeuron*> interInputs_;
	std::vector<SensorNeuron*> sensorInputs_;
	std::vector<double> sensorWeights_;
	std::vector<double> interWeights_;
	int activationThreshold_;
	/**
	 * @brief Calculates activation of the action neuron
	 */
	double getActivation() const;
};

class RndNeuron : public SensorNeuron
{
public:
	/**
	 * @brief Returns random number
	 */
	double getActivation() const override;
};

class BDyNeuron : public SensorNeuron
{
public:
	/**
	 * @brief Returns distance from north/south border
	 */
	double getActivation() const override;
	BDyNeuron(const Creature& owner);
	const Creature& owner_;
};

class BDxNeuron : public SensorNeuron
{
public:
	/**
	 * @brief Returns distance from east/west border
	 */
	double getActivation() const override;
	BDxNeuron(const Creature& owner);
private:
	const Creature& owner_;
};

class BDNeuron : public SensorNeuron
{
public:
	/**
	 * @brief Returns neares border distance
	 */
	double getActivation() const override;
	BDNeuron(const Creature& owner);
private:
	const Creature& owner_;
};

class LxNeuron : public SensorNeuron
{
public:
	/**
	 * @brief Returns neares border distance
	 */
	double getActivation() const override;
	LxNeuron(const Creature& owner);
private:
	const Creature& owner_;
};

class LyNeuron : public SensorNeuron
{
public:
	/**
	 * @brief Returns y location
	 */
	double getActivation() const override;
	LyNeuron(const Creature& owner);
private:
	const Creature& owner_;
};

class DensNeuron : public SensorNeuron
{
public:
	/**
	 * @brief Returns density of population in radius 2
	 */
	double getActivation() const override;
	DensNeuron(const Creature& owner);
private:
	const Creature& owner_;
};

class MFRNeuron : public ActionNeuron
{
public:
	MFRNeuron(Creature& owner, int activationTreshold);
	/**
	 * @brief Moves forward or backward based on activation
	 */
	void step() override;
};

class MrnNeuron : public ActionNeuron
{
public:
	MrnNeuron(Creature& owner, int activationTreshold);
	/**
	 * @brief Moves in random driection
	 */
	void step() override;
};

class MRLNeuron : public ActionNeuron
{
public:
	MRLNeuron(Creature& owner, int activationTreshold);
	/**
	 * @brief Moves right or left based on activation
	 */
	void step() override;
};

class MxNeuron : public ActionNeuron
{
public:
	MxNeuron(Creature& owner, int activationTreshold);
	/**
	 * @brief Moves along x axis
	 */
	void step() override;
};

class MyNeuron : public ActionNeuron
{
public:
	MyNeuron(Creature& owner, int activationTreshold);
	/**
	 * @brief Moves along y axis
	 */
	void step() override;
};

class KillNeuron : public ActionNeuron
{
public:
	KillNeuron(Creature& owner, int activationTreshold);
	/**
	 * @brief Kills creature infront
	 */
	void step() override;
};
#endif
