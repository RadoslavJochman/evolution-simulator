#pragma
#include <string>
#include <sstream>
#include <bitset>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Neurons.h"

template<std::size_t hexSize>
std::string hexToBin(const std::string& hexNumber)
{
	std::stringstream ss;
	unsigned tmp;
	ss << hexNumber;
	ss >> tmp;
	return std::bitset<4*hexSize>(tmp).to_string();
}

struct Config
{
	Config(std::size_t envSize, std::string envType, std::size_t numCreatures, std::size_t maxInternalNeurons, std::vector<std::size_t> activeSensorNeurons, std::vector<std::size_t> activeActionNeurons)
		:
		envSize_(envSize),
		envType_(envType),
		numCreatures_(numCreatures),
		maxInternalNeurons_(maxInternalNeurons),
		activeSensorNeurons_(activeSensorNeurons),
		activeActionNeurons_(activeActionNeurons)
	{}

	std::size_t envSize_;
	std::string envType_;
	std::size_t numCreatures_;
	std::size_t maxInternalNeurons_;
	std::vector<std::size_t> activeSensorNeurons_;
	std::vector<std::size_t> activeActionNeurons_;
};

enum ConfigKey {
    ENV_SIZE,
    ENV_TYPE,
    NUM_CREATURES,
    MAX_INTERNAL_NEURONS,
    SENSOR_NEURONS_TYPE,
    ACTION_NEURONS_TYPE,
    UNKNOWN
};

ConfigKey getConfigKey(const std::string& key) {
    static const std::unordered_map<std::string, ConfigKey> keyMap = {
        {"env_size", ENV_SIZE},
        {"env_type", ENV_TYPE},
        {"num_creatures", NUM_CREATURES},
        {"max_internal_neurons", MAX_INTERNAL_NEURONS},
        {"sensor_neurons_type", SENSOR_NEURONS_TYPE},
        {"action_neurons_type", ACTION_NEURONS_TYPE}
    };

    auto it = keyMap.find(key);
    if (it != keyMap.end()) {
        return it->second;
    }
    else {
        return UNKNOWN;
    }
}

ActionNeuronTypes getActionNeuron(const std::string& name)
{
    static const std::unordered_map<std::string, ActionNeuronTypes> actionNeuronMap = {
    {"MFR", ActionNeuronTypes::MFR},
    {"Mrn", ActionNeuronTypes::Mrn},
    {"MRL", ActionNeuronTypes::MRL},
    {"Mx", ActionNeuronTypes::Mx},
    {"My", ActionNeuronTypes::My},
    {"Kill", ActionNeuronTypes::Kill}
    };

    auto it = actionNeuronMap.find(name);
    if (it != actionNeuronMap.end()) {
        return it->second;
    }
    else {
        return ActionNeuronTypes::UNKNOWN;
    }
}

SensorNeuronTypes getSensorNeuron(const std::string& name)
{
    static const std::unordered_map<std::string, SensorNeuronTypes> sensorNeuronMap = {
    {"Age", SensorNeuronTypes::Age},
    {"Age", SensorNeuronTypes::Age},
    {"BDy", SensorNeuronTypes::BDy},
    {"BD", SensorNeuronTypes::BD},
    {"Lx", SensorNeuronTypes::Lx},
    {"Ly", SensorNeuronTypes::Ly},
    {"Osc", SensorNeuronTypes::Osc}
    };

    auto it = sensorNeuronMap.find(name);
    if (it != sensorNeuronMap.end()) {
        return it->second;
    }
    else {
        return SensorNeuronTypes::UNKNOWN;
    }
}

Config readConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    std::size_t envSize = 0;
    std::string envType;
    std::size_t numCreatures = 0;
    std::size_t maxInternalNeurons = 0;
    std::vector<std::size_t> sensorNeuronsType;
    std::vector<std::size_t> actionNeuronsType;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            std::string value;
            if (std::getline(iss, value)) {
                switch (getConfigKey(key)) {
                case ENV_SIZE:
                    envSize = std::stoul(value);
                    break;
                case ENV_TYPE:
                    envType = value;
                    break;
                case NUM_CREATURES:
                    numCreatures = std::stoul(value);
                    break;
                case MAX_INTERNAL_NEURONS:
                    maxInternalNeurons = std::stoul(value);
                    break;
                case SENSOR_NEURONS_TYPE: {
                    std::istringstream ss(value);
                    std::string neuron;
                    while (ss >> neuron) {
                        ActionNeuronTypes type = getActionNeuron(neuron);
                        if (type != ActionNeuronTypes::UNKNOWN)  actionNeuronsType.push_back((int)type);
                        else {}// Handle unknown neuron if necessary
                    }
                    break;
                }
                case ACTION_NEURONS_TYPE: {
                    std::istringstream ss(value);
                    std::string neuron;
                    while (ss >> neuron) {
                        SensorNeuronTypes type = getSensorNeuron(neuron);
                        if (type != SensorNeuronTypes::UNKNOWN)  actionNeuronsType.push_back((int)type);
                        else {}// Handle unknown neuron if necessary
                    }
                    break;
                }
                case UNKNOWN:
                    // Handle unknown keys if necessary
                    break;
                }
            }
        }
    }

    return Config(envSize, envType, numCreatures, maxInternalNeurons, sensorNeuronsType, actionNeuronsType);
}