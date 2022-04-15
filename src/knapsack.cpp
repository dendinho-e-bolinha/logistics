#include "sparse_boobacube.h"
#include "entities/delivery.h"

#include <vector>

using namespace std;

// Input:
// Values (stored in array v)
// Weights (stored in array w)
// Number of distinct items (n)
// Knapsack capacity (W)
// NOTE: The array "v" and array "w" are assumed to store all relevant values starting at index 1.

// Define value[n, W]

// Initialize all value[i, j] = -1

// Define m:=(i,j)         // Define function m so that it represents the maximum value we can get under the condition: use first i items, total weight limit is j
// {
//     if i == 0 or j <= 0 then:
//         value[i, j] = 0
//         return

//     if (value[i-1, j] == -1) then:     // m[i-1, j] has not been calculated, we have to call function m
//         value[i-1, j] = m(i-1, j)

//     if w[i] > j then:                      // item cannot fit in the bag
//         value[i, j] = value[i-1, j]
//     else: 
//         if (value[i-1, j-w[i]] == -1) then:     // m[i-1,j-w[i]] has not been calculated, we have to call function m
//             value[i-1, j-w[i]] = m(i-1, j-w[i])
//         value[i, j] = max(value[i-1,j], value[i-1, j-w[i]] + v[i])
// }

// Run m(n, W)

void knapsack(SparseBoobacube &boobacube, const vector<Delivery> &deliveries, int n, int wl, int vl, int tl) {
    if (n == 0 || wl <= 0 || vl <= 0 || tl <= 0) {
        boobacube.insert({ n, wl, vl, tl }, 0);
        return;
    }

    if (boobacube.at({ n - 1, wl, vl, tl }) == -1) {
        knapsack(boobacube, deliveries, n - 1, wl, vl, tl);
    }

    const Delivery &item = deliveries.at(n - 1); 
    bool cannotFit = item.get_weight() > wl || item.get_volume() > vl || item.get_duration() > tl;  

    if (cannotFit) {
        boobacube.insert({ n, wl, vl, tl }, boobacube.at({ n - 1, wl, vl, tl }));
    } else {
        if (boobacube.at({ n - 1, wl - item.get_weight(), vl - item.get_volume(), tl - item.get_duration() }) == -1) {
            knapsack(boobacube, deliveries,  n - 1, wl - item.get_weight(), vl - item.get_volume(), tl - item.get_duration());
        }

        boobacube.insert(
            { n, wl, vl, tl }, 
            max(
                boobacube.at({ n - 1, wl, vl, tl }),
                boobacube.at({ n - 1, wl - item.get_weight(), vl - item.get_volume(), tl - item.get_duration() }) + item.get_reward()
            )
        );
    }
}