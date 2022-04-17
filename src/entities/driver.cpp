#include <string>

#include "entities/driver.h"

using namespace std;

Driver::Driver(int max_volume, int max_weight, int daily_cost, bool is_selected, int current_volume, int current_weight, int used_seconds)
    : max_volume(max_volume), max_weight(max_weight), daily_cost(daily_cost),
      is_selected(is_selected), current_volume(current_volume), current_weight(current_weight),
      used_seconds(used_seconds) {}

Driver::Driver(const Driver &driver) : Driver(driver.get_max_volume(),driver.get_max_weight(), driver.get_daily_cost(), driver.is_selected, driver.current_volume, driver.current_weight, driver.used_seconds) {}

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