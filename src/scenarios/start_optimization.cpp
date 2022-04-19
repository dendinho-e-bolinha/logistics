#include "scenarios/start_optimization.h"
#include "constants.h"
#include <vector>
#include <algorithm>

using namespace std;

StartOptimization::StartOptimization(const vector<Delivery> &deliveries) : deliveries(deliveries) {}


const vector<Delivery> &StartOptimization::getDeliveries() const {
    return deliveries;
}

void StartOptimization::solve() {
    sort(deliveries.begin(), deliveries.end(), [](Delivery &delivery1, Delivery &delivery2) {
        return delivery1.get_seconds() < delivery2.get_seconds();
    });

    int available_seconds = WORK_TIME; // 9 to 5 working time (8 hours)

    deliveries.at(0).starting_time = 0;
    for (int i = 0; i < deliveries.size() - 1; ++i) {
        Delivery &delivery = deliveries.at(i);
        int end = delivery.starting_time + delivery.get_seconds();
        if (end > WORK_TIME) {
            break;
        }

        Delivery &next_delivery = deliveries.at(i + 1);
        next_delivery.starting_time = end;
    }
}