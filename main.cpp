// #include <iostream>
// #include "constants.h"
// #include "dataset.h"
// #include "entities/delivery.h"
// #include "entities/driver.h"
// #include <vector>
// #include <thread>

// #include "scenarios/reward_optimization.h"

// using namespace std;

// int main() {
//     srand(time(NULL)); rand();
//     File file(DELIVERIES_FILE_PATH);
//     vector<Delivery> deliveries;

//     for (FileEntry entry : file.get_entries()) {
//         Delivery delivery = Delivery::from_entry(entry);
//         deliveries.push_back(delivery);
//             // cout << delivery.getVolume() << ' ' << delivery.getWeight() <<
//             ' ' << delivery.getReward() << ' ' << delivery.getDuration() <<
//             endl;
//     }

//     File file2(VAN_FILE_PATH);
//     vector<Driver> drivers;

//     for (FileEntry entry : file2.get_entries()) {
//         Driver driver = Driver::from_entry(entry);
//         drivers.push_back(driver);
//     }

//     // solve(drivers, deliveries);

//     // for (int i = 0; i < drivers.size(); i++) {
//     //     Driver &driver = drivers.at(i);
//     //     cout << "\nNumber: " << i << "\nSelected: " << boolalpha <<
//     driver.is_selected << "\n";
//     //     if (driver.is_selected) {
//     //         cout << "Volume: " << driver.current_volume << " / " <<
//     driver.get_max_volume() << '\n'
//     //             << "Weight: " << driver.current_weight << " / " <<
//     driver.get_max_weight() << '\n'
//     //             << "Duration: " << driver.minutes_used << " / " << (24 *
//     60) << '\n';
//     //     } else break;
//     // }

//     // for (int i = 0; i < deliveries.size(); i++) {
//     //     Delivery &delivery = deliveries.at(i);
//     //     cout << "\nNumber: " << i << "\nSelected: " << boolalpha <<
//     (delivery.selected_driver != -1) << '\n';
//     //     if (delivery.selected_driver != -1) {
//     //         cout << "Driver: " << delivery.selected_driver << '\n';
//     //     }
//     // }

//     // Driver babyDriver(6, 6, 12);
//     // vector<Delivery> babyIpad = {
//     //     { 2, 2, 51, 4 }, //
//     //     { 3, 3, 12, 3 },
//     //     { 4, 4, 100, 1 },
//     //     { 6, 6, 67, 1 }, //
//     //     { 8, 8, 1, 300 },
//     //     { 12, 12, 49, 1 }, //
//     //     { 10, 10, 50, 1 }
//     // };

//     // SparseBoobacube boobacube;
//     // knapsack(boobacube, deliveries, deliveries.size(),
//     drivers.at(0).get_max_weight(), drivers.at(0).get_max_volume(), 8 * 60);

//     // cout << boobacube.at({ deliveries.size(),
//     drivers.at(0).get_max_weight(), drivers.at(0).get_max_volume(), 8 * 60 })
//     << endl;

//     // cout << boobacube.size() << endl;
//     // cout << boobacube.max_size() << endl;

//     // bool running[1];
//     // for (int i = 0; i < sizeof(running); i++) {
//     //     running[i] = false;
//     // }

//     // for (Driver &driver : drivers) {
//     //     int available_index;
//     //     while (running[available_index]) {
//     //         available_index++;
//     //         available_index %= sizeof(running);
//     //     }

//     //     running[available_index] = true;
//     //     thread t([&running, available_index, &driver, &deliveries]() {

//     //         cout << "\n\n\n\n\n";
//     //         auto entry = two_dim_knapsack(driver, deliveries, [](Delivery
//     delivery, Driver driver) {
//     //             return delivery.get_reward();
//     //         }, available_index);

//     //         cout << "(#" << available_index << ") " << entry.n << ' ' <<
//     entry.reward << ' ' << entry.weight << ' ' << entry.volume << ' ' <<
//     entry.duration << endl << endl;

//     //         auto de = find_deliveries(driver, deliveries, entry,
//     [](Delivery delivery, Driver driver) {
//     //             return delivery.get_reward();
//     //         }, available_index);

//     //         for (auto d : de) {
//     //             cout << "(#" << available_index << ") " << d.get_volume()
//     << ' ' << d.get_weight() << ' ' << d.get_reward() << ' ' <<
//     d.get_duration() << endl;
//     //         }

//     //         running[available_index] = false;
//     //     });

//     //     t.detach();
//     // }

//     RewardOptimization opt(drivers, deliveries);
//     opt.solve();

//     vector<int> profits(drivers.size(), 0);
//     for (int i = 0; i < profits.size(); i++) {
//         profits[i] -= drivers[i].get_daily_cost();
//     }

//     for (const Delivery &delivery : opt.getDeliveries()) {
//         if (delivery.selected_driver != -1) {
//             cout << "Delivered" << endl;
//             profits[delivery.selected_driver] +=
//             delivery.get_normal_reward();
//         } else {
//             cout << "Not delivered" << endl;
//         }
//     }

//     int sum = 0;
//     for (int i = 0; i < profits.size(); i++) {
//         // if (profits[i] != -drivers[i].get_daily_cost()) {
//             // sum += profits[i];
//             cout << profits[i] << endl;
//         // }
//     }

//     cout << endl << endl << sum << endl;
// }

#include "constants.h"
#include "dataset.h"
#include "entities/delivery.h"
#include "entities/driver.h"
#include <iostream>
#include <thread>
#include <vector>

#include "scenarios/driver_optimization.h"
#include "scenarios/reward_optimization.h"
#include "scenarios/sparse_boobacube.h"
#include "scenarios/start_optimization.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <set>

#include <iostream>

using namespace std;

void duration(vector<Delivery> deliveries, vector<Driver> drivers,
              ofstream &out) {
  RewardOptimization caso(drivers, deliveries);
  auto start = chrono::high_resolution_clock::now();
  caso.solve();
  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

  out << drivers.size() << "," << deliveries.size() << "," << duration.count()
      << endl;
}

vector<Delivery> create_sample(vector<Delivery> deliveries, int sample_size) {
  int max = deliveries.size() - 1;
  set<int> indexes;
  while (indexes.size() < sample_size) {
    indexes.insert((int)(rand() % max));
  }

  vector<Delivery> result;
  for (int i : indexes) {
    result.push_back(deliveries.at(i));
  }

  return result;
}

vector<Driver> create_sample(vector<Driver> drivers, int sample_size) {
  int max = drivers.size() - 1;
  set<int> indexes;
  while (indexes.size() < sample_size) {
    indexes.insert((int)(rand() % max));
  }

  vector<Driver> result;
  for (int i : indexes) {
    result.push_back(drivers.at(i));
  }

  return result;
}

int main(int argc, char const *argv[]) {

  srand(time(NULL));
  rand();
  File file(DELIVERIES_FILE_PATH);
  vector<Delivery> deliveries;

  for (FileEntry entry : file.get_entries()) {
    Delivery delivery = Delivery::from_entry(entry);
    deliveries.push_back(delivery);
    // cout << delivery.getVolume() << ' ' << delivery.getWeight() << ' ' <<
    // delivery.getReward() << ' ' << delivery.getDuration() << endl;
  }

  File file2(VAN_FILE_PATH);
  vector<Driver> drivers;

  for (FileEntry entry : file2.get_entries()) {
    Driver driver = Driver::from_entry(entry);
    drivers.push_back(driver);
  }

  ofstream out;
  out.open("data2.csv");

//   for (int i = 0; i < ; i++) {
    vector<Delivery> ten = create_sample(deliveries, 10);
    vector<Delivery> fifty = create_sample(deliveries, 50);
    vector<Delivery> hund = create_sample(deliveries, 100);
    vector<Delivery> twohun = create_sample(deliveries, 200);
    vector<Delivery> threehun = create_sample(deliveries, 300);

    vector<Driver> tend = create_sample(drivers, 10);
    vector<Driver> twenty = create_sample(drivers, 20);
    vector<Driver> thirty = create_sample(drivers, 30);
    vector<Driver> fourty = create_sample(drivers, 40);

    // 8

    cout << "Generated" << endl;

    duration(ten, tend, out);
    cout << 1 << endl;
    duration(ten, twenty, out);
    cout << 2 << endl;
    duration(ten, thirty, out);
    cout << 3 << endl;
    duration(ten, fourty, out);
    cout << 4 << endl;
    duration(ten, drivers, out);

    cout << 5 << endl;
    duration(fifty, tend, out);
    cout << 6 << endl;
    duration(fifty, twenty, out);
    cout << 7 << endl;
    duration(fifty, thirty, out);
    cout << 8 << endl;
    duration(fifty, fourty, out);
    cout << 9 << endl;
    duration(fifty, drivers, out);

    cout << 10 << endl;
    duration(hund, tend, out);
    cout << 11 << endl;
    duration(hund, twenty, out);
    cout << 12 << endl;
    duration(hund, thirty, out);
    cout << 13 << endl;
    duration(hund, fourty, out);
    cout << 14 << endl;
    duration(hund, drivers, out);

    cout << 15 << endl;
    duration(twohun, tend, out);
    cout << 16 << endl;
    duration(twohun, twenty, out);
    cout << 17 << endl;
    duration(twohun, thirty, out);
    cout << 18 << endl;
    duration(twohun, fourty, out);
    cout << 19 << endl;
    duration(twohun, drivers, out);

    cout << 20 << endl;
    duration(threehun, tend, out);
    cout << 21 << endl;
    duration(threehun, twenty, out);
    cout << 22 << endl;
    duration(threehun, thirty, out);
    cout << 23 << endl;
    duration(threehun, fourty, out);
    cout << 24 << endl;
    duration(threehun, drivers, out);

    cout << 25 << endl;
    duration(deliveries, tend, out);
    cout << 26 << endl;
    duration(deliveries, twenty, out);
    cout << 27 << endl;
    duration(deliveries, thirty, out);
    cout << 28 << endl;
    duration(deliveries, fourty, out);
    cout << 29 << endl;
    duration(deliveries, drivers, out);
//   }
  out.close();

  // try {

  //     UI ui = (argc == 2) ? UI(argv[1]) : UI();

  //     ui.start();
  // } catch(exception e) {
  //     cout << "An error has occurred: " << e.what() << endl;
  // }
}