#pragma once

#include <vector>
#include <functional>

#include "sparse_boobacube.h"
#include "entities/delivery.h"
#include "entities/driver.h"

class RewardOptimization {
    std::vector<Delivery> deliveries;
    std::vector<Driver> drivers;
    std::function<int(const Delivery& delivery, const Driver &driver)> calculateCost;

    SparseBoobacube boobacube;

    void knapsack(int n, int wl, int vl, int tl);

    public:
        RewardOptimization(const std::vector<Delivery> &deliveries, const std::vector<Driver> &drivers, std::function<int(const Delivery&, const Driver&)> calculateCost);

        std::vector<Delivery> &getDeliveries() const;
        std::vector<Driver> &getDrivers() const;
        void solve();
};