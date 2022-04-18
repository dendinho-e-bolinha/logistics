#include "constants.h"
#include "ui.h"


#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    
    try {

        UI ui = (argc == 2) ? UI(argv[1]) : UI();

        ui.start();
    } catch(exception e) {
        cout << "An error has occurred: " << e.what() << endl;
    }

    return 0;
}
