#pragma once

#include <vector>

#include "../entities/delivery.h"
#include "../entities/driver.h"

class StartOptimization {
    /** @brief Vector containing all Deliveries */
    std::vector<Delivery> deliveries;

public:
    /**
    /* @brief Construct a new StartOptimazation object 
    /*
    /* @param drivers
    /* @param deliveries
    */
    StartOptimization(const std::vector<Delivery> &deliveries);

    /**
     * @brief Get the Deliveries object
     * 
     * @return const std::vector<Delivery>& 
     */
    const std::vector<Delivery> &getDeliveries() const;

    /**
     * @brief Solver function for the algorithm
     */
    void solve();
};