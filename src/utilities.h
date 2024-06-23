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
enum class SensorNeuronTypes { Rnd, BDy, BDx, BD, Lx, Ly, Dens, UNKNOWN };

/**
 * @brief Checks if type T and U can be added together
 */
template<typename T, typename U>
concept Addable = requires(T a, U b) {
    { a + b };
};

/**
 * @brief Checks if type T and U can be multiplied togehter
 */
template<typename T, typename U>
concept Multipliable = requires(T a, U b) {
    { a * b };
};

/**
 * @brief Swaps first and second value in pair
 */
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

/**
 * @brief Generates random pair that contains exactly one 0 and one -1 or 1 respresenting one of the cardinal direction in 2D
 */
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


/**
 * @brief Converts hexadecimal number into decimal number
 */
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
/**
 * @brief Holds all the configurable parameters
 */
struct Config
{
    Config(std::size_t envSize,
        std::string envType,
        std::size_t numCreatures,
        std::size_t maxInternalNeurons,
        std::vector<SensorNeuronTypes> activeSensorNeurons = {},
        std::vector<ActionNeuronTypes> activeActionNeurons = {},
        std::size_t numGenes = 0,
        std::size_t numGenerations=0,
        std::size_t numSteps=0,
        std::size_t killZoneSize=0,
        double mutRate=0)
        : 
        envSize_(envSize),
        envType_(std::move(envType)),
        numCreatures_(numCreatures),
        maxInternalNeurons_(maxInternalNeurons),
        activeSensorNeurons_(std::move(activeSensorNeurons)),
        activeActionNeurons_(std::move(activeActionNeurons)),
        numGenes_(numGenes),
        numGenerations_(numGenerations),
        numSteps_(numSteps),
        killZoneSize_(killZoneSize),
        mutRate_(mutRate)

	{}
    Config()
        :
        envSize_(0),
        envType_(""),
        numCreatures_(0),
        maxInternalNeurons_(0),
        activeSensorNeurons_(),
        activeActionNeurons_(),
        numGenes_(0),
        numGenerations_(0),
        numSteps_(0),
        killZoneSize_(0),
        mutRate_(0)

    {}

	std::size_t envSize_;
	std::string envType_;
	std::size_t numCreatures_;
	std::size_t maxInternalNeurons_;
	std::vector<SensorNeuronTypes> activeSensorNeurons_;
	std::vector<ActionNeuronTypes> activeActionNeurons_;
    std::size_t numGenes_;
    std::size_t numGenerations_;
    std::size_t numSteps_;
    std::size_t killZoneSize_;
    double mutRate_;
};

/**
 * @brief Converts string name of action neuron into enum type
 */
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

/**
 * @brief Converts string name of sensor neuron into enum type
 */
inline SensorNeuronTypes getSensorNeuron(const std::string& name)
{
    static const std::unordered_map<std::string, SensorNeuronTypes> sensorNeuronMap = {
    {"Rnd", SensorNeuronTypes::Rnd},
    {"BDy", SensorNeuronTypes::BDy},
    {"BDx", SensorNeuronTypes::BDx},
    {"BD", SensorNeuronTypes::BD},
    {"Lx", SensorNeuronTypes::Lx},
    {"Ly", SensorNeuronTypes::Ly},
    {"Dens", SensorNeuronTypes::Ly}
    };

    auto it = sensorNeuronMap.find(name);
    if (it != sensorNeuronMap.end()) {
        return it->second;
    }
    else {
        return SensorNeuronTypes::UNKNOWN;
    }
}

#endif