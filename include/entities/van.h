#pragma once

#include <vector>
#include <string>

class Van {
    int max_volume;
    int max_weight;
    int daily_cost;

public:
    Van(int max_volume, int max_weight, int daily_cost);
    static Van from_entry(std::vector<std::string> entry);

    int get_max_volume() const;
    int get_max_weight() const;
    int get_daily_cost() const;
};
