#include <iostream>
#include <fstream>
#include <set>     // for std::set
#include <cstdint> // for fixed width integers
#include <chrono>  // for std::chrono::high_resolution_clock()
#include <string>  // for std::getline

int main()
{
    // Read input file
    std::ifstream inf{"inputs/day03.txt"};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, the file could not be opened for reading!\n";
        return 1;
    }

    std::string strInput{};
    while (std::getline(inf, strInput))
    {
        std::cout << strInput << "\n";
    }

    return 0;
}
