#pragma once

#include <vector>
#include <string>

class Driver {
    int max_volume;
    int max_weight;
    int daily_cost;

public:

    Driver(int max_volume, int max_weight, int daily_cost, bool is_selected = false, int current_volume = 0, int current_weight = 0, int used_seconds = 0);
    Driver(const Driver &driver);
    static Driver from_entry(std::vector<std::string> entry);

    int get_max_volume() const;
    int get_max_weight() const;
    int get_daily_cost() const;

    // Search results
    bool is_selected;
    int current_volume;
    int current_weight;
    int used_seconds;
};
