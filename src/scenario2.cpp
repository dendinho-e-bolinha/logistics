// #pragma once

#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <limits.h>

#include "entities/delivery.h"
#include "entities/driver.h"

#define DAY_OF_WORK (8 * 60)
#define INF 0

using namespace std;

struct KnapsackEntry {
    int n;
    int reward;
    int weight;
    int volume;
    int duration;
};

template <typename CostFunction>
KnapsackEntry two_dim_knapsack(Driver &driver, vector<Delivery> &deliveries, CostFunction cost_fun) {
    int N = deliveries.size();
    int WL = driver.get_max_weight();
    int VL = driver.get_max_volume();
    int TL = DAY_OF_WORK;

    vector<vector<vector<KnapsackEntry>>> reward(
        WL + 1,
        vector<vector<KnapsackEntry>>(
            VL + 1,
            vector<KnapsackEntry>(TL + 1, { 0, 0, 0, 0, 0 })
        )
    );

    vector<vector<vector<KnapsackEntry>>> previousReward = reward;

    // Apply algorithm
    for (int i = 1; i <= N; ++i) {
        int realIndex = i - 1;
        Delivery &delivery = deliveries.at(realIndex);

        int itemWeight = delivery.get_weight();
        int itemVolume = delivery.get_volume();
        int itemDuration = delivery.get_duration();
        int itemReward = cost_fun(delivery, driver);

        previousReward = reward;
        
        for (int currWeight = 1; currWeight <= WL; currWeight++) {
            for (int currVolume = 1; currVolume <= VL; currVolume++) {
                for (int currDuration = 1; currDuration <= TL; currDuration++) {
                    int weightLeft = currWeight - itemWeight;
                    int volumeLeft = currVolume - itemVolume;
                    int durationLeft = currDuration - itemDuration;
                    bool canFit = weightLeft >= 0 && volumeLeft >= 0 && durationLeft >= 0;

                    KnapsackEntry &currentEntry = previousReward[currWeight][currVolume][currDuration];
                    if (canFit) {
                        // In this case, we can add the item to the knapsack
                        // so we test if it is worth it

                        KnapsackEntry &previousEntry = previousReward[weightLeft][volumeLeft][durationLeft];

                        int possibleReward = previousEntry.reward + itemReward;
                        if (possibleReward > currentEntry.reward) {
                            int possibleN = previousEntry.n + 1;
                            int possibleWeight = previousEntry.weight + itemWeight;
                            int possibleVolume = previousEntry.volume + itemVolume;
                            int possibleDuration = previousEntry.duration + itemDuration;

                            reward[currWeight][currVolume][currDuration] = { possibleN, possibleReward, possibleWeight, possibleVolume, possibleDuration };
                            continue;
                        }
                    }
                    
                    reward[currWeight][currVolume][currDuration] = currentEntry;
                }
            }
        }
    }

    return reward[WL][VL][TL];
}

template <typename CostFunction>
int compareToEntry(const Driver &driver, const vector<vector<Delivery>::iterator> &iterators, KnapsackEntry entry, CostFunction cost_fun) {
    int sumReward = 0;
    int sumWeight = 0;
    int sumVolume = 0;
    int sumDuration = 0;
    for (auto it : iterators) {
        sumReward += cost_fun(*it, driver);
        sumWeight += it->get_duration();
        sumVolume += it->get_volume();
        sumDuration += it->get_duration();
    }

    if (sumReward == entry.reward) {
        if (sumWeight == entry.weight) {
            if (sumVolume == entry.volume) {
                if (sumDuration == entry.duration) {
                    return 0;
                } else if (sumDuration < entry.duration) {
                    return -1;
                } else {    
                    return 1;
                }
            } else if (sumVolume < entry.volume) {
                return -1;
            } else {
                return 1;
            }
        } else if (sumWeight < entry.weight) {
            return -1;
        } else {
            return 1;
        }
    } else if (sumReward < entry.reward) {
        return -1;
    } else {
        return 1;
    }
}

template <typename CostFunction>
vector<Delivery> find_deliveries(Driver &driver, vector<Delivery> &deliveries, KnapsackEntry entry, CostFunction cost_fun) {
    sort(deliveries.begin(), deliveries.end(), [&driver](Delivery &d1, Delivery &d2) {
        int cost1 = cost_fun(d1, driver);
        int cost2 = cost_fun(d2, driver);
        return cost1 < cost2 || (cost1 == cost2 && d1.get_weight() < d2.get_weight()) || (d1.get_weight() == d2.get_weight() && d1.get_volume() < d2.get_volume()) || (d1.get_volume() == d2.get_volume() && d1.get_duration() < d2.get_duration());
    });

    int n = entry.n;
    int reward = entry.reward;
    int weight = entry.weight;
    int volume = entry.volume;
    int duration = entry.duration;

    vector<vector<Delivery>::iterator> iterators;
    for (int i = 0; i < n; i++) {
        iterators.push_back(deliveries.begin() + i);
    }
    
    for (int i = 0; i < deliveries.size() - n; i++) {
        if (compareToEntry(driver, iterators, entry, cost_fun) >= 0) {
            break;
        }

        for (auto it : iterators) {
            it++;
        }
    }

    vector<Delivery> result;

    int comparison = compareToEntry(driver, iterators, entry, cost_fun);
    if (comparison < 0) {
        return result;
    } 
    
    if (comparison == 0) {
        for (auto it : iterators) {
            result.push_back(*it);
        }

        return result;
    }

    while (true) {
        
    }
}