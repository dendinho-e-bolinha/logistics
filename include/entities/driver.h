#pragma once

#include <vector>
#include <string>

class Driver {
    int max_volume;
    int max_weight;
    int daily_cost;

public:

    Driver(int max_volume, int max_weight, int daily_cost);
    Driver(const Driver &driver);
    static Driver from_entry(std::vector<std::string> entry);

    int get_max_volume() const;
    int get_max_weight() const;
    int get_daily_cost() const;

    // Search results
    bool is_selected;
    int current_volume;
    int current_weight;
    int minutes_used;
};
