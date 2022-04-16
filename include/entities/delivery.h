#pragma once

#include <vector>
#include <string>

class Delivery {

    int volume;
    int weight;
    int normal_reward;
    int duration;
    
public:

    Delivery(int volume, int weight, int reward, int duration);
    Delivery(const Delivery &delivery);
    static Delivery from_entry(std::vector<std::string> entry);

    int get_volume() const;
    int get_weight() const;
    int get_normal_reward() const;
    int get_duration() const;

    // Search results
    int selected_driver;
    int search_reward;
};
