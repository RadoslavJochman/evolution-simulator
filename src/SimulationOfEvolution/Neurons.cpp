#include "Neurons.h"
#include <ranges>
double InternalNeuron::getActivation() const
{
	double activation = 0;
	for (auto&& [i, j] : std::ranges::zip_view(sensorInputs_, sensorWeights_))
	{
		activation += i->getActivation() * j;
	}
	return activation;
}

void InternalNeuron::createConnection(double weight, SensorNeuron* source)
{
	sensorInputs_.push_back(source);
	sensorWeights_.push_back(weight);
}

//returns random number
double RndNeuron::getActivation() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1, 1);
	return dis(gen);
}

//returns distance from north/south border
double BDyNeuron::getActivation() const
{
	return -1 + owner_->getPosition().second * (2.0f / owner_->config_->envSize_);
}

//returns distance from east/west border
double BDxNeuron::getActivation() const
{
	return -1 + owner_->getPosition().first * (2.0f / owner_->config_->envSize_);
}

//returns neares border distance
double BDNeuron::getActivation() const
{
	return std::min(std::fabs(-1 + owner_->getPosition().first * (2.0f / owner_->config_->envSize_)),
							  -1 + owner_->getPosition().second * (2.0f / owner_->config_->envSize_));
}

//returns x location
double LxNeuron::getActivation() const
{
	return owner_->getPosition().first * (1.0f / owner_->config_->envSize_);
}

//returns y location
double LyNeuron::getActivation() const
{
	return owner_->getPosition().second * (1.0f / owner_->config_->envSize_);
}

double DensNeuron::getActivation() const
{
	float activation = 0;
	auto [x_pos, y_pos] = owner_->getPosition();
	for (auto x : std::views::iota(std::max(0, (int)(x_pos - 2)), std::min((int)owner_->config_->envSize_, (int)(x_pos + 2))))
	{
		for (auto y : std::views::iota(std::max(0, (int)(y_pos - 2)), std::min((int)owner_->config_->envSize_, (int)(y_pos + 2))))
		{
			if (owner_->getEnv()->getHabitat()->at(x).at(y) != nullptr)
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

double ActionNeuron::getActivation()const
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

//Kills creature infront
void KillNeuron::step()
{
	if (std::fabs(getActivation()) >= activationThreshold_)
	{

	}
}

//Moves along y axis
void MyNeuron::step()
{
	double activation = getActivation();
	if (std::fabs(activation) >= activationThreshold_)
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
	if (std::fabs(activation) >= activationThreshold_)
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
	if (std::fabs(activation) >= activationThreshold_)
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
	if (std::fabs(getActivation()) >= activationThreshold_)
	{
		owner_->updatePosition(generateRandomDirection());
	}
}

//Moves forwards/backwards
void MFRNeuron::step()
{
	double activation = getActivation();
	if (std::fabs(activation) >= activationThreshold_)
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


