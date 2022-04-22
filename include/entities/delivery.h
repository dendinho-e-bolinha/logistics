#pragma once

#include <vector>
#include <string>

/** @brief Manages a elivery */
class Delivery {

    /** @brief Volume of a delivery */
    int volume;

    /** @brief Weight of a delivery */
    int weight;

    /** @brief reward of a delivery */
    int normal_reward;

    /** @brief time a delivery takes to ship */
    int seconds, minutes;
    
public:

    /**
     * @brief Creates a Delivery instance
     */
    Delivery(int volume, int weight, int reward, int seconds, int selected_driver = -1, int search_reward = 0, int starting_time = 0);

    /**
     * @brief Delivery copy constructor
     */
    Delivery(const Delivery &delivery);

    /**
     * @brief Creates a Delivery instance from a vector of entries
     * 
     * @param entry 
     * @return Delivery instance
     */
    static Delivery from_entry(std::vector<std::string> entry);

    /** Getters */
    int get_volume() const;
    int get_weight() const;
    int get_normal_reward() const;
    int get_seconds() const;

    // Reward optimization
    int selected_driver;
    int search_reward;
    
    // Start optimization
    int starting_time;
};
