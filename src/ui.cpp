#include "ui.h"

#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <set>

using namespace std;

void UI::start() {
    string file = choose_file_menu();
    // read from dataset here?

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

string UI::choose_file_menu() {
    string user_choice = read_value<string>("Please choose the file to read data from: ", "Please provide a valid file format", [](const string user_choice) { return user_choice; });
    this->file = user_choice;
    return user_choice;
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
    });

    extra_options.add_option("Medir eficiência da operação (número de pedidos entregues / número de pedidos enviados)", [this]() {
        this->efficacy = true;
    });
}
