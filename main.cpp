#include "constants.h"
#include "ui.h"


#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[]) {
    bool verbose = argc == 2 && string(argv[1]) == "-v";

    try {
        UI ui(verbose);
        ui.start();
    } catch (end_of_file_exception e) {
        return 0;
    } catch(exception e) {
        cout << "An error has occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
