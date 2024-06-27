#include "Neurons.h"
#include "Creature.h"
#include <ranges>
double InternalNeuron::getActivation() const
{
	double activation = 0;
	for (std::size_t i = 0; i<sensorInputs_.size(); i++)
	{
		activation += sensorInputs_[i]->getActivation() * sensorWeights_[i];
	}
	return activation;
}

void InternalNeuron::createConnection(double weight, SensorNeuron* source)
{
	sensorInputs_.push_back(source);
	sensorWeights_.push_back(weight);
}

double RndNeuron::getActivation() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1, 1);
	return dis(gen);
}

BDyNeuron::BDyNeuron(const Creature & owner)
	:
	owner_(owner)
{}

double BDyNeuron::getActivation() const
{
	return -1 + owner_.getPosition().second * (2.0f / owner_.config_->envSize_);
}

BDxNeuron::BDxNeuron(const Creature& owner)
	:
	owner_(owner)
{}

double BDxNeuron::getActivation() const
{
	return -1 + owner_.getPosition().first * (2.0f / owner_.config_->envSize_);
}

BDNeuron::BDNeuron(const Creature& owner)
	:
	owner_(owner)
{}

double BDNeuron::getActivation() const
{
	return std::min(std::fabs(-1 + owner_.getPosition().first * (2.0f / owner_.config_->envSize_)),
					std::fabs(-1 + owner_.getPosition().second * (2.0f / owner_.config_->envSize_)));
}

LxNeuron::LxNeuron(const Creature& owner)
	:
	owner_(owner)
{}

double LxNeuron::getActivation() const
{
	return owner_.getPosition().first * (1.0f / owner_.config_->envSize_);
}

LyNeuron::LyNeuron(const Creature& owner)
	:
	owner_(owner)
{}

double LyNeuron::getActivation() const
{
	return owner_.getPosition().second * (1.0f / owner_.config_->envSize_);
}


DensNeuron::DensNeuron(const Creature& owner)
	:
	owner_(owner)
{}

double DensNeuron::getActivation() const
{
	float activation = 0;
	auto [x_pos, y_pos] = owner_.getPosition();
	for (auto x : std::views::iota(std::max(0, (int)(x_pos - 2)), std::min((int)owner_.config_->envSize_, (int)(x_pos + 3))))
	{
		for (auto y : std::views::iota(std::max(0, (int)(y_pos - 2)), std::min((int)owner_.config_->envSize_, (int)(y_pos + 3))))
		{
			if (owner_.getEnv()->getHabitat().at(x).at(y) != nullptr)
			{
				activation += 1;
			}
			else
			{
				activation -= 1;
			}
		}
	}
	return activation / 25;
}

ActionNeuron::ActionNeuron(Creature& owner, int activationTreshold)
	:
	owner_(owner),
	activationThreshold_(activationTreshold)
{}

double ActionNeuron::getActivation()const
{
	double activation = 0;
	for (std::size_t i = 0; i<interInputs_.size(); i++)
	{
		activation += interWeights_[i] * interInputs_[i]->getActivation();
	}
	for (std::size_t i = 0; i<sensorInputs_.size(); i++)
	{
		activation += sensorWeights_[i] * sensorInputs_[i]->getActivation();
	}
	return activation;
}


void ActionNeuron::createConnection(int weight, InternalNeuron* source)
{
	interInputs_.push_back(source);
	interWeights_.push_back(weight);
}


void ActionNeuron::createConnection(int weight, SensorNeuron* source)
{
	sensorInputs_.push_back(source);
	sensorWeights_.push_back(weight);
}


KillNeuron::KillNeuron(Creature& owner, int activationTreshold)
	: ActionNeuron(owner, activationTreshold) {}

void KillNeuron::step()
{
	if (std::fabs(getActivation()) >= activationThreshold_)
	{
		auto habitat = owner_.getEnv()->getHabitat();
		auto [x, y] = owner_.getPosition()+owner_.getDirection();
		if (x < owner_.config_->envSize_ && x >= 0 && y < owner_.config_->envSize_ && y >= 0 && habitat.at(x).at(y) != nullptr)
		{
			habitat.at(x).at(y)->die();
		}
	}
}

MyNeuron::MyNeuron(Creature& owner, int activationTreshold)
	: ActionNeuron(owner, activationTreshold) {}

void MyNeuron::step()
{
	double activation = getActivation();
	if (std::fabs(activation) >= activationThreshold_)
	{
		if (activation > 0)
		{
			owner_.updatePosition({ 0, 1 });
		}
		else
		{
			owner_.updatePosition({ 0, -1 });
		}
		
	}
}

MxNeuron::MxNeuron(Creature& owner, int activationTreshold)
	: ActionNeuron(owner, activationTreshold) {}

void MxNeuron::step()
{
	double activation = getActivation();
	if (std::fabs(activation) >= activationThreshold_)
	{
		if (activation > 0)
		{
			owner_.updatePosition({ 1, 0 });
		}
		else
		{
			owner_.updatePosition({ -1, 0 });
		}

	}
}

MRLNeuron::MRLNeuron(Creature& owner, int activationTreshold)
	: ActionNeuron(owner, activationTreshold) {}

void MRLNeuron::step()
{
	double activation = getActivation();
	if (std::fabs(activation) >= activationThreshold_)
	{
		if (activation > 0)
		{
			owner_.moveRight({ 1, -1 });
		}
		else
		{
			owner_.moveRight({ -1, 1 });
		}
	}
}

MrnNeuron::MrnNeuron(Creature& owner, int activationTreshold)
	: ActionNeuron(owner, activationTreshold) {}

void MrnNeuron::step()
{
	if (std::fabs(getActivation()) >= activationThreshold_)
	{
		owner_.updatePosition(generateRandomDirection());
	}
}

MFRNeuron::MFRNeuron(Creature& owner, int activationTreshold)
	: ActionNeuron(owner, activationTreshold) {}

void MFRNeuron::step()
{
	double activation = getActivation();
	if (std::fabs(activation) >= activationThreshold_)
	{
		if (activation > 0)
		{
			owner_.moveForward({ 1,1 });
		}
		else
		{
			owner_.moveForward({ -1,-1 });
		}

	}
}


