#include "Neurons.h"

float InternalNeuron::getActivation()
{
	float activation = bias;
	for (auto&& i : inputs)
	{
		activation = activation + i->getActivation();
	}
	for (auto&& i : interInputs)
	{
		activation = activation + i->getActivation();
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
	return my_env->currentStepInGen / my_env->maxGeneration;
}

ActionNeuron::ActionNeuron()
{
	
}