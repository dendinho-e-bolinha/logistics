#include <iostream>
#include "constants.h"
#include "dataset.h"
#include "entities/delivery.h"
#include <vector>

#include "src/scenario2.cpp"

using namespace std;

int main() {
    File file(DELIVERIES_FILE_PATH);
    vector<Delivery> deliveries;

    for (FileEntry entry : file.get_entries()) {
        Delivery delivery = Delivery::from_entry(entry);
        deliveries.push_back(delivery);
            // cout << delivery.getVolume() << ' ' << delivery.getWeight() << ' ' << delivery.getReward() << ' ' << delivery.getDuration() << endl;
    }

    File file2(VAN_FILE_PATH);
    vector<Driver> drivers;
    
    for (FileEntry entry : file2.get_entries()) {
        Driver driver = Driver::from_entry(entry);
        drivers.push_back(driver);
    }

    // solve(drivers, deliveries);
    
    // for (int i = 0; i < drivers.size(); i++) {
    //     Driver &driver = drivers.at(i);
    //     cout << "\nNumber: " << i << "\nSelected: " << boolalpha << driver.is_selected << "\n"; 
    //     if (driver.is_selected) {
    //         cout << "Volume: " << driver.current_volume << " / " << driver.get_max_volume() << '\n'
    //             << "Weight: " << driver.current_weight << " / " << driver.get_max_weight() << '\n'
    //             << "Duration: " << driver.minutes_used << " / " << (24 * 60) << '\n';
    //     } else break;
    // }

    // for (int i = 0; i < deliveries.size(); i++) {
    //     Delivery &delivery = deliveries.at(i);
    //     cout << "\nNumber: " << i << "\nSelected: " << boolalpha << (delivery.selected_driver != -1) << '\n'; 
    //     if (delivery.selected_driver != -1) {
    //         cout << "Driver: " << delivery.selected_driver << '\n';
    //     }
    // }

    Driver babyDriver(60, 60, 12);
    vector<Delivery> babyIpad = { 
        { 2, 2, 51, 4 }, //
        { 3, 3, 12, 3 },
        { 4, 4, 100, 1 }, 
        { 6, 6, 67, 1 }, //
        { 8, 8, 1, 300 }, 
        { 12, 12, 49, 1 }, //
        { 10, 10, 50, 1 }
    };

    cout << two_dim_knapsack(babyDriver, babyIpad, [](Delivery delivery, Driver driver) {
        return delivery.get_reward();
    }) << endl;

}
