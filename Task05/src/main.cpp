#include <iostream>
#include "LocationSearcher.h"

/**
 * The main entry point of the LocationSearcher program.
 * Creates an instance of the LocationSearcher class and runs the location search process.
 *
 * @return The exit status of the program.
 */
int main() 
{
    try
    {
        LocationSearcher locationSearcher;
        locationSearcher.run();
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}
