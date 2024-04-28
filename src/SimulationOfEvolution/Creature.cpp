#pragma once
#include "Creature.h"
#include "utilites.h"
#include <ranges>
//enum class ActionNeuronTypes { MFR, Mrn, MRL, Mx, My, Kill };
//enum class SensorNeuronTypes { Age, Rnd, BDy, BD, Lx, Ly, Osc };

void Creature::createGenome(std::size_t numOfGenes)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 15);

	for (auto&& i : std::ranges::iota_view( 0,numOfGenes ))
	{
		std::stringstream gene;
		for (auto&& j : std::ranges::iota_view( 0,8 ))
		{
			int randNumb = dis(gen);
			gene << std::hex << randNumb;
		}
		genome.push_back(gene.str());
	}

}

void Creature::buildBrain()
{
	
	for (auto&& gene : genome)
	{
		std::string binGenome = hexToBin<8>(gene);
		char sourceType = binGenome[0];
		char endType = binGenome[8];
		int sourceID;
		int endID;
		if (sourceType == '0')
		{
			sourceID = std::stoi(binGenome.substr(1, 8), nullptr, 2) % ((int)SensorNeuronTypes::size) + 1;
			SensorNeuronTypes neuronType = static_cast<SensorNeuronTypes>(sourceID);
			if (sensorBrain.find(neuronType) == sensorBrain.end())
			{
				addSensorNeuron(neuronType);
			}
		}
		else
		{
			sourceID = std::stoi(binGenome.substr(1, 8), nullptr, 2) % (maxNumInternal);
			if (internalBrain.find(sourceID)==internalBrain.end())
			{
				internalBrain.emplace(std::make_pair(internalBrain.size(), std::make_unique<InternalNeuron>()));
			}
		}
		if (endType == '0')
		{
			endID = std::stoi(binGenome.substr(9, 16), nullptr, 2) % ((int)ActionNeuronTypes::size) + 1;
			ActionNeuronTypes neuronType = static_cast<ActionNeuronTypes>(sourceID);
			if (actionBrain.find(neuronType) == actionBrain.end())
			{
				addActionNeuron(neuronType);
			}
		}
		else
		{
			sourceID = std::stoi(binGenome.substr(1, 8), nullptr, 2) % (maxNumInternal);
			if (internalBrain.find(sourceID) == internalBrain.end())
			{
				internalBrain.emplace(std::make_pair(internalBrain.size(), std::make_unique<InternalNeuron>()));
			}
		}
	}
}


void Creature::addSensorNeuron(SensorNeuronTypes type)
{
	switch (type)
	{
	case SensorNeuronTypes::Age:
	{
		sensorBrain.emplace(std::make_pair(type, std::make_unique<AgeNeuron>()));
		break;
	}
	case SensorNeuronTypes::Rnd:
	{
		sensorBrain.emplace(std::make_pair(type, std::make_unique<RndNeuron>()));
		break;
	}
	case SensorNeuronTypes::BDy:
	{
		sensorBrain.emplace(std::make_pair(type, std::make_unique<BDyNeuron>()));
		break;
	}
	case SensorNeuronTypes::BD:
	{
		sensorBrain.emplace(std::make_pair(type, std::make_unique<BDNeuron>()));
		break;
	}
	case SensorNeuronTypes::Lx:
	{
		sensorBrain.emplace(std::make_pair(type, std::make_unique<LxNeuron>()));
		break;
	}
	case SensorNeuronTypes::Ly:
	{
		sensorBrain.emplace(std::make_pair(type, std::make_unique<LyNeuron>()));
		break;
	}
	case SensorNeuronTypes::Osc:
	{
		sensorBrain.emplace(std::make_pair(type, std::make_unique<OscNeuron>()));
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
		actionBrain.emplace(std::make_pair(type, std::make_unique<MFRNeuron>()));
		break;
	}
	case ActionNeuronTypes::Mrn:
	{
		actionBrain.emplace(std::make_pair(type, std::make_unique<MrnNeuron>()));
		break;
	}
	case ActionNeuronTypes::MRL:
	{
		actionBrain.emplace(std::make_pair(type, std::make_unique<MRLNeuron>()));
		break;
	}
	case ActionNeuronTypes::Mx:
	{
		actionBrain.emplace(std::make_pair(type, std::make_unique<MxNeuron>()));
		break;
	}
	case ActionNeuronTypes::My:
	{
		actionBrain.emplace(std::make_pair(type, std::make_unique<MyNeuron>()));
		break;
	}
	case ActionNeuronTypes::Kill:
	{
		actionBrain.emplace(std::make_pair(type, std::make_unique<KillNeuron>()));
		break;
	}
	default:
	{
		break;
	}
	}
}
