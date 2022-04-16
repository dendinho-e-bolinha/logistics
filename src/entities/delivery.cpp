#include <iostream>
#include <sstream>
#include <string>

#include "entities/delivery.h"

using namespace std;

Delivery::Delivery(int volume, int weight, int normal_reward, int duration)
    : volume(volume), weight(weight), normal_reward(normal_reward), duration(duration), selected_driver(-1), search_reward(0) {}

Delivery::Delivery(const Delivery &delivery) : Delivery(delivery.get_volume(), delivery.get_weight(), delivery.get_normal_reward(), delivery.get_duration()) {}

Delivery Delivery::from_entry(std::vector<std::string> entry) {
    int volume = stoi(entry.at(0));
    int weight = stoi(entry.at(1));
    int normal_reward = stoi(entry.at(2));
    int duration = stoi(entry.at(3));

    return Delivery(volume, weight, normal_reward, duration);
}

int Delivery::get_volume() const {
    return volume;
}

int Delivery::get_weight() const {
    return weight;
}

int Delivery::get_normal_reward() const {
    return normal_reward;
}

int Delivery::get_duration() const {
    return duration;
}