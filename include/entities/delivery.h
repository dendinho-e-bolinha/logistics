#pragma once

#include <vector>
#include <string>

class Delivery {

    int volume;
    int weight;
    int reward;
    int duration;
    
public:

    Delivery(int volume, int weight, int reward, int duration);
    static Delivery from_entry(std::vector<std::string> entry);

    int get_volume() const;
    int get_weight() const;
    int get_reward() const;
    int get_duration() const;
};
