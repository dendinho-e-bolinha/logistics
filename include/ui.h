#pragma once

#include "entities/delivery.h"
#include "entities/driver.h"
#include "interact.h"

#include <vector>
#include <string>

class UI {
    bool scenario1 = false;
    bool scenario2 = false;
    bool scenario3 = false;

    bool verbose;

    std::vector<Delivery> deliveries;
    std::vector<Driver> drivers;

    /**
     * @brief Lets the user pick the file where to get the data from
     * 
     * @return true if the file exists, false otherwise
     */
    std::string choose_file_menu(std::string);

    /**
     * @brief Gets the scenario the user chose
     * 
     * @return Menu 
     */
    Menu get_scenario_menu();

    void show_selection(const std::vector<Driver> &currentDrivers, const std::vector<Delivery> &currentDeliveries) const;

    public:
        /**
         * @brief Displays the menu
         */
        void start();

        UI(bool verbose = false);
};