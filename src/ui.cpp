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

using namespace std;

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
    for (int i = 0; i < this->drivers.size(); i++) {
        Driver &driver = this->drivers.at(i);
        cout << "\nNumber: " << i << "\nSelected: " << boolalpha << driver.is_selected << "\n"; 
        if (driver.is_selected) {
            cout << "Volume: " << driver.current_volume << " / " << driver.get_max_volume() << '\n'
                << "Weight: " << driver.current_weight << " / " << driver.get_max_weight() << '\n'
                << "Duration: " << driver.minutes_used << " / " << (24 * 60) << '\n';
        } else break;
    }

    for (int i = 0; i < this->deliveries.size(); i++) {
        Delivery &delivery = this->deliveries.at(i);
        cout << "\nNumber: " << i << "\nSelected: " << boolalpha << (delivery.selected_driver != -1) << '\n'; 
        if (delivery.selected_driver != -1) {
            cout << "Driver: " << delivery.selected_driver << '\n';
        }
    }
}

Menu UI::get_scenario_menu() {
    Menu scenario("Escolha um dos seguintes cenários:");

    MenuBlock scenario_options;
    
    scenario_options.add_option("[Cenário 1] Minimizar o número de estafetas utilizado, entregando o maior número de pedidos", [this]() {
        this->scenario1 = true;
    });

    scenario_options.add_option("[Cenário 2] Maximizar o lucro da empresa", [this]() {
        this->scenario2 = true;
    });

    scenario_options.add_option("[Cenário 3] Maximizar o número de entregas expresso em 8 horas de trabalho", [this]() {
        this->scenario3 = true;
    });

    scenario.add_block(scenario_options);
    return scenario;
}

Menu UI::get_extras_menu() { // should be able to select more than one? update docs accordingly
    Menu extras("Escolha 0 ou mais extras:");

    MenuBlock extra_options;

    extra_options.add_option("Transferir pedidos não entregues num dia para o dia seguinte", [this]() {
        this->transfer = true;

        if (this->scenario1)
            scenario1::solve(this->drivers, this->deliveries); 
        //else if (this->scenario2)
            //scenario2::solve(this->drivers, this->deliveries); 
        else if (this->scenario3)
            scenario3::solve(this->deliveries);

        this->show_selection();
    });

    extra_options.add_option("Medir eficiência da operação (número de pedidos entregues / número de pedidos enviados)", [this]() {
        this->efficacy = true;

        if (this->scenario1)
            scenario1::solve(this->drivers, this->deliveries); 
        //else if (this->scenario2)
            //scenario2::solve(this->drivers, this->deliveries); 
        else if (this->scenario3)
            scenario3::solve(this->deliveries);

        this->show_selection();
    });

    extra_options.add_option("None", [this](){
        if (this->scenario1)
            scenario1::solve(this->drivers, this->deliveries); 
        //else if (this->scenario2)
            //scenario2::solve(this->drivers, this->deliveries); 
        else if (this->scenario3)
            scenario3::solve(this->deliveries);

        this->show_selection();
    });

    extras.add_block(extra_options);
    return extras;
}
