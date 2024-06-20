#include "Neurons.h"
#include <ranges>
float InternalNeuron::getActivation()
{
	float activation = 0;
	for (auto&& [i, j] : std::ranges::zip_view(sensorInputs_, sensorWeights_))
	{
		activation += i->getActivation() * j;
	}
	for (auto&& [i, j] : std::ranges::zip_view(interInputs_, interWeights_))
	{
		activation += i->getActivation() * j;
	}
	return activation;
}

void InternalNeuron::createConnection(double weight, InternalNeuron* source)
{
	interInputs_.push_back(source);
	interWeights_.push_back(weight);
}

void InternalNeuron::createConnection(double weight, SensorNeuron* source)
{
	sensorInputs_.push_back(source);
	sensorWeights_.push_back(weight);
}

//returns how many frames passed since start of current generation
float AgeNeuron::getActivation()
{
	return 1.0f;
}

//returns random number
float RndNeuron::getActivation()
{
	return 1.0f;
}

//returns distance from north/south border
float BDyNeuron::getActivation()
{
	return 1.0f;
}

//returns distance from east/west border
float BDxNeuron::getActivation()
{
	return 1.0f;
}

//returns neares border distance
float BDNeuron::getActivation()
{
	return 1.0f;
}

//returns x location
float LxNeuron::getActivation()
{
	return 1.0f;
}

//returns y location
float LyNeuron::getActivation()
{
	return 1.0f;
}

//oscillate and returns the value of this oscillation
float OscNeuron::getActivation()
{
	return 1.0f;
}

double ActionNeuron::getActivation()
{
	double activation = 0;
	for (const auto& [interNeuron, interWeight] : std::ranges::zip_view(interInputs_, interWeights_))
	{
		activation += interWeight * interNeuron->getActivation();
	}
	for (const auto& [sensorNeuron, sensorWeight] : std::ranges::zip_view(sensorInputs_, sensorWeights_))
	{
		activation += sensorWeight * sensorNeuron->getActivation();
	}
	return activation;
}

void ActionNeuron::createConnection(double weight, InternalNeuron* source)
{
	interInputs_.push_back(source);
	interWeights_.push_back(weight);
}

void ActionNeuron::createConnection(double weight, SensorNeuron* source)
{
	sensorInputs_.push_back(source);
	sensorWeights_.push_back(weight);
}

//Kills creature infront
void KillNeuron::step()
{
	if (std::fabs(getActivation()) >= activationTreshold_)
	{

	}
}

//Moves along y axis
void MyNeuron::step()
{
	double activation = getActivation();
	if (std::fabs(activation) >= activationTreshold_)
	{
		if (activation > 0)
		{
			owner_->updatePosition({ 0, 1 });
		}
		else
		{
			owner_->updatePosition({ 0, -1 });
		}
		
	}
}

//Moves along x axis
void MxNeuron::step()
{
	double activation = getActivation();
	if (std::fabs(activation) >= activationTreshold_)
	{
		if (activation > 0)
		{
			owner_->updatePosition({ 1, 0 });
		}
		else
		{
			owner_->updatePosition({ -1, 0 });
		}

	}
}

//Moves left/right
void MRLNeuron::step()
{
	double activation = getActivation();
	if (std::fabs(activation) >= activationTreshold_)
	{
		if (activation > 0)
		{
			owner_->moveRight({ 1, -1 });
		}
		else
		{
			owner_->moveRight({ -1, 1 });
		}
	}
}

//Moves in random direction
void MrnNeuron::step()
{
	if (std::fabs(getActivation()) >= activationTreshold_)
	{
		owner_->updatePosition(generateRandomDirection());
	}
}

//Moves forwards/backwards
void MFRNeuron::step()
{
	double activation = getActivation();
	if (std::fabs(activation) >= activationTreshold_)
	{
		if (activation > 0)
		{
			owner_->moveForward({ 1,1 });
		}
		else
		{
			owner_->moveForward({ -1,-1 });
		}

	}
}


