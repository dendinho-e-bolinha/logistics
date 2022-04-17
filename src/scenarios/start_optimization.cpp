#include "scenarios/start_optimization.h"

#include <vector>
#include <algorithm>

using namespace std;

StartOptimization::StartOptimization(const vector<Driver> &drivers, const vector<Delivery> &deliveries) : drivers(
        drivers), deliveries(deliveries) {}

const vector<Driver> &StartOptimization::getDrivers() const {
    return drivers;
}

const vector<Delivery> &StartOptimization::getDeliveries() const {
    return deliveries;
}

float StartOptimization::solve() {
    sort(deliveries.begin(), deliveries.end(), [](Delivery &delivery1, Delivery &delivery2) {
        return delivery1.get_minutes() < delivery2.get_minutes();
    });

    int average_starting_time = 0;
    int minutes_remaining = 480; // 9 to 5 working time
    int deliveries_made = 0;

    int i;

    for (i = 0; i < deliveries.size(); ++i) {
        if (deliveries.at(i).get_seconds() <= minutes_remaining) {
            average_starting_time += average_starting_time + deliveries.at(i).get_seconds();
            minutes_remaining -= deliveries.at(i).get_seconds();
            deliveries_made++;
            if (minutes_remaining < deliveries.at(i).get_seconds())
                break;
        }
    }

    average_starting_time -= deliveries.at(i).get_seconds();
    average_starting_time /= 2;

    return 9 + average_starting_time / (float) deliveries_made / 60.0;  // Average in hours starting at 9am
}