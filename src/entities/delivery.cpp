#include <iostream>
#include <sstream>
#include <string>

#include "entities/delivery.h"

using namespace std;

Delivery::Delivery(int volume, int weight, int reward, int duration)
    : volume(volume), weight(weight), reward(reward), duration(duration) {}

Delivery Delivery::from_entry(std::vector<std::string> entry) {
    int volume = stoi(entry.at(0));
    int weight = stoi(entry.at(1));
    int reward = stoi(entry.at(2));
    int duration = stoi(entry.at(3));

    return Delivery(volume, weight, reward, duration);
}

int Delivery::get_volume() const {
    return volume;
}

int Delivery::get_weight() const {
    return weight;
}

int Delivery::get_reward() const {
    return reward;
}

int Delivery::get_duration() const {
    return duration;
}