#pragma once
#include <vector>
#include <memory>
#include "Environment.h"
#include <iostream>




class SensorNeuron
{
protected:
	Environment* my_env;
public:
	virtual float getActivation() = 0;
};

class InternalNeuron
{
	std::vector<InternalNeuron*> interInputs;
	std::vector<SensorNeuron*> inputs;
	float bias;

public:
	InternalNeuron();
	float getActivation();
};


class AgeNeuron: SensorNeuron
{
	std::vector<double> connectionWeights;
	double maxOutput;
	double minOutput;
public:
	AgeNeuron();
	float getActivation() override;
};

class ActionNeuron
{
	ActionNeuron();
	double activationTreshold;
	Environment* my_env;
};