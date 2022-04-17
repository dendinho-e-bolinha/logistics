#pragma once

#include <vector>

#include "../entities/delivery.h"
#include "../entities/driver.h"

class StartOptimization {
    std::vector<Driver> drivers;
    std::vector<Delivery> deliveries;

public:
    StartOptimization(const std::vector<Driver> &drivers, const std::vector<Delivery> &deliveries);

    const std::vector<Driver> &getDrivers() const;

    const std::vector<Delivery> &getDeliveries() const;

    float solve();
};