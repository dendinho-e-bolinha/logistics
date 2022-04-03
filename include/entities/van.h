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

    int getMaxVolume() const;
    int getMaxWeight() const;
    int getDailyCost() const;
};
