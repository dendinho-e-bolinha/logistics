#include <iostream>
#include <sstream>
#include <string>

#include "entities/delivery.h"

using namespace std;

Delivery::Delivery(int volume, int weight, int normal_reward, int seconds, int selected_driver, int search_reward, int starting_time)
    : volume(volume), weight(weight), normal_reward(normal_reward),
      seconds(seconds), selected_driver(selected_driver), search_reward(search_reward), starting_time(starting_time) {
  int minutes = seconds / 60;
  this->minutes = seconds % 60 == 0 ? minutes : minutes + 1;
}

Delivery::Delivery(const Delivery &delivery)
    : Delivery(delivery.get_volume(), delivery.get_weight(), delivery.get_normal_reward(),
      delivery.get_seconds(),
      delivery.selected_driver,
      delivery.search_reward) {}

Delivery Delivery::from_entry(std::vector<std::string> entry) {
  int volume = stoi(entry.at(0));
  int weight = stoi(entry.at(1));
  int normal_reward = stoi(entry.at(2));
  int duration = stoi(entry.at(3));

  return Delivery(volume, weight, normal_reward, duration);
}

int Delivery::get_volume() const { return volume; }

int Delivery::get_weight() const { return weight; }

int Delivery::get_normal_reward() const { return normal_reward; }

int Delivery::get_seconds() const { return seconds; }
