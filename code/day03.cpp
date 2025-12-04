#include <iostream>
#include <fstream>
#include <set>     // for std::set
#include <cstdint> // for fixed width integers
#include <chrono>  // for std::chrono::high_resolution_clock()
#include <string>  // for std::getline

int findLargeJoltage(std::string batteryBank)
{
    size_t bankLength{batteryBank.length()};
    char firstBattery{batteryBank[0]};
    char secondBattery{batteryBank[1]};
    int currIndex{1};
    while (currIndex < bankLength)
    {
        char currBattery{batteryBank[currIndex]};
        if ((currBattery > firstBattery) && (currIndex < bankLength - 1))
        {
            firstBattery = currBattery;
            secondBattery = batteryBank[currIndex + 1];
        } else if (currBattery > secondBattery)
        {
            secondBattery = currBattery;
        }
        currIndex ++;
    }

    return (firstBattery - '0') * 10 + (secondBattery - '0');
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

    std::string strInput{};
    int part1{};
    while (std::getline(inf, strInput))
    {
        // std::cout << strInput[0] << "\n";
        part1 += findLargeJoltage(strInput);
    }
    std::cout << part1 << "\n";
    return 0;
}
