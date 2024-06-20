#ifndef NEURONS_H
#define NEURONS_H
#include <vector>
#include <memory>
#include <ranges>
#include <iostream>
#include "Creature.h"

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
	virtual void step() = 0;
	ActionNeuron(Creature* owner, double activationTreshold)
		:
		owner_(owner),
		activationTreshold_(activationTreshold) {}
protected:
	Creature* owner_;
	std::vector<InternalNeuron*> interInputs_;
	std::vector<SensorNeuron*> sensorInputs_;
	std::vector<int> sensorWeights_;
	std::vector<int> interWeights_;
	double activationTreshold_;
	double getActivation();
};

class AgeNeuron : public SensorNeuron
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
	void step() override;
};

class MrnNeuron : public ActionNeuron
{
	void step() override;
};

class MRLNeuron : public ActionNeuron
{
	void step() override;
};

class MxNeuron : public ActionNeuron
{
	void step() override;
};

class MyNeuron : public ActionNeuron
{
	void step() override;
};

class KillNeuron : public ActionNeuron
{
	void step() override;
};
#endif