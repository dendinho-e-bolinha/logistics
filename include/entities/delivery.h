#pragma once

#include <vector>
#include <string>

class Delivery {

    int volume;
    int weight;
    int normal_reward;
    int seconds, minutes;
    
public:

    Delivery(int volume, int weight, int reward, int seconds, int selected_driver = -1, int search_reward = 0);
    Delivery(const Delivery &delivery);
    static Delivery from_entry(std::vector<std::string> entry);

    int get_volume() const;
    int get_weight() const;
    int get_normal_reward() const;
    int get_seconds() const;
    int get_minutes() const;

    // Search results
    int selected_driver;
    int search_reward;
};
