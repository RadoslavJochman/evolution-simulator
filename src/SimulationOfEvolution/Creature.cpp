#include "Creature.h"
#include "utilites.h"
#include <ranges>

Creature::Creature(std::pair<int,int>&& pos, const Config* config, Environment* myEnv)
	:
	myEnv_(myEnv),
	config_(config),
	pos_(pos),
	direction_({ 1,0 })

{
	createGenome();
}

Creature::Creature()
	:
	myEnv_(nullptr),
	config_(nullptr),
	pos_({ 0,0 }),
	direction_({ 1,0 })
{}

void Creature::step()
{
	for (auto&& actionNeuron : actionBrain_)
	{
		actionNeuron.second->step();
	}
}

void Creature::moveRight(const std::pair<int, int>& direction)
{
	direction_ = swapPairValues(direction_) * direction;
	std::pair<int, int> new_pos = pos_ + direction_;
	if (myEnv_->isFree(new_pos.first, new_pos.second))
	{
		myEnv_->moveCreature(pos_.first, pos_.second, new_pos.first, new_pos.second);
		pos_ = new_pos;
	}
}

void Creature::moveForward(const std::pair<int, int>& direction)
{
	direction_ = direction_ * direction;
	std::pair<int, int> new_pos = pos_ + direction_;
	if (myEnv_->isFree(new_pos.first, new_pos.second))
	{
		myEnv_->moveCreature(pos_.first, pos_.second, new_pos.first, new_pos.second);
		pos_ = new_pos;
	}
}

void Creature::updatePosition(const std::pair<int, int>& direction)
{
	
	std::pair<int, int> new_pos = pos_ + direction;
	if (myEnv_->isFree(new_pos.first, new_pos.second))
	{
		myEnv_->moveCreature(pos_.first, pos_.second, new_pos.first, new_pos.second);
		pos_ = new_pos;
	}
}

const std::pair<std::size_t, std::size_t>& Creature::getPosition() const
{
	return pos_;
}

void Creature::createGenome()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 15);

	for (auto&& i : std::ranges::iota_view<std::size_t, std::size_t>(0, config_->numGenes_))
	{
		std::stringstream gene;
		for (auto&& j : std::ranges::iota_view(0, 8))
		{
			int randNumb = dis(gen);
			gene << std::hex << randNumb;
		}
		genome_.push_back(gene.str());
	}
}

void Creature::buildBrain()
{

	for (auto&& gene : genome_)
	{
		std::string binGenome = hexToBin(gene);
		char sourceType = binGenome[0];
		char endType = binGenome[8];
		int sourceID;
		int endID;
		int weight = 1;//std::stoi(binGenome.substr(16, 32), nullptr, 2);
		if (sourceType == '0' || (sourceType == '1' && endType == '1') || config_->maxInternalNeurons_ == 0)
		{
			sourceID = std::stoi(binGenome.substr(1, 8), nullptr, 2) % config_->activeSensorNeurons_.size();
			SensorNeuronTypes neuronType = config_->activeSensorNeurons_[sourceID];
			if (sensorBrain_.find(neuronType) == sensorBrain_.end())
			{
				addSensorNeuron(neuronType);
			}
		}
		else
		{
			sourceID = std::stoi(binGenome.substr(1, 8), nullptr, 2) % (config_->maxInternalNeurons_);
			if (internalBrain_.find(sourceID) == internalBrain_.end())
			{
				internalBrain_.insert(std::make_pair(sourceID, InternalNeuron()));
			}
		}
		if (endType == '0' || (sourceType == '1' && endType == '1') || config_->maxInternalNeurons_ == 0)
		{
			endID = std::stoi(binGenome.substr(9, 16), nullptr, 2) % config_->activeActionNeurons_.size();
			ActionNeuronTypes neuronType = config_->activeActionNeurons_[endID];
			if (actionBrain_.find(neuronType) == actionBrain_.end())
			{
				addActionNeuron(neuronType);
			}
		}
		else
		{
			endID = std::stoi(binGenome.substr(1, 8), nullptr, 2) % config_->maxInternalNeurons_;

			if (internalBrain_.find(endID) == internalBrain_.end())
			{
				internalBrain_.insert(std::make_pair(endID, InternalNeuron()));
			}

		}

		createConnection(sourceType, endType, sourceID, endID, weight);
	}
}

void Creature::createConnection(char sourceType, char endType, int sourceID, int endID, int weight)
{
	if (sourceType == '0' || (sourceType == '1' && endType == '1') || config_->maxInternalNeurons_ == 0)
	{
		SensorNeuronTypes sourceNeuronType = config_->activeSensorNeurons_[sourceID];
		SensorNeuron* source = sensorBrain_.find(sourceNeuronType)->second.get();
		if (endType == '0' || (sourceType == '1' && endType == '1') || config_->maxInternalNeurons_ == 0)
		{

			ActionNeuronTypes endNeuronType = config_->activeActionNeurons_[endID];
			ActionNeuron* end = actionBrain_.find(endNeuronType)->second.get();
			end->createConnection(weight, source);
			
		}
		else
		{
			InternalNeuron* end = &(internalBrain_.find(endID)->second);
			end->createConnection(weight, source);
		}
	}
	else
	{
		InternalNeuron* source = &(internalBrain_.find(sourceID)->second);
		if (endType == '0')
		{
			ActionNeuronTypes endNeuronType = config_->activeActionNeurons_[endID];
			ActionNeuron* end = actionBrain_.find(endNeuronType)->second.get();
			end->createConnection(weight, source);
		}
		else
		{
			InternalNeuron* end = &(internalBrain_.find(endID)->second);
			end->createConnection(weight, source);
		}
	}
}

void Creature::addSensorNeuron(SensorNeuronTypes type)
{
	switch (type)
	{
	case SensorNeuronTypes::Age:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<AgeNeuron>()));
		break;
	}
	case SensorNeuronTypes::Rnd:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<RndNeuron>()));
		break;
	}
	case SensorNeuronTypes::BDy:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<BDyNeuron>()));
		break;
	}
	case SensorNeuronTypes::BDx:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<BDxNeuron>()));
	}
	case SensorNeuronTypes::BD:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<BDNeuron>()));
		break;
	}
	case SensorNeuronTypes::Lx:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<LxNeuron>()));
		break;
	}
	case SensorNeuronTypes::Ly:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<LyNeuron>()));
		break;
	}
	case SensorNeuronTypes::Osc:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<OscNeuron>()));
		break;
	}
	default:
	{
		break;
	}
	}
}

void Creature::addActionNeuron(ActionNeuronTypes type)
{
	switch (type)
	{
	case ActionNeuronTypes::MFR:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<MFRNeuron>(this,0.8)));
		break;
	}
	case ActionNeuronTypes::Mrn:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<MrnNeuron>(this, 0.8)));
		break;
	}
	case ActionNeuronTypes::MRL:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<MRLNeuron>(this, 0.8)));
		break;
	}
	case ActionNeuronTypes::Mx:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<MxNeuron>(this, 0.8)));
		break;
	}
	case ActionNeuronTypes::My:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<MyNeuron>(this, 0.8)));
		break;
	}
	case ActionNeuronTypes::Kill:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<KillNeuron>(this, 0.8)));
		break;
	}
	default:
	{
		break;
	}
	}
}


