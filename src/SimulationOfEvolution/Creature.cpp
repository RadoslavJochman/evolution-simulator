#pragma once
#include "Creature.h"
#include <bitset>

//enum class ActionNeuronTypes { MFR, Mrn, MRL, Mx, My, Kill };
//enum class SensorNeuronTypes { Age, Rnd, BDy, BD, Lx, Ly, Osc };

void Creature::createGenome(std::size_t numOfGenes)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 15);

	for (auto&& i : std::ranges::iota_view<std::size_t, std::size_t>{ 0,numOfGenes })
	{
		std::stringstream gene;
		for (auto&& j : std::ranges::iota_view{ 0,8 })
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
		std::stringstream ss;
		unsigned tmp;
		ss << gene;
		ss >> tmp;
		std::string binGenome = std::bitset<32>(tmp).to_string();
		switch (binGenome[0])
		{
		case 0:
		{
			SensorNeuronTypes neuronType = static_cast<SensorNeuronTypes>(std::stoi(binGenome.substr(1, 8), nullptr, 2) % ((int)SensorNeuronTypes::size) + 1);
			if (sensorBrain.find(neuronType) == sensorBrain.end())
			{
				addSensorNeuron(neuronType);
			}
		}
		case 1:
		{
			ActionNeuronTypes neuronType = static_cast<ActionNeuronTypes>(std::stoi(binGenome.substr(1, 8), nullptr, 2) % ((int)ActionNeuronTypes::size) + 1);
			if (actionBrain.find(neuronType) == actionBrain.end())
			{
				addActionNeuron(neuronType);
			}
		}
		default:
			break;
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
		break
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
	}
}
