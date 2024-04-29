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

	std::vector<InternalNeuron*> interInputs_;
	std::vector<SensorNeuron*> sensorInputs_;
	std::vector<int> sensorWeights_;
	std::vector<int> interWeights_;

	InternalNeuron();
	float getActivation();
};

class ActionNeuron
{
public:
	std::vector<InternalNeuron*> interInputs_;
	std::vector<SensorNeuron*> sensorInputs_;
	std::vector<int> sensorWeights_;
	std::vector<int> interWeights_;
	ActionNeuron();
	double activationTreshold_;
};

class AgeNeuron: SensorNeuron
{
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