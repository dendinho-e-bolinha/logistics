#include "scenarios/reward_optimization.h"
#include <iostream>

using namespace std;

#define WORK_TIME (16 * 60)

RewardOptimization::RewardOptimization(const vector<Driver> &drivers,
                                       const vector<Delivery> &deliveries)
    : drivers(drivers), deliveries(deliveries) {}

void RewardOptimization::knapsack(int n, int wl, int vl, int tl) {
  if (n == 0 || wl <= 0 || vl <= 0 || tl <= 0) {
    boobacube.insert({n, wl, vl, tl}, 0);
    return;
  }

  if (boobacube.at({n - 1, wl, vl, tl}) == -1) {
    knapsack(n - 1, wl, vl, tl);
  }

  const Delivery &item = deliveries.at(n - 1);
  bool cannotFit = item.get_weight() > wl || item.get_volume() > vl ||
                   item.get_duration() > tl;

  if (cannotFit) {
    boobacube.insert({n, wl, vl, tl}, boobacube.at({n - 1, wl, vl, tl}));
  } else {
    if (boobacube.at({n - 1, wl - item.get_weight(), vl - item.get_volume(),
                      tl - item.get_duration()}) == -1) {
      knapsack(n - 1, wl - item.get_weight(), vl - item.get_volume(),
               tl - item.get_duration());
    }

    boobacube.insert(
        {n, wl, vl, tl},
        max(boobacube.at({n - 1, wl, vl, tl}),
            boobacube.at({n - 1, wl - item.get_weight(), vl - item.get_volume(),
                          tl - item.get_duration()}) +
                item.search_reward));
  }
}

void RewardOptimization::knapsack(const Driver &driver) {
  knapsack(static_cast<int>(deliveries.size()), driver.get_max_weight(),
           driver.get_max_volume(), WORK_TIME);
}

vector<vector<Delivery>::iterator>
RewardOptimization::getSelectedDeliveries(int n, int wl, int vl, int tl) {
  if (n == 0) {
    return {};
  }

  if (boobacube.at({n, wl, vl, tl}) > boobacube.at({n - 1, wl, vl, tl})) {
    vector<Delivery>::iterator it = deliveries.begin() + (n - 1);

    auto rest =
        getSelectedDeliveries(n - 1, wl - it->get_weight(),
                              vl - it->get_volume(), tl - it->get_duration());
    rest.push_back(it);

    return rest;
  } else {
    return getSelectedDeliveries(n - 1, wl, vl, tl);
  }
}

vector<vector<Delivery>::iterator>
RewardOptimization::getSelectedDeliveries(const Driver &driver) {
  return getSelectedDeliveries(static_cast<int>(deliveries.size()),
                               driver.get_max_weight(), driver.get_max_volume(),
                               WORK_TIME);
}

int RewardOptimization::getReward(int n, int wl, int vl, int tl) {
    return boobacube.at({ n, wl, vl, tl });
}

int RewardOptimization::getReward(const Driver &driver) {
    return getReward(deliveries.size(), driver.get_max_weight(), driver.get_max_volume(), WORK_TIME);
}

vector<Driver> RewardOptimization::getDrivers() const { return drivers; }

vector<Delivery> RewardOptimization::getDeliveries() const {
  return deliveries;
}

void RewardOptimization::solve() {
  for (int i = 0; i < drivers.size(); i++) {
    cout << "Driver " << (i + 1) << "/" << drivers.size() << endl;
    boobacube.clear();
    Driver &driver = drivers.at(i);

    for (Delivery &delivery : deliveries) {
      delivery.search_reward =
          delivery.selected_driver == -1
              ? delivery.get_normal_reward()
              : drivers.at(delivery.selected_driver).get_daily_cost();

        // cout << "Search Reward: " << delivery.search_reward << endl;
    }

    // cout << "Daily cost: " << driver.get_daily_cost() << endl;

    knapsack(driver);

    cout << "Reward: " << getReward(driver) << endl;

    if (getReward(driver) - driver.get_daily_cost() > 0) {
        cout << "Profit!" << endl;
        auto selectedDeliveries = getSelectedDeliveries(driver);
        for (auto it : selectedDeliveries) {
            it->selected_driver = i;
        }
    }
  }
}