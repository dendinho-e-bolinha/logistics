#include <iostream>
#include "constants.h"
#include "dataset.h"
#include "entities/delivery.h"
#include "entities/driver.h"
#include <vector>
#include <thread>

#include "src/knapsack.cpp"

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

    // Driver babyDriver(6, 6, 12);
    // vector<Delivery> babyIpad = { 
    //     { 2, 2, 51, 4 }, //
    //     { 3, 3, 12, 3 },
    //     { 4, 4, 100, 1 }, 
    //     { 6, 6, 67, 1 }, //
    //     { 8, 8, 1, 300 }, 
    //     { 12, 12, 49, 1 }, //
    //     { 10, 10, 50, 1 }
    // };

    SparseBoobacube boobacube;
    knapsack(boobacube, deliveries, deliveries.size(), drivers.at(0).get_max_weight(), drivers.at(0).get_max_volume(), 8 * 60);

    cout << boobacube.at({ deliveries.size(), drivers.at(0).get_max_weight(), drivers.at(0).get_max_volume(), 8 * 60 }) << endl;


    // bool running[1];
    // for (int i = 0; i < sizeof(running); i++) {
    //     running[i] = false;
    // }

    // for (Driver &driver : drivers) {
    //     int available_index;
    //     while (running[available_index]) {
    //         available_index++;
    //         available_index %= sizeof(running);
    //     }

    //     running[available_index] = true;
    //     thread t([&running, available_index, &driver, &deliveries]() {

    //         cout << "\n\n\n\n\n";
    //         auto entry = two_dim_knapsack(driver, deliveries, [](Delivery delivery, Driver driver) {
    //             return delivery.get_reward();
    //         }, available_index);

    //         cout << "(#" << available_index << ") " << entry.n << ' ' << entry.reward << ' ' << entry.weight << ' ' << entry.volume << ' ' << entry.duration << endl << endl;

    //         auto de = find_deliveries(driver, deliveries, entry, [](Delivery delivery, Driver driver) {
    //             return delivery.get_reward();
    //         }, available_index);

    //         for (auto d : de) {
    //             cout << "(#" << available_index << ") " << d.get_volume() << ' ' << d.get_weight() << ' ' << d.get_reward() << ' ' << d.get_duration() << endl;
    //         }

    //         running[available_index] = false;
    //     });

    //     t.detach();
    // }
}
