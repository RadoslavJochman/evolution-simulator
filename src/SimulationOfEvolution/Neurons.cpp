#include "Neurons.h"

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


float AgeNeuron::getActivation()
{
	return 0.0f;
}

float RndNeuron::getActivation()
{
	return 0.0f;
}

float BDyNeuron::getActivation()
{
	return 0.0f;
}

float BDxNeuron::getActivation()
{
	return 0.0f;
}

float BDNeuron::getActivation()
{
	return 0.0f;
}

float LxNeuron::getActivation()
{
	return 0.0f;
}

float LyNeuron::getActivation()
{
	return 0.0f;
}

float OscNeuron::getActivation()
{
	return 0.0f;
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

void KillNeuron::step()
{
	if (getActivation() >= activationTreshold_)
	{

	}
}

void MyNeuron::step()
{
	if (getActivation() >= activationTreshold_)
	{

	}
}

void MxNeuron::step()
{
	if (getActivation() >= activationTreshold_)
	{

	}
}

void MRLNeuron::step()
{
	if (getActivation() >= activationTreshold_)
	{

	}
}

void MrnNeuron::step()
{
	if (getActivation() >= activationTreshold_)
	{

	}
}

void MFRNeuron::step()
{
	if (getActivation() >= activationTreshold_)
	{

	}
}


