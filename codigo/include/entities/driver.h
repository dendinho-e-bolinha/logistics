#pragma once

#include <vector>
#include <string>

/** @brief Manages a Driver */
class Driver {

    /** @brief Max volume a driver can take */
    int max_volume;

    /** @brief Max Weight a driver can take */
    int max_weight;

    /** @brief Daily cost of a driver */
    int daily_cost;

public:

    /**
     * @brief Creates a Driver instance
     */
    Driver(int max_volume, int max_weight, int daily_cost, bool is_selected = false, int current_volume = 0, int current_weight = 0, int used_seconds = 0);

    /**
     * @brief Driver copy constructor
     */
    Driver(const Driver &driver);


    /**
     * @brief Creates a Driver instance from a vector of entries
     * 
     * @param entry 
     * @return Driver instance
     */
    static Driver from_entry(std::vector<std::string> entry);

    /** Getters */
    int get_max_volume() const;
    int get_max_weight() const;
    int get_daily_cost() const;

    // Search results
    bool is_selected;
    int current_volume;
    int current_weight;
    int used_seconds;
};
