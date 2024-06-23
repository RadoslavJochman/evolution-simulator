#include "Neurons.h"
#include <ranges>
double InternalNeuron::getActivation() const
{
	double activation = 0;
	for (auto&& [input, weight] : std::ranges::zip_view(sensorInputs_, sensorWeights_))
	{
		activation += input->getActivation() * weight;
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

double BDyNeuron::getActivation() const
{
	return -1 + owner_->getPosition().second * (2.0f / owner_->config_->envSize_);
}

double BDxNeuron::getActivation() const
{
	return -1 + owner_->getPosition().first * (2.0f / owner_->config_->envSize_);
}

double BDNeuron::getActivation() const
{
	return std::min(std::fabs(-1 + owner_->getPosition().first * (2.0f / owner_->config_->envSize_)),
					std::fabs(-1 + owner_->getPosition().second * (2.0f / owner_->config_->envSize_)));
}

double LxNeuron::getActivation() const
{
	return owner_->getPosition().first * (1.0f / owner_->config_->envSize_);
}

double LyNeuron::getActivation() const
{
	return owner_->getPosition().second * (1.0f / owner_->config_->envSize_);
}


double DensNeuron::getActivation() const
{
	float activation = 0;
	auto [x_pos, y_pos] = owner_->getPosition();
	for (auto x : std::views::iota(std::max(0, (int)(x_pos - 2)), std::min((int)owner_->config_->envSize_, (int)(x_pos + 3))))
	{
		for (auto y : std::views::iota(std::max(0, (int)(y_pos - 2)), std::min((int)owner_->config_->envSize_, (int)(y_pos + 3))))
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


void KillNeuron::step()
{
	if (std::fabs(getActivation()) >= activationThreshold_)
	{
		auto habitat = owner_->getEnv()->getHabitat();
		auto [x, y] = owner_->getPosition()+owner_->getDirection();
		if (x < owner_->config_->envSize_ && x >= 0 && y < owner_->config_->envSize_ && y >= 0 && habitat->at(x).at(y) != nullptr)
		{
			habitat->at(x).at(y)->die();
		}
	}
}

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

void MrnNeuron::step()
{
	if (std::fabs(getActivation()) >= activationThreshold_)
	{
		owner_->updatePosition(generateRandomDirection());
	}
}

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


