#include <iostream>
#include <fstream>
#include <set>     // for std::set
#include <cstdint> // for fixed width integers
#include <chrono>  // for std::chrono::high_resolution_clock()
#include <string>  // for std::getline

uint64_t findLargeJoltage(std::string batteryBank, int batteries)
{
    size_t bankLength{batteryBank.length()};
    int firstBatteryLoc{0}; // stores the first battery to start checking from
    uint64_t output{0};
    for (int i{0}; i < batteries; i++)
    {
        output *= 10;
        char bestNextBattery{'0'};
        // we start checking from the location after the previous battery
        // and end when there will not be enough space for the rest
        // of the batteries
        for (int j{firstBatteryLoc}; j <= bankLength - batteries + i; j++)
        {
            if (batteryBank[j] > bestNextBattery)
            {
                bestNextBattery = batteryBank[j];
                firstBatteryLoc = j + 1;
            }
        }
        output += (bestNextBattery - '0');
    }
    // std::cout << output << "\n";
    return output;
}

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

    auto start{std::chrono::high_resolution_clock::now()};

    std::string strInput{};
    uint64_t part1{};
    uint64_t part2{};
    while (std::getline(inf, strInput))
    {
        // std::cout << strInput[0] << "\n";
        part1 += findLargeJoltage(strInput, 2);
        part2 += findLargeJoltage(strInput, 12);
    }
    
    std::cout << "Part 1: " << part1 << "\n";
    std::cout << "Part 2: " << part2 << "\n";

    auto stop{std::chrono::high_resolution_clock::now()};
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time: " << duration.count() << " microseconds\n";
    
    return 0;
}
