#ifndef NEURONS_H
#define NEURONS_H
#include <vector>
#include <memory>
#include <ranges>
#include <iostream>
#include "Creature.h"

enum class ActionNeuronTypes;
enum class SensorNeuronTypes; 
class Creature;


class SensorNeuron
{
public:
	virtual float getActivation() = 0;
};

class InternalNeuron
{
public:
	float getActivation();
	void createConnection(double weight, InternalNeuron* source);
	void createConnection(double weight, SensorNeuron* source);
protected:
	std::vector<InternalNeuron*> interInputs_;
	std::vector<SensorNeuron*> sensorInputs_;
	std::vector<int> sensorWeights_;
	std::vector<int> interWeights_;
};

class ActionNeuron
{
public:
	virtual void step() = 0;
	void createConnection(double weight, InternalNeuron* source);
	void createConnection(double weight, SensorNeuron* source);
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
public:
	MFRNeuron(Creature* owner, double activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};

class MrnNeuron : public ActionNeuron
{
public:
	MrnNeuron(Creature* owner, double activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};

class MRLNeuron : public ActionNeuron
{
public:
	MRLNeuron(Creature* owner, double activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};

class MxNeuron : public ActionNeuron
{
public:
	MxNeuron(Creature* owner, double activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};

class MyNeuron : public ActionNeuron
{
public:
	MyNeuron(Creature* owner, double activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};

class KillNeuron : public ActionNeuron
{
public:
	KillNeuron(Creature* owner, double activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};
#endif