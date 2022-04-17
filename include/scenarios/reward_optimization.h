#pragma once

#include <vector>

#include "sparse_boobacube.h"
#include "../entities/delivery.h"
#include "../entities/driver.h"

class RewardOptimization {
    std::vector<Driver> drivers;
    std::vector<Delivery> deliveries;

    SparseBoobacube boobacube;
    int frozenDeliveries;

    void knapsack(int n, int wl, int vl, int tl);
    void knapsack(const Driver &driver);

    std::vector<std::vector<Delivery>::iterator> getSelectedDeliveries(int n, int wl, int vl, int tl);
    std::vector<std::vector<Delivery>::iterator> getSelectedDeliveries(const Driver &driver);

    int getReward(int n, int wl, int vl, int tl);
    int getReward(const Driver &driver);

    void randomizeDeliveries();
    void freezeDelivery(std::vector<Delivery>::iterator it);

    public:
        RewardOptimization(const std::vector<Driver> &drivers, const std::vector<Delivery> &deliveries);

    const std::vector<Driver> &getDrivers() const;

    const std::vector<Delivery> &getDeliveries() const;

    void solve();
};