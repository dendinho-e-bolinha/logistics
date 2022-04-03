#include <string>

#include "entities/van.h"

using namespace std;

Van::Van(int max_volume, int max_weight, int daily_cost)
    : max_volume(max_volume), max_weight(max_weight), daily_cost(daily_cost) {}


Van Van::from_entry(std::vector<std::string> entry) {
    int max_volume = stoi(entry.at(0));
    int max_weight = stoi(entry.at(1));
    int daily_cost = stoi(entry.at(2));

    return Van{max_volume, max_weight, daily_cost};
}

int Van::getMaxVolume() const {
    return max_volume;
}

int Van::getMaxWeight() const {
    return max_weight;
}

int Van::getDailyCost() const {
    return daily_cost;
}