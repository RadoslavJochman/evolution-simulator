#pragma once
#include <vector>
#include <memory>
#include <ranges>
#include <iostream>

class SensorNeuron
{
protected:
public:
	virtual float getActivation() = 0;
};

class InternalNeuron
{
public:

	std::vector<InternalNeuron*> interInputs;
	std::vector<SensorNeuron*> sensorInputs;
	std::vector<int> sensorWeights;
	std::vector<int> interWeights;

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

class RndNeuron : SensorNeuron
{

};

class BDyNeuron : SensorNeuron
{

};

class BDxNeuron : SensorNeuron
{

};

class BDNeuron :SensorNeuron
{

};

class LxNeuron : SensorNeuron
{

};

class LyNeuron : SensorNeuron
{

};

class OscNeuron : SensorNeuron
{

};

class ActionNeuron
{
public:
	std::vector<InternalNeuron*> interInputs;
	std::vector<SensorNeuron*> sensorInputs;
	std::vector<int> sensorWeights;
	std::vector<int> interWeights;
	ActionNeuron();
	double activationTreshold;
};

class MFRNeuron : ActionNeuron
{

};

class MrnNeuron : ActionNeuron
{

};

class MRLNeuron : ActionNeuron
{

};

class MxNeuron : ActionNeuron
{

};

class MyNeuron : ActionNeuron
{

};

class KillNeuron : ActionNeuron
{

};