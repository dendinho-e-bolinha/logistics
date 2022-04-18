#include "scenarios/start_optimization.h"

#include <vector>
#include <algorithm>

using namespace std;

StartOptimization::StartOptimization(const vector<Driver> &drivers, const vector<Delivery> &deliveries) : drivers(
        drivers), deliveries(deliveries), averageStartingTime(0) {}

const vector<Driver> &StartOptimization::getDrivers() const {
    return drivers;
}

const vector<Delivery> &StartOptimization::getDeliveries() const {
    return deliveries;
}

void StartOptimization::solve() {
    sort(deliveries.begin(), deliveries.end(), [](Delivery &delivery1, Delivery &delivery2) {
        return delivery1.get_seconds() < delivery2.get_seconds();
    });

    int available_seconds = 8 * 3600; // 9 to 5 working time (8 hours)
    int sum_starting_time = 0;
    int deliveries_made = 0;

    deliveries.at(0).starting_time = 0;

    for (int i = 1; i < deliveries.size(); ++i) {
        Delivery &delivery = deliveries.at(i);
        Delivery &previous_delivery = deliveries.at(i - 1);
        
        delivery.starting_time = previous_delivery.starting_time + previous_delivery.get_seconds();
        if (delivery.starting_time > available_seconds) {
            break;
        }

        sum_starting_time += delivery.starting_time;
        deliveries_made++;
    }

    averageStartingTime = 9 + sum_starting_time / ((float) (deliveries_made * 3600));
}