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
	virtual double getActivation() const = 0;
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
	void createConnection(int weight, InternalNeuron* source);
	void createConnection(int weight, SensorNeuron* source);
	ActionNeuron(Creature* owner, int activationTreshold)
		:
		owner_(owner),
		activationThreshold_(activationTreshold) {}
protected:
	Creature* owner_;
	std::vector<InternalNeuron*> interInputs_;
	std::vector<SensorNeuron*> sensorInputs_;
	std::vector<double> sensorWeights_;
	std::vector<double> interWeights_;
	int activationThreshold_;
	double getActivation() const;
};


class RndNeuron : public SensorNeuron
{
public:
	double getActivation() const override;
};

class BDyNeuron : public SensorNeuron
{
public:
	double getActivation() const override;
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
	double getActivation() const override;
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
	double getActivation() const override;
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
	double getActivation() const override;
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
	double getActivation() const override;
	LyNeuron(const Creature* owner)
		:
		owner_(owner)
	{}
private:
	const Creature* owner_;
};

class DensNeuron : public SensorNeuron
{
public:
	double getActivation() const override;
	DensNeuron(const Creature* owner)
		:
		owner_(owner)
	{}
private:
	const Creature* owner_;
};

class MFRNeuron : public ActionNeuron
{
public:
	MFRNeuron(Creature* owner, int activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};

class MrnNeuron : public ActionNeuron
{
public:
	MrnNeuron(Creature* owner, int activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};

class MRLNeuron : public ActionNeuron
{
public:
	MRLNeuron(Creature* owner, int activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};

class MxNeuron : public ActionNeuron
{
public:
	MxNeuron(Creature* owner, int activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};

class MyNeuron : public ActionNeuron
{
public:
	MyNeuron(Creature* owner, int activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};

class KillNeuron : public ActionNeuron
{
public:
	KillNeuron(Creature* owner, int activationTreshold)
		: ActionNeuron(owner, activationTreshold) {}
	void step() override;
};
#endif