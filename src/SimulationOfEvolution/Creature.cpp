#include "Creature.h"
#include "utilites.h"
#include <ranges>

Creature::Creature(std::pair<int,int>&& pos, const Config* config, Environment* myEnv)
	:
	config_(config),
	killed(false),
	myEnv_(myEnv),
	pos_(std::move(pos)),
	direction_(generateRandomDirection())

{
	createGenome();
}

Creature::Creature(std::pair<int, int>&& pos, const Config* config, Environment* myEnv, std::vector<std::string>&& genome)
	:
	config_(config),
	killed(false),
	myEnv_(myEnv),
	genome_(std::move(genome)),
	pos_(std::move(pos)),
	direction_({ 1,0 })
{}

Creature::Creature()
	:
	config_(nullptr),
	killed(false),
	myEnv_(nullptr),
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
	std::mt19937 rndGenerator(rd());
	std::uniform_int_distribution<> dis(0, 15);

	for (auto&& i : std::ranges::iota_view<std::size_t, std::size_t>(0, config_->numGenes_))
	{
		std::stringstream gene;
		for (auto&& j : std::ranges::iota_view(0, 8))
		{
			int randNumb = dis(rndGenerator);
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
		int weight = std::stoi(binGenome.substr(16, 23), nullptr, 2);
		int activationThreshold = std::stoi(binGenome.substr(24, 31), nullptr, 2);
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
				addActionNeuron(neuronType, activationThreshold);
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

const std::array<int, 3> Creature::getColor() const
{
	int r = 0;
	int g = 0;
	int b = 0;
	for (auto&& gene : genome_)
	{
		r += std::stoi(gene.substr(0, 2), nullptr, 16);
		g += std::stoi(gene.substr(2, 2), nullptr, 16);
		b += std::stoi(gene.substr(4, 2), nullptr, 16);
	}
	r = r / genome_.size();
	g = g / genome_.size();
	b = b / genome_.size();
	return { r, g, b };
}

void Creature::die()
{
	killed = true;
}

bool Creature::isKilled()
{
	return killed;
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

Creature Creature::breed(const Creature& c1, std::pair<int, int>&& pos)
{
	std::vector<std::string> genome;
	std::random_device rd;
	std::mt19937 rndGenerator(rd());
	std::uniform_int_distribution<> dist(0, 1);
	for (auto&& [gene1, gene2] : std::ranges::zip_view(c1.genome_, genome_))
	{
		int randomIndex = dist(rndGenerator);
		genome.push_back((randomIndex == 0) ? gene1 : gene2);
	}
	return Creature(std::move(pos), config_, myEnv_, std::move(genome));
}

void Creature::mutate()
{
	std::random_device rd;
	std::mt19937 rndGenerator(rd());
	std::array<char, 16> hexDigits({'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'});
	std::uniform_int_distribution<> genePicker(0, config_->numGenes_-1);
	int geneIndex = genePicker(rndGenerator);
	std::uniform_int_distribution<> basePicker(0, 8);
	int baseIndex = basePicker(rndGenerator);
	std::uniform_int_distribution<> newBasePicker(0, 15);
	int newBaseIndex = newBasePicker(rndGenerator);
	genome_[geneIndex][baseIndex] = hexDigits[newBaseIndex];
}

void Creature::addSensorNeuron(SensorNeuronTypes type)
{
	switch (type)
	{
	case SensorNeuronTypes::Rnd:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<RndNeuron>()));
		break;
	}
	case SensorNeuronTypes::BDy:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<BDyNeuron>(this)));
		break;
	}
	case SensorNeuronTypes::BDx:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<BDxNeuron>(this)));
		break;
	}
	case SensorNeuronTypes::BD:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<BDNeuron>(this)));
		break;
	}
	case SensorNeuronTypes::Lx:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<LxNeuron>(this)));
		break;
	}
	case SensorNeuronTypes::Ly:
	{
		sensorBrain_.insert(std::make_pair(type, std::make_unique<LyNeuron>(this)));
		break;
	}
	default:
	{
		break;
	}
	}
}

void Creature::addActionNeuron(ActionNeuronTypes type, int activationThreshold)
{
	switch (type)
	{
	case ActionNeuronTypes::MFR:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<MFRNeuron>(this, activationThreshold)));
		break;
	}
	case ActionNeuronTypes::Mrn:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<MrnNeuron>(this, activationThreshold)));
		break;
	}
	case ActionNeuronTypes::MRL:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<MRLNeuron>(this, activationThreshold)));
		break;
	}
	case ActionNeuronTypes::Mx:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<MxNeuron>(this, activationThreshold)));
		break;
	}
	case ActionNeuronTypes::My:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<MyNeuron>(this, activationThreshold)));
		break;
	}
	case ActionNeuronTypes::Kill:
	{
		actionBrain_.insert(std::make_pair(type, std::make_unique<KillNeuron>(this, activationThreshold)));
		break;
	}
	default:
	{
		break;
	}
	}
}


