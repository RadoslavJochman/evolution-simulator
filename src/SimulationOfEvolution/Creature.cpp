#pragma once
#include "Creature.h"
#include "utilites.h"
#include <ranges>
//enum class ActionNeuronTypes { MFR, Mrn, MRL, Mx, My, Kill };
//enum class SensorNeuronTypes { Age, Rnd, BDy, BD, Lx, Ly, Osc };

Creature::Creature(std::size_t numGenes, std::pair<std::size_t, std::size_t> pos)
	:
	pos_(pos)
{
	createGenome(numGenes);
	buildBrain();
}

void Creature::createGenome(std::size_t numOfGenes)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 15);

	for (auto&& i : std::ranges::iota_view<std::size_t,std::size_t>( 0,numOfGenes ))
	{
		std::stringstream gene;
		for (auto&& j : std::ranges::iota_view( 0,8 ))
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
		std::string binGenome = hexToBin<8>(gene);
		char sourceType = binGenome[0];
		char endType = binGenome[8];
		int sourceID;
		int endID;
		int weight = std::stoi(binGenome.substr(16, 32), nullptr, 2);
		if (sourceType == '0')
		{
			sourceID = std::stoi(binGenome.substr(1, 8), nullptr, 2) % ((int)SensorNeuronTypes::size) + 1;
			SensorNeuronTypes neuronType = static_cast<SensorNeuronTypes>(sourceID);
			if (sensorBrain_.find(neuronType) == sensorBrain_.end())
			{
				addSensorNeuron(neuronType);
			}
		}
		else
		{
			sourceID = std::stoi(binGenome.substr(1, 8), nullptr, 2) % (maxNumInternal_);
			if (internalBrain_.find(sourceID)==internalBrain_.end())
			{
				internalBrain_.emplace(std::make_pair(internalBrain_.size(), std::make_unique<InternalNeuron>()));
			}
		}
		if (endType == '0')
		{
			endID = std::stoi(binGenome.substr(9, 16), nullptr, 2) % ((int)ActionNeuronTypes::size) + 1;
			ActionNeuronTypes neuronType = static_cast<ActionNeuronTypes>(sourceID);
			if (actionBrain_.find(neuronType) == actionBrain_.end())
			{
				addActionNeuron(neuronType);
			}
		}
		else
		{
			sourceID = std::stoi(binGenome.substr(1, 8), nullptr, 2) % (maxNumInternal_);
			if (internalBrain_.find(sourceID) == internalBrain_.end())
			{
				internalBrain_.emplace(std::make_pair(internalBrain_.size(), std::make_unique<InternalNeuron>()));
			}
		}

		createConnection(sourceType, endType, sourceID, endID, weight);
	}
}

void Creature::createConnection(char sourceType, char endType, int sourceID, int endID, int weight)
{
	if (sourceType == '0')
	{
		SensorNeuronTypes neuronType = static_cast<SensorNeuronTypes>(sourceID);
		SensorNeuron* source = sensorBrain_.find(neuronType)->second.get();
		if (endType == '0')
		{
			ActionNeuronTypes neuronType = static_cast<ActionNeuronTypes>(sourceID);
			ActionNeuron* end = actionBrain_.find(neuronType)->second.get();
			end->sensorWeights_.push_back(weight);
			end->sensorInputs_.push_back(source);
		}
		else
		{
			InternalNeuron* end = &(internalBrain_.find(endID)->second);
			end->sensorWeights_.push_back(weight);
			end->sensorInputs_.push_back(source);
		}
	}
	else
	{
		InternalNeuron* source = &(internalBrain_.find(sourceID)->second);
		if (endType == '0')
		{
			ActionNeuronTypes neuronType = static_cast<ActionNeuronTypes>(sourceID);
			ActionNeuron* end = actionBrain_.find(neuronType)->second.get();
			end->interWeights_.push_back(weight);
			end->interInputs_.push_back(source);
		}
		else
		{
			InternalNeuron* end = &(internalBrain_.find(endID)->second);
			end->interWeights_.push_back(weight);
			end->interInputs_.push_back(source);
		}
	}
}

void Creature::addSensorNeuron(SensorNeuronTypes type)
{
	switch (type)
	{
	case SensorNeuronTypes::Age:
	{
		sensorBrain_.emplace(std::make_pair(type, std::make_unique<AgeNeuron>()));
		break;
	}
	case SensorNeuronTypes::Rnd:
	{
		sensorBrain_.emplace(std::make_pair(type, std::make_unique<RndNeuron>()));
		break;
	}
	case SensorNeuronTypes::BDy:
	{
		sensorBrain_.emplace(std::make_pair(type, std::make_unique<BDyNeuron>()));
		break;
	}
	case SensorNeuronTypes::BDx:
	{
		sensorBrain_.emplace(std::make_pair(type, std::make_unique<BDxNeuron>()));
	}
	case SensorNeuronTypes::BD:
	{
		sensorBrain_.emplace(std::make_pair(type, std::make_unique<BDNeuron>()));
		break;
	}
	case SensorNeuronTypes::Lx:
	{
		sensorBrain_.emplace(std::make_pair(type, std::make_unique<LxNeuron>()));
		break;
	}
	case SensorNeuronTypes::Ly:
	{
		sensorBrain_.emplace(std::make_pair(type, std::make_unique<LyNeuron>()));
		break;
	}
	case SensorNeuronTypes::Osc:
	{
		sensorBrain_.emplace(std::make_pair(type, std::make_unique<OscNeuron>()));
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
		actionBrain_.emplace(std::make_pair(type, std::make_unique<MFRNeuron>()));
		break;
	}
	case ActionNeuronTypes::Mrn:
	{
		actionBrain_.emplace(std::make_pair(type, std::make_unique<MrnNeuron>()));
		break;
	}
	case ActionNeuronTypes::MRL:
	{
		actionBrain_.emplace(std::make_pair(type, std::make_unique<MRLNeuron>()));
		break;
	}
	case ActionNeuronTypes::Mx:
	{
		actionBrain_.emplace(std::make_pair(type, std::make_unique<MxNeuron>()));
		break;
	}
	case ActionNeuronTypes::My:
	{
		actionBrain_.emplace(std::make_pair(type, std::make_unique<MyNeuron>()));
		break;
	}
	case ActionNeuronTypes::Kill:
	{
		actionBrain_.emplace(std::make_pair(type, std::make_unique<KillNeuron>()));
		break;
	}
	default:
	{
		break;
	}
	}
}


