#ifndef NEURONS_H
#define NEURONS_H
#include <vector>
#include <memory>
#include <ranges>
#include <iostream>
#include "Creature.h"
#include <random>
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


class RndNeuron : public SensorNeuron
{
public:
	float getActivation() override;
};

class BDyNeuron : public SensorNeuron
{
public:
	float getActivation() override;
	BDyNeuron(const Creature* owner)
		:
		owner_(owner)
	{}
private:
	const Creature* owner_;
};

class BDxNeuron : public SensorNeuron
{
public:
	float getActivation() override;
	BDxNeuron(const Creature* owner)
		:
		owner_(owner)
	{}
private:
	const Creature* owner_;
};

class BDNeuron : public SensorNeuron
{
public:
	float getActivation() override;
	BDNeuron(const Creature* owner)
		:
		owner_(owner)
	{}
private:
	const Creature* owner_;
};

class LxNeuron : public SensorNeuron
{
public:
	float getActivation() override;
	LxNeuron(const Creature* owner)
		:
		owner_(owner)
	{}
private:
	const Creature* owner_;
};

class LyNeuron : public SensorNeuron
{
public:
	float getActivation() override;
	LyNeuron(const Creature* owner)
		:
		owner_(owner)
	{}
private:
	const Creature* owner_;
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