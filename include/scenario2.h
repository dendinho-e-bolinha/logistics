#pragma once

#include <vector>

#include "entities/driver.h"
#include "entities/delivery.h"

#define DAY_OF_WORK (8 * 60)
#define INF 0

namespace scenario2 {
    template <typename CostFunction>
    int two_dim_knapsack(Driver &driver, std::vector<Delivery> &deliveries, CostFunction cost_fun);
}