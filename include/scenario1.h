#pragma once

#include "entities/driver.h"
#include "entities/delivery.h"

#include <vector>

namespace scenario1 {
    bool can_delivery_fit(const Delivery &delivery, const Driver &driver);
    void solve(std::vector<Driver> &drivers, std::vector<Delivery> &deliveries);
}