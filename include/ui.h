#pragma once

#include "entities/delivery.h"
#include "entities/driver.h"
#include "interact.h"

#include <vector>
#include <string>

class UI {
    std::string drivers_file;
    std::string deliveries_file;

    bool scenario1 = false;
    bool scenario2 = false;
    bool scenario3 = false;

    // TODO: Implement features late
    bool transfer = false;
    bool efficacy = false;

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

    /**
     * @brief Gets any extras the user might choose
     * 
     * @return Menu 
     */
    Menu get_extras_menu();


    void show_selection();

    public:
        /**
         * @brief Displays the menu
         */
        void start();
};