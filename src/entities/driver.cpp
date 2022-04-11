#include <string>

#include "entities/driver.h"

using namespace std;

Driver::Driver(int max_volume, int max_weight, int daily_cost)
    : max_volume(max_volume), max_weight(max_weight), daily_cost(daily_cost),
      is_selected(false), current_volume(0), current_weight(0),
      minutes_used(0) {}

Driver Driver::from_entry(std::vector<std::string> entry) {
  int max_volume = stoi(entry.at(0));
  int max_weight = stoi(entry.at(1));
  int daily_cost = stoi(entry.at(2));

  return Driver{max_volume, max_weight, daily_cost};
}

int Driver::get_max_volume() const {
    return max_volume;
}

int Driver::get_max_weight() const {
    return max_weight;
}

int Driver::get_daily_cost() const {
    return daily_cost;
}