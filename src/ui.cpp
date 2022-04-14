#include "ui.h"
#include "constants.h"
#include "scenario1.h"
#include "scenario2.h"
#include "scenario3.h"
#include "dataset.h"

#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <set>
#include <fstream>
#include <iomanip>

using namespace std;


UI::UI(string verbose_mode) {
    if (verbose_mode == "-v")
        this->verbose_mode = true;
}

UI::UI(){}

void UI::start() {
    this->drivers_file = choose_file_menu("drivers");
    this->deliveries_file = choose_file_menu("deliveries");
    // read from dataset here?

    File file1(drivers_file);
    this->drivers = file1.read_drivers();

    File file2(deliveries_file);
    this->deliveries = file2.read_deliveries();

    Menu scenario_choice = get_scenario_menu();
    Menu extras = get_extras_menu();

    Menu* menus[2] = { &scenario_choice, &extras };

    bool is_running = true;
    while (is_running) {
        bool is_reset = false;

        MenuBlock special_block;    
        special_block.add_option("Reset", [&is_reset]() { is_reset = true; });
        special_block.add_option("Exit", [&is_running]() { is_running = false; });

        for (int i = 0; i < sizeof(menus) / sizeof(Menu*); i++) {
            Menu &menu = **(menus + i);
            
            menu.set_special_block(special_block);
            menu.show();

            if (!is_running || is_reset)
                break;
        }

        cout << endl;
        wait_for_input();
    }
}

string UI::choose_file_menu(string choice) {
    string user_choice = read_value<string>("Please choose the file to read " + choice + " data from: ", "Invalid file (accepted file extensions: txt)", [&](const string user_choice) {
        bool valid_file_format = user_choice.substr(user_choice.find_last_of(".") + 1) == "txt";

        ifstream infile(DATASET_PATH + user_choice);

        return infile && valid_file_format;
    });

    return DATASET_PATH + user_choice;
}

void UI::show_selection() {

    int selected_drivers = count_if(currentDrivers.begin(), currentDrivers.end(), [](Driver &driver){
        return driver.is_selected == true;
    });

    int total_drivers = drivers.size();

    int delivered_orders = count_if(currentDeliveries.begin(), currentDeliveries.end(), [](Delivery &delivery){
        return delivery.selected_driver != -1;
    });

    int total_orders = currentDeliveries.size();

    int money_won = 0, money_spent = 0;

    for (int i = 0; i < this->currentDrivers.size(); ++i) {
        Driver &driver = this->currentDrivers.at(i);
        if (verbose_mode)
            cout << "\nNumber: " << i << "\nSelected: " << boolalpha << driver.is_selected << "\n"; 
        if (driver.is_selected) {
            money_spent += driver.get_daily_cost();

            if (verbose_mode)
                cout << "Volume: " << driver.current_volume << " / " << driver.get_max_volume() << '\n'
                    << "Weight: " << driver.current_weight << " / " << driver.get_max_weight() << '\n'
                    << "Duration: " << driver.minutes_used << " / " << (24 * 60) << '\n';

        }
    }

    for (int i = 0; i < this->currentDeliveries.size(); ++i) {
        Delivery &delivery = this->currentDeliveries.at(i);
        if (verbose_mode)
            cout << "\nNumber: " << i << "\nSelected: " << boolalpha << (delivery.selected_driver != -1) << '\n'; 
        if (delivery.selected_driver != -1) {
            money_won += delivery.get_reward();
            if (verbose_mode)
                cout << "Driver: " << delivery.selected_driver << "\n\n";
        }
    }

    cout << ((verbose_mode) ? "\x1B[2J\x1B[;H" : "\n\x1B[3J\x1B[2J\x1B[;H")
         << setfill('-') << setw(33) << "Statistics" << setw(33) << "-" << endl << endl;

    cout << setfill(' ') << setw(7) << "Delivered orders" << setw(25) << "Undelivered Orders" << setw(25) << "Total orders" << endl;

    cout << setw(7) << delivered_orders << setw(25) << total_orders - delivered_orders << setw(25) << total_orders
     << endl << endl;

    cout << setw(7) << "Selected drivers" << setw(25) << "Unselected drivers" << setw(25) << "Total drivers"
     << endl;

    cout << setw(7) << selected_drivers << setw(25) << total_drivers - selected_drivers << setw(25) << total_drivers
     << endl << endl;

    cout << "Money won: " << money_won << "€" << endl 
         << "Money spent: " << money_spent << "€" << endl
         << setw(7) << "Total profit: " << money_won - money_spent << "€" << endl;
}

Menu UI::get_scenario_menu() {
    Menu scenario("Escolha um dos seguintes cenários:");

    MenuBlock scenario_options;
    
    scenario_options.add_option("[Scenario 1] Minimize the number of drivers used by delivering the largest number of orders", [this]() {
        this->scenario1 = true;
    });

    scenario_options.add_option("[Scenario 2] Maximize the company profit", [this]() {
        this->scenario2 = true;
    });

    scenario_options.add_option("[Scenario 3] Maximize the number of express deliveries per day of work", [this]() {
        this->scenario3 = true;
    });

    scenario.add_block(scenario_options);
    return scenario;
}

Menu UI::get_extras_menu() { // should be able to select more than one? update docs accordingly
    Menu extras("Escolha 0 ou mais extras:");

    MenuBlock extra_options;

    extra_options.add_option("Transfer undelivered orders one day to the next day", [this]() {
        this->transfer = true;

        if (this->scenario1) {
            this->currentDrivers = this->drivers;
            this->currentDeliveries = this->deliveries;
            scenario1::solve(this->currentDrivers, this->currentDeliveries); 
        } //else if (this->scenario2) {
            //this->currentDeliveries = this->deliveries;
            //this->currentDrivers = this->drivers;
            //scenario2::solve(this->currentDrivers, this->currentDeliveries); 
        //} 
        else if (this->scenario3) {
            this->currentDeliveries = this->deliveries;
            scenario3::solve(this->currentDeliveries);
        }

        this->show_selection();
    });

    extra_options.add_option("Measure operation efficiency (number of orders delivered / number of orders shipped)", [this]() {
        this->efficacy = true;

        if (this->scenario1) {
            this->currentDrivers = this->drivers;
            this->currentDeliveries = this->deliveries;
            scenario1::solve(this->currentDrivers, this->currentDeliveries); 
        } //else if (this->scenario2) {
            //this->currentDeliveries = this->deliveries;
            //this->currentDrivers = this->drivers;
            //scenario2::solve(this->currentDrivers, this->currentDeliveries); 
        //} 
        else if (this->scenario3) {
            this->currentDeliveries = this->deliveries;
            scenario3::solve(this->currentDeliveries);
        }

        this->show_selection();
    });

    extra_options.add_option("None", [this](){

        if (this->scenario1) {
            this->currentDrivers = this->drivers;
            this->currentDeliveries = this->deliveries;
            scenario1::solve(this->currentDrivers, this->currentDeliveries); 
        } //else if (this->scenario2) {
            //this->currentDeliveries = this->deliveries;
            //this->currentDrivers = this->drivers;
            //scenario2::solve(this->currentDrivers, this->currentDeliveries); 
        //} 
        else if (this->scenario3) {
            this->currentDeliveries = this->deliveries;
            scenario3::solve(this->currentDeliveries);
        }

        this->show_selection();
    });

    extras.add_block(extra_options);
    return extras;
}
