#ifndef MYUTILITIES_H
#define MYUTILITIES_H
#include <string>
#include <sstream>
#include <bitset>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Neurons.h"

enum class ActionNeuronTypes { MFR, Mrn, MRL, Mx, My, Kill, UNKNOWN };
enum class SensorNeuronTypes { Age, Rnd, BDy, BDx, BD, Lx, Ly, Osc, UNKNOWN };


template<typename T, typename U>
concept Addable = requires(T a, U b) {
    { a + b };
};

template<typename T, typename U>
concept Multipliable = requires(T a, U b) {
    { a * b };
};

template<typename T, typename U>
std::pair<U, T> swapPairValues(std::pair<T, U> p)
{
    return std::make_pair(p.second, p.first);
}

template<typename T1, typename T2, typename U1, typename U2>
    requires Addable<T1, U1>&& Addable<T2, U2>
auto operator+(const std::pair<T1, T2>& p1, const std::pair<U1, U2>& p2) -> std::pair<decltype(p1.first + p2.first), decltype(p1.second + p2.second)> {
    return std::make_pair(p1.first + p2.first, p1.second + p2.second);
}

template<typename T1, typename T2, typename U1, typename U2>
    requires Multipliable<T1, U1>&& Multipliable<T2, U2>
auto operator*(const std::pair<T1, T2>& p1, const std::pair<U1, U2>& p2) -> std::pair<decltype(p1.first * p2.first), decltype(p1.second * p2.second)> {
    return std::make_pair(p1.first * p2.first, p1.second * p2.second);
}

inline std::pair<int, int> generateRandomDirection() {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, 1); 
    std::uniform_int_distribution<> index_dis(0, 1);
    int index = index_dis(gen);
    std::pair<int, int> result;
    result.first = (index == 0) ? 0 : (dis(gen) == 0 ? 1 : -1);
    result.second = (index == 1) ? 0 : (dis(gen) == 0 ? -1 : 1);

    return result;
}

inline std::string hexToBin(const std::string& hex) {
    static const std::unordered_map<char, std::string> hexToBinMap = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
        {'a', "1010"}, {'b', "1011"}, {'c', "1100"}, {'d', "1101"},
        {'e', "1110"}, {'f', "1111"}
    };

    std::string bin;
    for (char hexChar : hex) {
        if (hexToBinMap.find(hexChar) != hexToBinMap.end()) {
            bin += hexToBinMap.at(hexChar);
        }
        else
        {

        }
    }

    return bin;
}

struct Config
{
    Config(std::size_t envSize,
        std::string envType,
        std::size_t numCreatures,
        std::size_t maxInternalNeurons,
        std::vector<SensorNeuronTypes> activeSensorNeurons = {},
        std::vector<ActionNeuronTypes> activeActionNeurons = {},
        std::size_t numGenes = 0)
        : 
        envSize_(envSize),
        envType_(std::move(envType)),
        numCreatures_(numCreatures),
        maxInternalNeurons_(maxInternalNeurons),
        activeSensorNeurons_(std::move(activeSensorNeurons)),
        activeActionNeurons_(std::move(activeActionNeurons)),
        numGenes_(numGenes)

	{}

	std::size_t envSize_;
	std::string envType_;
	std::size_t numCreatures_;
	std::size_t maxInternalNeurons_;
	std::vector<SensorNeuronTypes> activeSensorNeurons_;
	std::vector<ActionNeuronTypes> activeActionNeurons_;
    std::size_t numGenes_;
};

enum ConfigKey {
    ENV_SIZE,
    ENV_TYPE,
    NUM_CREATURES,
    MAX_INTERNAL_NEURONS,
    SENSOR_NEURONS_TYPE,
    ACTION_NEURONS_TYPE,
    NUM_GENES,
    UNKNOWN
};

inline ConfigKey getConfigKey(const std::string& key) {
    static const std::unordered_map<std::string, ConfigKey> keyMap = {
        {"env_size", ENV_SIZE},
        {"env_type", ENV_TYPE},
        {"num_creatures", NUM_CREATURES},
        {"max_internal_neurons", MAX_INTERNAL_NEURONS},
        {"sensor_neurons_type", SENSOR_NEURONS_TYPE},
        {"action_neurons_type", ACTION_NEURONS_TYPE},
        {"number_of_genes", NUM_GENES}
    };

    auto it = keyMap.find(key);
    if (it != keyMap.end()) {
        return it->second;
    }
    else {
        return UNKNOWN;
    }
}

inline ActionNeuronTypes getActionNeuron(const std::string& name)
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

inline SensorNeuronTypes getSensorNeuron(const std::string& name)
{
    static const std::unordered_map<std::string, SensorNeuronTypes> sensorNeuronMap = {
    {"Age", SensorNeuronTypes::Age},
    {"Rnd", SensorNeuronTypes::Rnd},
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

inline Config readConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    std::size_t envSize = 0;
    std::string envType;
    std::size_t numCreatures = 0;
    std::size_t maxInternalNeurons = 0;
    std::size_t numGenes = 0;
    std::vector<SensorNeuronTypes> sensorNeuronsType;
    std::vector<ActionNeuronTypes> actionNeuronsType;

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
                case NUM_GENES:
                    numGenes = std::stoul(value);
                case SENSOR_NEURONS_TYPE: {
                    std::istringstream ss(value);
                    std::string neuron;
                    while (ss >> neuron) {
                        ActionNeuronTypes type = getActionNeuron(neuron);
                        if (type != ActionNeuronTypes::UNKNOWN)  actionNeuronsType.push_back(type);
                        else {}// Handle unknown neuron if necessary
                    }
                    break;
                }
                case ACTION_NEURONS_TYPE: {
                    std::istringstream ss(value);
                    std::string neuron;
                    while (ss >> neuron) {
                        SensorNeuronTypes type = getSensorNeuron(neuron);
                        if (type != SensorNeuronTypes::UNKNOWN)  sensorNeuronsType.push_back(type);
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

    return Config(envSize, envType, numCreatures, maxInternalNeurons, sensorNeuronsType, actionNeuronsType, numGenes);
}
#endif