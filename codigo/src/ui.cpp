#include "ui.h"
#include "constants.h"
#include "scenarios/driver_optimization.h"
#include "scenarios/reward_optimization.h"
#include "scenarios/start_optimization.h"
#include "dataset.h"

#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <set>
#include <fstream>
#include <iomanip>

using namespace std;


UI::UI(bool verbose) : verbose(verbose) {}

void UI::start() {
    string drivers_file = choose_file_menu("drivers");
    string deliveries_file = choose_file_menu("deliveries");

    File file1(drivers_file);
    this->drivers = file1.read_drivers();

    File file2(deliveries_file);
    this->deliveries = file2.read_deliveries();

    Menu scenario_choice = get_scenario_menu();

    bool is_running = true;
    while (is_running) {

        MenuBlock special_block;    
        special_block.add_option("Exit", [&is_running]() { is_running = false; });
        
        scenario_choice.set_special_block(special_block);
        scenario_choice.show();

        if (!is_running)
            break;

        wait_for_input();
    }
}

string UI::choose_file_menu(string type) {
    string user_choice = read_value<string>("Please choose the file to read " + type + " data from: ", "Invalid filename", [&](const string filename) {
        string fileExtension = filename.substr(filename.find_last_of(".") + 1);
        if (fileExtension != "txt") {
            throw validation_error("Unsupported extension (valid options: txt)");
        }

        ifstream infile(DATASET_PATH + filename);
        if (!infile.is_open()) {
            throw validation_error("File not found (" + (DATASET_PATH + filename) + ")");
        }

        return true;
    });

    return DATASET_PATH + user_choice;
}

void UI::show_selection(const vector<Driver> &currentDrivers, const vector<Delivery> &currentDeliveries) const {
    const string sep = "    ";

    cout << endl;

    if (verbose) {
        if (scenario1 || scenario2) {
            for (int i = 0; i < currentDrivers.size(); i++) {
                const Driver &driver = currentDrivers.at(i);

                cout << "Number: " << i << endl;
                
                if (scenario2) {
                    cout << "Cost: " << driver.get_daily_cost() << endl;
                }

                cout << "Selected: " << boolalpha << driver.is_selected << endl;

                if (driver.is_selected) {
                    cout << "Volume: " << driver.current_volume << " / " << driver.get_max_volume() << endl
                         << "Weight: " << driver.current_weight << " / " << driver.get_max_weight() << endl
                         << "Time taken: " << driver.used_seconds << " / " << WORK_TIME << endl
                         << endl;
                    
                    if (scenario1) {
                        cout << setfill('=') << setw(17) << right << ' ' << "Deliveries" << setfill('=') << setw(17) << left << ' ' << endl
                             << setfill(' ') << setw(12) << left << "Volume" << sep << setfill(' ') << setw(12) << left << "Weight" << sep << setfill(' ') << setw(12) << left << "Duration" << endl
                             << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "--------" << endl;
                    } else {
                        cout << setfill('=') << setw(25) << right << ' ' << "Deliveries" << setfill('=') << setw(25) << left << ' ' << endl
                             << setfill(' ') << setw(12) << left << "Volume" << sep << setfill(' ') << setw(12) << left << "Weight" << sep << setfill(' ') << setw(12) << left << "Duration" << sep << setfill(' ') << setw(12) << left << "Reward" << endl
                             << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "--------" << sep << setfill('-') << setw(12) << left << "------" << endl;
                    }

                    for (int j = 0; j < currentDeliveries.size(); j++) {
                        const Delivery &delivery = currentDeliveries.at(j);
                        
                        if (delivery.selected_driver == i) {
                            float volume = delivery.get_volume();
                            float weight = delivery.get_weight();
                            float duration = delivery.get_seconds();

                            cout << setfill(' ') << setw(12) << left << volume << sep
                                << setfill(' ') << setw(12) << left << weight << sep
                                << setfill(' ') << setw(12) << left << duration;

                            if (scenario2) {
                                float reward = delivery.get_normal_reward();
                                cout << sep << setfill(' ') << setw(12) << left << reward;
                            }
                            
                            cout << endl;
                        }
                    }
                }

                cout << endl
                     << endl;
            }

            if (scenario1) {
                cout << setfill('=') << setw(11) << right << ' ' << "Unfulfilled Deliveries" << setfill('=') << setw(11) << left << ' ' << endl
                     << setfill(' ') << setw(12) << left << "Volume" << sep << setfill(' ') << setw(12) << left << "Weight" << sep << setfill(' ') << setw(12) << left << "Duration" << endl
                     << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "--------" << endl;
            } else {
                cout << setfill('=') << setw(19) << right << ' ' << "Unfulfilled Deliveries" << setfill('=') << setw(19) << left << ' ' << endl
                     << setfill(' ') << setw(12) << left << "Volume" << sep << setfill(' ') << setw(12) << left << "Weight" << sep << setfill(' ') << setw(12) << left << "Duration" << sep << setfill(' ') << setw(12) << left << "Reward" << endl
                     << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "--------" << sep << setfill('-') << setw(12) << left << "------" << endl;
            }

            for (int j = 0; j < currentDeliveries.size(); j++) {
                const Delivery &delivery = currentDeliveries.at(j);
                
                if (delivery.selected_driver == -1) {
                    float volume = delivery.get_volume();
                    float weight = delivery.get_weight();
                    float duration = delivery.get_seconds();

                    cout << setfill(' ') << setw(12) << left << volume << sep
                        << setfill(' ') << setw(12) << left << weight << sep
                        << setfill(' ') << setw(12) << left << duration;

                    if (scenario2) {
                        float reward = delivery.get_normal_reward();
                        cout << sep << setfill(' ') << setw(12) << left << reward;
                    }
                    
                    cout << endl;
                }
            }

        } else if (scenario3) {

            cout << setfill('=') << setw(20) << right << ' ' << "Fulfilled Deliveries" << setfill('=') << setw(20) << left << ' ' << endl
                 << setfill(' ') << setw(12) << left << "Volume" << sep << setfill(' ') << setw(12) << left << "Weight" << sep << setfill(' ') << setw(12) << left << "Start (s)" << sep << setfill(' ') << setw(12) << left << "End (s)" << endl
                 << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "---------" << sep << setfill('-') << setw(12) << left << "-------" << endl;

            for (int j = 0; j < currentDeliveries.size(); j++) {
                const Delivery &delivery = currentDeliveries.at(j);
                
                if (delivery.starting_time + delivery.get_normal_reward() <= WORK_TIME) {
                    float volume = delivery.get_volume();
                    float weight = delivery.get_weight();
                    float start = delivery.starting_time;
                    float end = start + delivery.get_seconds();

                    cout << setfill(' ') << setw(12) << left << volume << sep
                         << setfill(' ') << setw(12) << left << weight << sep
                         << setfill(' ') << setw(12) << left << start << sep
                         << setfill(' ') << setw(12) << left << end << endl;
                }
            }

            cout << endl
                 << endl
                 << setfill('=') << setw(19) << right << ' ' << "Fulfilled Deliveries" << setfill('=') << setw(19) << left << ' ' << endl
                 << setfill(' ') << setw(12) << left << "Volume" << sep << setfill(' ') << setw(12) << left << "Weight" << sep << setfill(' ') << setw(12) << left << "Start (s)" << sep << setfill(' ') << setw(12) << left << "End (s)" << endl
                 << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "------" << sep << setfill('-') << setw(12) << left << "---------" << sep << setfill('-') << setw(12) << left << "-------" << endl;

            for (int j = 0; j < currentDeliveries.size(); j++) {
                const Delivery &delivery = currentDeliveries.at(j);
                
                float start = delivery.starting_time;
                float end = start + delivery.get_seconds();
                if (end > WORK_TIME) {
                    float volume = delivery.get_volume();
                    float weight = delivery.get_weight();

                    cout << setfill(' ') << setw(12) << left << volume << sep
                         << setfill(' ') << setw(12) << left << weight << sep
                         << setfill(' ') << setw(12) << left << start << sep
                         << setfill(' ') << setw(12) << left << end << endl;
                }
            }
        }

        cout << endl
             << endl;
    }
    
    int total_drivers = drivers.size();
    int selected_drivers = count_if(currentDrivers.begin(), currentDrivers.end(), [](const Driver &driver){
        return driver.is_selected;
    });
    int unselected_drivers = total_drivers - selected_drivers;


    int total_deliveries = currentDeliveries.size();
    int fulfilled_deliveries = count_if(currentDeliveries.begin(), currentDeliveries.end(), [&](const Delivery &delivery){
        if (scenario1 || scenario2) {
            return delivery.selected_driver != -1;
        } else if (scenario3) {
            return delivery.starting_time + delivery.get_seconds() <= WORK_TIME;
        }

        return true;
    });
    int unfulfilled_deliveries = total_deliveries - fulfilled_deliveries;


    cout << setfill('=') << setw(35) << right << ' ' << "Statistics" << setfill('=') << setw(35) << left << ' ' << endl
         << endl;

    cout << setfill(' ') << setw(24) << left << "Fulfilled Deliveries" << sep << setfill(' ') << setw(24) << left << "Unfulfilled Deliveries" << sep << setfill(' ') << setw(24) << left << "Total Deliveries" << endl
         << setfill('-') << setw(24) << left << "--------------------" << sep << setfill('-') << setw(24) << left << "----------------------" << sep << setfill('-') << setw(24) << left << "----------------" << endl
         << setfill(' ') << setw(24) << left << fulfilled_deliveries   << sep << setfill(' ') << setw(24) << left << unfulfilled_deliveries   << sep << setfill(' ') << setw(24) << left << total_deliveries   << endl
         << endl;

    if (scenario1 || scenario2) {
        cout << setfill(' ') << setw(24) << left << "Selected Drivers" << sep << setfill(' ') << setw(24) << left << "Unselected Drivers" << sep << setfill(' ') << setw(24) << left << "Total Drivers" << endl
             << setfill('-') << setw(24) << left << "----------------" << sep << setfill('-') << setw(24) << left << "------------------" << sep << setfill('-') << setw(24) << left << "-------------" << endl
             << setfill(' ') << setw(24) << left << selected_drivers   << sep << setfill(' ') << setw(24) << left << unselected_drivers   << sep << setfill(' ') << setw(24) << left << total_drivers   << endl
             << endl;
    }
    
    

    if (scenario2) {
        int money_won = 0, money_spent = 0;
        for (const Driver &driver : currentDrivers) {
            if (driver.is_selected) {
                money_spent += driver.get_daily_cost();
            }
        }

        for (const Delivery &delivery : currentDeliveries) {
            if (delivery.selected_driver != -1) {
                money_won += delivery.get_normal_reward();
            }
        }

        cout << "Money gained: " << money_won << "€" << endl 
             << "Money spent: " << money_spent << "€" << endl
             << "Total profit: " << money_won - money_spent << "€" << endl;
    
    } else if (scenario3) {
        int sum_ending_time = 0;
        for (const Delivery &delivery : deliveries) {
            int end = delivery.starting_time + delivery.get_seconds();
            if (end <= WORK_TIME) {
                sum_ending_time += end;
            }
        }

        float average_ending_time = ((float) sum_ending_time) / fulfilled_deliveries;
        cout << "Average ending time: " << fixed << setprecision(2) << average_ending_time << "s" << endl;
    }

    float operating_efficiency = 100.0 * fulfilled_deliveries / total_deliveries;
    cout << "Efficiency: " << fixed << setprecision(2) << operating_efficiency << '%' << endl
         << endl;
}

Menu UI::get_scenario_menu() {
    this->scenario1 = false;
    this->scenario2 = false;
    this->scenario3 = false;

    Menu scenario("Choose one of the following scenarios:");

    MenuBlock scenario_options;
    scenario_options.add_option("[Scenario 1] Deliver the largest number of orders while minimizing the number of drivers used", [this]() {
        this->scenario1 = true;
        this->scenario2 = false;
        this->scenario3 = false;

        DriverOptimization opt(this->drivers, this->deliveries);
        opt.solve();

        this->show_selection(opt.getDrivers(), opt.getDeliveries());
    });

    scenario_options.add_option("[Scenario 2] Maximize the profit", [this]() {
        this->scenario1 = false;
        this->scenario2 = true;
        this->scenario3 = false;

        RewardOptimization opt(this->drivers, this->deliveries);
        opt.solve();

        this->show_selection(opt.getDrivers(), opt.getDeliveries());
    });

    scenario_options.add_option("[Scenario 3] Maximize the number of express deliveries per day of work", [this]() {
        this->scenario1 = false;
        this->scenario2 = false;
        this->scenario3 = true;

        StartOptimization opt(this->deliveries);
        opt.solve();

        this->show_selection({}, opt.getDeliveries());
    });

    scenario.add_block(scenario_options);
    return scenario;
}
