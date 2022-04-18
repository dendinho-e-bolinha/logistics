#pragma once

#include <vector>

#include "../entities/delivery.h"
#include "../entities/driver.h"

class StartOptimization {
    /** @brief Vector containing all Drivers */
    std::vector<Driver> drivers;

    /** @brief Vector containing all Deliveries */
    std::vector<Delivery> deliveries;

    /** @brief The average starting time */
    float averageStartingTime;

public:
    /**
    /* @brief Construct a new StartOptimazation object 
    /*
    /* @param drivers
    /* @param deliveries
    */
    StartOptimization(const std::vector<Driver> &drivers, const std::vector<Delivery> &deliveries);

    /**
     * @brief Get the Drivers object
     * 
     * @return const std::vector<Driver>& 
     */
    const std::vector<Driver> &getDrivers() const;

    /**
     * @brief Get the Deliveries object
     * 
     * @return const std::vector<Delivery>& 
     */
    const std::vector<Delivery> &getDeliveries() const;

    /**
     * @brief Get the Average Starting Time object
     * 
     * @return const int 
     */
    const int getAverageStartingTime() const;

    /**
     * @brief Solver function for the algorithm
     */
    void solve();
};