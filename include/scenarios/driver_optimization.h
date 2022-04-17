#pragma once

#include <vector>

#include "../entities/delivery.h"
#include "../entities/driver.h"

class DriverOptimization {
    std::vector<Driver> drivers;
    std::vector<Delivery> deliveries;

    bool can_delivery_fit(const Delivery &delivery, const Driver &driver);
public:
    DriverOptimization(const std::vector<Driver> &drivers, const std::vector<Delivery> &deliveries);

    const std::vector<Driver> &getDrivers() const;
    const std::vector<Delivery> &getDeliveries() const;

    void solve();
};