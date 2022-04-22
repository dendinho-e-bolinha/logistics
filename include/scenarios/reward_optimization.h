#pragma once

#include <vector>

#include "sparse_hypercube.h"
#include "../entities/delivery.h"
#include "../entities/driver.h"

class RewardOptimization {

    /** @brief Vector containing all drivers */
    std::vector<Driver> drivers;

    /** @brief Vector containing all deliveries */
    std::vector<Delivery> deliveries;

    /** @brief Hypercube for storing knapsack data */
    SparseHypercube hypercube;

    /** @brief Number of deliveries processed by the knapsack algorithm */
    int frozenDeliveries;

    /** @brief Branch-and-bound implementation of the 0-1 knapsack algorithm with multiple constraints
     * 
     * @param n the number of deliveries
     * @param wl the weight limit of those deliveries
     * @param vl the volume limit of those deliveries
     * @param tl the time limit of those deliveries
     */
    void knapsack(int n, int wl, int vl, int tl);

    /** @brief Auxiliary function to call the knapsack algorithm for the first 20 deliveries on this driver 
     * 
     * @param driver a driver to assign deliveries to
    */
    void knapsack(const Driver &driver);

    /** @brief Get a vector of iterators pointing to the deliveries selected by the knapsack algorithm
     * 
     * @param n the number of deliveries to choose from
     * @param wl the weight limit of those deliveries
     * @param vl the volume limit of those deliveries
     * @param tl the time limit of those deliveries
     * @return vector of iterators pointing to the selected deliveries
     */
    std::vector<std::vector<Delivery>::iterator> getSelectedDeliveries(int n, int wl, int vl, int tl);

    /** @brief Auxiliary function to get the selected deliveries for this driver out of the first 20 
     * 
     * @param driver The driver that was used when running the knapsack algorithm
     * @return vector of iterators pointing to the selected deliveries
    */
    std::vector<std::vector<Delivery>::iterator> getSelectedDeliveries(const Driver &driver);

    /** @brief Select at most 20 random deliveries that are not frozen and put the at the beggining of the deliveries vector */
    void randomizeDeliveries();
    /**
     * @brief Freeze the delivery that the iterator points to.
     * 
     * @param it An iterator pointing to a delivery that will be frozen
     */
    void freezeDelivery(std::vector<Delivery>::iterator it);

    public:
        /**
         * @brief Construct a new Reward Optimization object
         * 
         * @param drivers the drivers in this scenario 
         * @param deliveries the deliveries in this scenario
         */
        RewardOptimization(const std::vector<Driver> &drivers, const std::vector<Delivery> &deliveries);

    /**
     * @brief Get the vector of drivers in this scenario. If this function is called after solve, the search properties inside each driver are valid.
     * 
     * @return a vector of drivers
     */
    const std::vector<Driver> &getDrivers() const;

    /**
     * @brief Get the vector of deliveries in this scenario. If this function is called after solve, the search properties inside each delivery are valid.
     * 
     * @return a vector of deliveries
     */
    const std::vector<Delivery> &getDeliveries() const;

    /**
     * @brief Solve the scenario
     * 
     */
    void solve();
};