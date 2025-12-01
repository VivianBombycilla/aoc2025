#include <iostream>
#include <fstream>
#include <string> // for std::stoi

// Return the raw new dial position, given an inital dial position
// and an instruction.
int runInstruction(int dialPosition, std::string instruction)
{
    // Extract instruction information
    std::string direction{instruction.substr(0, 1)};
    // Convert rest of string to integer
    int amount{std::stoi(instruction.substr(1))};

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

// Count number of times dial points at zero, given the inital and final dial positions.
int zeroPoints(int dialPosition, int rawNewDialPosition)
{
    // This is a good first guess, only off by 1 in one easily catchable case.
    int zeroPoints{abs(rawNewDialPosition / 100)};

    // If final position is <= 0 and initial position is not 0, then we undercounted by 1.
    if (rawNewDialPosition <= 0 && dialPosition != 0)
    {
        zeroPoints++;
    }
    return zeroPoints;
}

int main()
{
    // Read input file
    std::ifstream inf{"day02.txt"};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, the file could not be opened for reading!\n";
        return 1;
    }

    // Initialize variables
    int dialPosition{50};
    int part1{0};
    int part2{0};
    int rawNewDialPosition;

    // Read from input stream line by line
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

    // Output results
    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';

    return 0;

    // When inf goes out of scope, the ifstream
    // destructor will close the file
}
