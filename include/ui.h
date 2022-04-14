#pragma once

#include "entities/delivery.h"
#include "entities/driver.h"

#include <vector>
#include <string>

class UI {
    std::string file;
    bool scenario1 = false;
    bool sceanrio2 = false;
    bool scenario3 = false;
    bool transfer = false;
    bool efficacy = false;

    /**
     * @brief Lets the user pick the file where to get the data from
     * 
     * @return string containing the user's choice
     */
    string choose_file_menu();

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

    public:
        /**
         * @brief Displays the menu
         */
        void start();
};