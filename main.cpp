#include <iostream>
#include "constants.h"
#include "dataset.h"
#include "entities/delivery.h"

using namespace std;

int main() {
    File file(DELIVERIES_FILE_PATH);

    for (FileEntry entry : file.get_entries()) {
        Delivery delivery = Delivery::from_entry(entry);
            cout << delivery.getVolume() << ' ' << delivery.getWeight() << ' ' << delivery.getReward() << ' ' << delivery.getDuration() << endl;
    }


    return 0;
}
