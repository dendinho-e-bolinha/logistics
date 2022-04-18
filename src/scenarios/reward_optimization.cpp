#include "scenarios/reward_optimization.h"
#include <algorithm>
#include <iostream>

using namespace std;

#define MAX_KNAPSACK 20
#define WORK_TIME (8 * 60 * 60)

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
                   item.get_seconds() > tl;

  if (cannotFit) {
    boobacube.insert({n, wl, vl, tl}, boobacube.at({n - 1, wl, vl, tl}));
  } else {
    if (boobacube.at({n - 1, wl - item.get_weight(), vl - item.get_volume(),
                      tl - item.get_seconds()}) == -1) {
      knapsack(n - 1, wl - item.get_weight(), vl - item.get_volume(),
               tl - item.get_seconds());
    }

    boobacube.insert(
        {n, wl, vl, tl},
        max(boobacube.at({n - 1, wl, vl, tl}),
            boobacube.at({n - 1, wl - item.get_weight(), vl - item.get_volume(),
                          tl - item.get_seconds()}) +
                item.search_reward));
  }
}

void RewardOptimization::knapsack(const Driver &driver) {
  int numAvailableDeliveries = deliveries.size() - frozenDeliveries;
  int step = min(numAvailableDeliveries, MAX_KNAPSACK);

  knapsack(step, driver.get_max_weight() - driver.current_weight,
           driver.get_max_volume() - driver.current_volume,
           WORK_TIME - driver.used_seconds);
}

const vector<Driver> &RewardOptimization::getDrivers() const {
    return drivers;
}

const vector<Delivery> &RewardOptimization::getDeliveries() const {
    return deliveries;
}

vector<vector<Delivery>::iterator>
RewardOptimization::getSelectedDeliveries(int n, int wl, int vl, int tl) {
  if (n == 0 || wl <= 0 || vl <= 0 || tl <= 0) {
    return {};
  }

  if (boobacube.at({n, wl, vl, tl}) > boobacube.at({n - 1, wl, vl, tl})) {
    vector<Delivery>::iterator it = deliveries.begin() + (n - 1);

    auto rest =
        getSelectedDeliveries(n - 1, wl - it->get_weight(),
                              vl - it->get_volume(), tl - it->get_seconds());
    rest.push_back(it);

    return rest;
  } else {
    return getSelectedDeliveries(n - 1, wl, vl, tl);
  }
}

vector<vector<Delivery>::iterator>
RewardOptimization::getSelectedDeliveries(const Driver &driver) {
  int numAvailableDeliveries = deliveries.size() - frozenDeliveries;
  int step = min(numAvailableDeliveries, MAX_KNAPSACK);

  return getSelectedDeliveries(step,
                               driver.get_max_weight() - driver.current_weight,
                               driver.get_max_volume() - driver.current_volume,
                               WORK_TIME - driver.used_seconds);
}

int RewardOptimization::getReward(int n, int wl, int vl, int tl) {
  return boobacube.at({n, wl, vl, tl});
}

int RewardOptimization::getReward(const Driver &driver) {
  int numAvailableDeliveries = deliveries.size() - frozenDeliveries;
  int step = min(numAvailableDeliveries, MAX_KNAPSACK);

  return getReward(step, driver.get_max_weight() - driver.current_weight,
                   driver.get_max_volume() - driver.current_volume,
                   WORK_TIME - driver.used_seconds);
}

void RewardOptimization::randomizeDeliveries() {
  int numAvailableDeliveries = deliveries.size() - frozenDeliveries;

  for (int i = 0; i < min(numAvailableDeliveries, MAX_KNAPSACK); i++) {
    int deliveriesLeft = numAvailableDeliveries - i;
    int index = (rand() % deliveriesLeft) + i;

    Delivery temp = deliveries.at(i);
    deliveries.at(i) = deliveries.at(index);
    deliveries.at(index) = temp;
  }
}

void RewardOptimization::freezeDelivery(vector<Delivery>::iterator it) {
  int freezerIndex = deliveries.size() - frozenDeliveries - 1;

  Delivery temp = deliveries.at(freezerIndex);
  deliveries.at(freezerIndex) = *it;
  *it = temp;

  frozenDeliveries++;
}

void RewardOptimization::solve() {
  vector<Driver> finishedDrivers;
  vector<Delivery> finishedDeliveries;

  int tries = 0;
  while (tries < 3) {
    if (drivers.empty() || deliveries.empty()) {
      break;
    }

    for (Driver &driver : drivers) {
        driver.is_selected = false;
        driver.current_weight = 0;
        driver.current_volume = 0;
        driver.used_seconds = 0;
    }

    for (Delivery &delivery : deliveries) {
        delivery.selected_driver = -1;
        delivery.search_reward = 0;
    }

    for (int i = 0; i < drivers.size(); i++) {

      frozenDeliveries = 0;
      boobacube.clear();

      Driver &driver = drivers.at(i);
      for (Delivery &delivery : deliveries) {
        delivery.search_reward =
            delivery.selected_driver == -1
                ? delivery.get_normal_reward()
                : drivers.at(delivery.selected_driver).get_daily_cost() -
                      driver.get_daily_cost();
      }

      while (true) {
        randomizeDeliveries();
        knapsack(driver);

        auto selectedDeliveries = getSelectedDeliveries(driver);
        if (selectedDeliveries.empty()) {
          break;
        }

        for (auto it : selectedDeliveries) {
          it->selected_driver = i;

          driver.current_weight += it->get_weight();
          driver.current_volume += it->get_volume();
          driver.used_seconds += it->get_seconds();

          freezeDelivery(it);
        }
      }
    }

    vector<int> profit(drivers.size(), 0);

    for (int i = 0; i < drivers.size(); i++) {
      Driver &driver = drivers.at(i);

      driver.current_weight = 0;
      driver.current_volume = 0;
      driver.used_seconds = 0;

      profit[i] -= driver.get_daily_cost();
    }

    for (Delivery &delivery : deliveries) {
      if (delivery.selected_driver == -1) {
        continue;
      }
      profit[delivery.selected_driver] += delivery.get_normal_reward();
    }

    vector<int> bestDrivers;
    for (int i = 0; i < drivers.size(); i++) {
      bestDrivers.push_back(i);
    }

    sort(bestDrivers.begin(), bestDrivers.end(),
         [&profit](int a, int b) { return profit[a] > profit[b]; });

    for (Delivery &delivery : deliveries) {
      if (delivery.selected_driver == -1 ||
          profit[delivery.selected_driver] < 0) {
        for (int index : bestDrivers) {
          if (profit[index] < 0) {
            break;
          }

          Driver &driver = drivers.at(index);
          int weightLeft = driver.get_max_weight() - driver.current_weight;
          int volumeLeft = driver.get_max_volume() - driver.current_volume;
          int durationLeft = WORK_TIME - driver.used_seconds;

          if (weightLeft >= delivery.get_weight() &&
              volumeLeft >= delivery.get_volume() &&
              durationLeft >= delivery.get_seconds()) {
            delivery.selected_driver = index;

            driver.current_weight += delivery.get_weight();
            driver.current_volume += delivery.get_volume();
            driver.used_seconds += delivery.get_seconds();

            profit[index] += delivery.get_normal_reward();
            break;
          }
        }
      }
    }

    int prevNumDrivers = drivers.size();

    auto currDriver = drivers.begin();
    for (int i = 0; i < drivers.size(); i++) {
      if (profit[i] >= 0) {
        Driver driver = *currDriver;

        driver.is_selected = true;
        finishedDrivers.push_back(driver);

        currDriver = drivers.erase(currDriver);

        auto currDelivery = deliveries.begin();
        for (int j = 0; j < deliveries.size(); j++) {
          Delivery delivery = *currDelivery;
          if (delivery.selected_driver == i) {
            delivery.selected_driver = finishedDrivers.size() - 1;
            finishedDeliveries.push_back(delivery);

            currDelivery = deliveries.erase(currDelivery);
          } else {
            currDelivery++;
          }
        }
      } else {
        currDriver++;
      }
    }

    if (prevNumDrivers == drivers.size()) {
      tries++;
    } else {
      tries = 0;
    }
  }

  for (Driver driver : drivers) {
    driver.is_selected = false;
    driver.current_weight = 0;
    driver.current_volume = 0;
    driver.used_seconds = 0;
    finishedDrivers.push_back(driver);
  }

  for (Delivery delivery : deliveries) {
    delivery.selected_driver = -1;
    finishedDeliveries.push_back(delivery);
  }

  deliveries = finishedDeliveries;
  drivers = finishedDrivers;
}


