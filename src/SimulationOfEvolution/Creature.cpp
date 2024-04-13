#pragma once
#include "Creature.h"
#include <bitset>

//enum class ActionNeuronsType { MFR, Mrn, MRL, Mx, My, Kill };
//enum class SensorNeuronsType { Age, Rnd, BDy, BD, Lx, Ly, Osc };

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
			SensorNeuronsType neuronType = static_cast<SensorNeuronsType>(std::stoi(binGenome.substr(1, 8),nullptr,2)%((int)SensorNeuronsType::size)+1);
			
		}
		default:
			break;
		}
	}
}

void Creature::addSensorNeuron(SensorNeuronsType type)
{
	switch (type)
	{
	case SensorNeuronsType::Age:
	{
		sensorBrain.emplace(std::make_pair(type, AgeNeuron()));
	}

	}
}
