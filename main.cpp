#include <iostream>
#include "constants.h"
#include "dataset.h"
#include "entities/delivery.h"

using namespace std;

int main() {
    File file(DELIVERIES_FILE_PATH);

    for (FileEntry entry : file.get_entries()) {
        Delivery delivery = Delivery::from_entry(entry);
            cout << delivery.get_volume() << ' ' << delivery.get_weight() << ' ' << delivery.get_reward() << ' ' << delivery.get_duration() << endl;
    }


    return 0;
}
