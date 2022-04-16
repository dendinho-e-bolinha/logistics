#include <vector>
#include <iostream>
#include <string.h>
#include <algorithm>

#include "entities/delivery.h"
#include "entities/driver.h"

using namespace std;

float solve(vector<Delivery> &deliveries) {
    sort(deliveries.begin(), deliveries.end(), [](Delivery &delivery1, Delivery &delivery2) {
        return delivery1.get_minutes() < delivery2.get_minutes();
    });

    int average_starting_time = 0;
    int minutes_remaining = 480; // 9 to 5 working time
    int deliveries_made = 0;
    
    for (int i = 0; i < deliveries.size(); i++) {
        if (deliveries.at(i).get_minutes() <= minutes_remaining) {
            average_starting_time += average_starting_time + deliveries.at(i).get_minutes();
            minutes_remaining -= deliveries.at(i).get_minutes();
            deliveries_made++;
            if (minutes_remaining < deliveries.at(i).get_minutes()) {
                average_starting_time -= deliveries.at(i).get_minutes();
                average_starting_time /= 2;
                break;
            }
        }
    }


    return 9 + average_starting_time / (float) deliveries_made / 60.0;  // Average in hours starting at 9am
}
