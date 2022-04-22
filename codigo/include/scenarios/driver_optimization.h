#pragma once

#include <vector>

#include "../entities/delivery.h"
#include "../entities/driver.h"

/** @brief Manages the algorithms needed to solve scenario 1 */
class DriverOptimization {

    /** @brief Vector containing all Drivers */
    std::vector<Driver> drivers;

    /** @brief Vector containing all Deliveries */
    std::vector<Delivery> deliveries;

    /**
     * @brief Checks if a delivery can still be delivered by a certain Driver
     * 
     * @param delivery Delivery instance
     * @param driver Driver instance
     * @return true if the delivery can fit
     * @return false if the delivery can't fit
     */
    bool can_delivery_fit(const Delivery &delivery, const Driver &driver);
public:

    /**
     * @brief Construct a new DriverOptimization object
     * 
     * @param drivers 
     * @param deliveries 
     */
    DriverOptimization(const std::vector<Driver> &drivers, const std::vector<Delivery> &deliveries);

    /** Getters */
    const std::vector<Driver> &getDrivers() const;
    const std::vector<Delivery> &getDeliveries() const;

    void solve();
};