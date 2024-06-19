#pragma once
#include <vector>
#include <memory>
#include <ranges>
#include <iostream>

enum class ActionNeuronTypes { MFR, Mrn, MRL, Mx, My, Kill, UNKNOWN };
enum class SensorNeuronTypes { Age, Rnd, BDy, BDx, BD, Lx, Ly, Osc, UNKNOWN };

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
	float getActivation();
};

class ActionNeuron
{
public:
	std::vector<InternalNeuron*> interInputs_;
	std::vector<SensorNeuron*> sensorInputs_;
	std::vector<int> sensorWeights_;
	std::vector<int> interWeights_;
	double activationTreshold_;
};

class AgeNeuron: public SensorNeuron
{
public:
	float getActivation() override;
};

class RndNeuron : public SensorNeuron
{
	float getActivation() override;
};

class BDyNeuron : public SensorNeuron
{
	float getActivation() override;
};

class BDxNeuron : public SensorNeuron
{
	float getActivation() override;
};

class BDNeuron : public SensorNeuron
{
	float getActivation() override;
};

class LxNeuron : public SensorNeuron
{
	float getActivation() override;
};

class LyNeuron : public SensorNeuron
{
	float getActivation() override;
};

class OscNeuron : public SensorNeuron
{
	float getActivation() override;
};

class MFRNeuron : public ActionNeuron
{

};

class MrnNeuron : public ActionNeuron
{

};

class MRLNeuron : public ActionNeuron
{

};

class MxNeuron : public ActionNeuron
{

};

class MyNeuron : public ActionNeuron
{

};

class KillNeuron : public ActionNeuron
{

};