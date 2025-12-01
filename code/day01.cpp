#include <iostream>
#include <fstream>
#include <string> // for std::stoi
#include <tuple>

int runInstruction(int dialPosition, std::string instruction)
{
    // Extract instruction information
    std::string direction{ instruction.substr(0,1) };
    int amount{ std::stoi(instruction.substr(1)) };

    // std::cout 
    //     << "Performing instruction " << instruction
    //     << " on dial position " << dialPosition
    //     << '\n';
    
    // Compute new dial position
    int rawNewDialPosition;
    if (direction == "R")
    {
        rawNewDialPosition = dialPosition + amount;
    }
    else
    {
        rawNewDialPosition = dialPosition - amount;
    }

    return rawNewDialPosition;
}

// Count number of times dial points at zero.
int zeroPoints(int dialPosition, int rawNewDialPosition)
{
    // Calculate times the dial pointed at zero
    std::div_t dialValues{std::div(rawNewDialPosition, 100)};
    int zeroPoints{abs(dialValues.quot)};
    if (rawNewDialPosition <= 0 && dialPosition != 0)
    {
        zeroPoints++;
    }
    return zeroPoints;
}

int main()
{
    // Initialize variables
    int dialPosition{ 50 };
    int part1{0};
    int part2{0};

    // Read input file
    std::ifstream inf{ "day01.txt" };

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
        return 1;
    }

    // While there's still stuff left to read
    int rawNewDialPosition;
    std::string strInput{};
    while (std::getline(inf, strInput))
    {
        rawNewDialPosition = runInstruction(dialPosition, strInput);
        part2 = part2 + zeroPoints(dialPosition, rawNewDialPosition);
        dialPosition = ((rawNewDialPosition % 100) + 100) % 100;
        if (dialPosition == 0)
        {
            part1++;
        }
    }
    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';

    return 0;

    // When inf goes out of scope, the ifstream
    // destructor will close the file
}
