#include "RepairCenter.h"
#include <iostream>

int main() {
    try {
        // Construct System class object with default data directory "Data"
        RepairCenter system("Data");

        // Start system main menu event loop
        system.run();
    } catch (const std::exception& e) {
        std::cerr << "\n[FATAL ERROR] An unhandled exception occurred: " << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "\n[FATAL ERROR] An unknown critical error occurred.\n";
        return 1;
    }
    return 0;
}
