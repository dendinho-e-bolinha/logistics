#include <iostream>
#include <string.h>
#include <vector>

#include "scenario1.h"

using namespace std;

bool scenario1::can_delivery_fit(const Delivery &delivery, const Driver &driver) {
    return driver.current_volume + delivery.get_volume() <= driver.get_max_volume()
        && driver.current_weight + delivery.get_weight() <= driver.get_max_weight()
        && driver.minutes_used + delivery.get_duration() <= 24 * 3600;
}

void scenario1::solve(vector<Driver> &drivers, vector<Delivery> &deliveries) {
    if (drivers.empty() || deliveries.empty()) {
        return;
    }



    int selected_until = 0;
    for (Delivery &delivery : deliveries) {
        int fits_in = -1;

        for (int i = 0; i < selected_until; i++) {
            if (can_delivery_fit(delivery, drivers.at(i))) {
                fits_in = i;
                break;
            }
        }

        if (fits_in == -1) {
            // Open a new bin
            vector<int> available_bins;
            for (int i = 0; i < drivers.size(); i++) {
                Driver &driver = drivers.at(i);
                if (can_delivery_fit(delivery, driver)) {
                    available_bins.push_back(i);
                }
            }

            if (available_bins.size() > 0) {
                int selected_bin = 0;

                // Randomly select bin
                // ...

                Driver temp = drivers.at(available_bins.at(selected_bin));
                drivers.at(available_bins.at(selected_bin)) = drivers.at(selected_until);
                drivers.at(selected_until) = temp;

                drivers.at(selected_until).is_selected = true;
                delivery.selected_driver = selected_until;


                drivers.at(selected_until).current_volume += delivery.get_volume();
                drivers.at(selected_until).current_weight += delivery.get_weight();
                drivers.at(selected_until).minutes_used += delivery.get_duration();

                selected_until++;
            }
        } else {
            // Place item in bin
            delivery.selected_driver = fits_in;

            Driver &selected_driver = drivers.at(fits_in);
            selected_driver.current_volume += delivery.get_volume();
            selected_driver.current_weight += delivery.get_weight();
            selected_driver.minutes_used += delivery.get_duration();
        }
    }
}