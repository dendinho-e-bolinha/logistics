#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <limits.h>

#include "entities/delivery.h"
#include "entities/driver.h"

#define maxN 31
#define maxW 31
#define INF INT_MAX

using namespace std;

/**
 * @brief Returns the maximum value that can fit the backpack
 */
vector<vector<int>> knapsack(int capacity, vector<int> weights, vector<int> values) {
    if (values.size() != weights.size())
        return {};
    
    int n = weights.size();

    // Creating Lookup table
    // Each column represents a weight
    // Each row represents a Item
    // The inner table is filled with the value gained
    vector<vector<int>> lookup_table(
        n,
        vector<int>(capacity, 0)
    );

    // Loop variables
    int i, w;

    // Building the table (bottom-up approach)
    for (i = 0; i <= n; ++i) {
        for (w = 0; w <= capacity; ++w) {
            if (i == 0 || w == 0)
                lookup_table.at(i).at(w) = 0;
            else if (weights.at(i - 1) <= w)
                lookup_table.at(i).at(w) = max(
                    values.at(i - 1) + lookup_table.at(i - 1).at(w - weights.at(i - 1)),
                    lookup_table.at(i - 1).at(w)
                );
            else
                lookup_table.at(i).at(w) = lookup_table.at(i - 1).at(w);
        }
    }

    // Result of knapsack
    int res = lookup_table.at(n).at(w);

    // Stores (value, weight) pairs will
    vector<vector<int>> chosen_pairs(2, vector<int>(2, 0));

    // Searching for the elements which where included
    for (; n > 0 && res > 0; --n) {
        if (res == lookup_table.at(n - 1).at(capacity))
            continue;
        else {
            chosen_pairs.push_back({weights.at(n - 1), values.at(i - 1)});

            res -= values.at(i - 1);
            capacity -= weights.at(i - 1);
        }
    }

    return chosen_pairs;
}


 
// 3D array to store
// states of DP
int dp[maxN][maxW][maxW];


void two_dim_knapsack(Driver &driver, vector<Delivery> &deliveries, int(Delivery, Driver) cost_fun) {
    int WL = driver.get_max_weight();
    int VL = driver.get_max_volume();

    vector<vector<vector<int>>> vec(
        deliveries.size(),
        vector<vector<int>>(
            WL + 1,
            vector<int>(VL + 1, INF)
        )
    );

    for (int w = 0; w <= WL; ++w) {
        for (int v = 0; v <= VL; ++v) {
            vec[0][w][v] = INF;
        }
    }

    vec[0][0][0] = 0;

    for (int i = 1; i <= deliveries.size(); ++i) {
        int wi = deliveries.at(i).get_weight();
        int vi = deliveries.at(i).get_volume();
        int ci = cost_fun(deliveries.at(i - 1), driver);
        
        for (int w = 0; w <= WL; ++w) {
            for (int v = 0; v <= VL; ++v) {
                vec[i][w][v] = min(vec[i - 1][w][v], vec[i - 1][w - wi][v - vi] + ci);
            }
        }
    }

    for (auto i : vec)
        for (auto j : i)
            for (auto k : j)
                cout << i << " " << j << " " << k << endl;
}
// ks1_cap represents remaining capacity of 1st knapsack
// ks2_cap represents remaining capacity of 2nd knapsack
// i represents index of the array arr we are working on
int maxWeight(vector<int> &arr, int n, int ks1_cap, int ks2_cap, int i)
{
    // Base case
    if (i == n)
        return 0;
    if (dp[i][ks1_cap][ks2_cap] != -1)
        return dp[i][ks1_cap][ks2_cap];
 
    // Variables to store the result of three
    // parts of recurrence relation
    int fill_ks1 = 0, fill_ks2 = 0, fill_none = 0;
 
    if (ks1_cap >= arr[i])
        fill_ks1 = arr[i] +
         maxWeight(arr, n, ks1_cap - arr[i], ks2_cap, i + 1);
 
    if (ks2_cap >= arr[i])
        fill_ks2 = arr[i] +
         maxWeight(arr, n, ks1_cap, ks2_cap - arr[i], i + 1);
 
    fill_none = maxWeight(arr, n, ks1_cap, ks2_cap, i + 1);
 
    // Store the state in the 3D array
    dp[i][ks1_cap][ks2_cap] = max(fill_none, max(fill_ks1, fill_ks2));
 
    return dp[i][ks1_cap][ks2_cap];
}


void solve(vector<Driver> &drivers, vector<Delivery> &deliveries) {

}