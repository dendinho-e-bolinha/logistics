#pragma once

#include <vector>

#include "../entities/delivery.h"
#include "../entities/driver.h"

class StartOptimization {
    std::vector<Delivery> deliveries;

public:
    StartOptimization(const std::vector<Delivery> &deliveries);

    const std::vector<Delivery> &getDeliveries() const;

    void solve();
};