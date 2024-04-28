#include "Neurons.h"

float InternalNeuron::getActivation()
{
	float activation;
	for (auto&& [i,j] : std::ranges::zip_view(sensorInputs, sensorWeights))
	{
		activation += i->getActivation() * j;
	}
	for (auto&& [i,j] : std::ranges::zip_view(interInputs, interWeights))
	{
		activation += i->getActivation() * j;
	}
	return activation;
}
InternalNeuron::InternalNeuron()
{
	
}

AgeNeuron::AgeNeuron()
{

}

float AgeNeuron::getActivation()
{

}

ActionNeuron::ActionNeuron()
{
	
}