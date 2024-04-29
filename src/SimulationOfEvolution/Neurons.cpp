#include "Neurons.h"

float InternalNeuron::getActivation()
{
	float activation = 0;
	for (auto&& [i,j] : std::ranges::zip_view(sensorInputs_, sensorWeights_))
	{
		activation += i->getActivation() * j;
	}
	for (auto&& [i,j] : std::ranges::zip_view(interInputs_, interWeights_))
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