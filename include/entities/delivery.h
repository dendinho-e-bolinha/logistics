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

    int getVolume() const;
    int getWeight() const;
    int getReward() const;
    int getDuration() const;
};
