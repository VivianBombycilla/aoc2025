#include <iostream>
#include <fstream>
#include <string> // for std::stoi

// Class storing the position of the dial 
// as well as counters for Part 1 and Part 2.
class DialState
{
public:
    int dialPosition{50};
    int part1{0};
    int part2{0};
};

// Return the raw new dial position, 
// given an inital dial position and an instruction.
int getRawNewDialPosition(DialState& dialState, std::string instruction)
{
    // Extract instruction information
    std::string direction{instruction.substr(0, 1)};
    // Convert rest of string to integer
    int amount{std::stoi(instruction.substr(1))};

    // Compute new dial position
    int rawNewDialPosition;
    if (direction == "R")
        rawNewDialPosition = dialState.dialPosition + amount;
    else
        rawNewDialPosition = dialState.dialPosition - amount;

    return rawNewDialPosition;
}

// Count number of times dial points at zero, 
// given the inital and final dial positions.
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

// Run the instruction on the dial,
// updating counters for Part 1 and Part 2.
void runInstruction(DialState& dialState, std::string instruction)
{
    // Find the raw new dial position
    int rawNewDialPosition{getRawNewDialPosition(dialState, instruction)};
    
    // The part 2 counter is computed using the old dial position,
    // so this comes before dialState.dialPosition is updated. 
    dialState.part2 += zeroPoints(dialState.dialPosition, rawNewDialPosition);

    // Update dialState.dialPosition
    dialState.dialPosition = ((rawNewDialPosition % 100) + 100) % 100;

    // Increment part 1 counter (if necessary)
    if (dialState.dialPosition == 0)
        dialState.part1++;
}

int main()
{
    // Read input file
    std::ifstream inf{"inputs/day01.txt"};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, the file could not be opened for reading!\n";
        return 1;
    }

    // Initialize variables
    DialState dialState{};

    // Read from input stream line by line
    std::string strInput{};
    while (std::getline(inf, strInput))
    {
        runInstruction(dialState, strInput);
    }

    // Output results
    std::cout << "Part 1: " << dialState.part1 << '\n';
    std::cout << "Part 2: " << dialState.part2 << '\n';

    return 0;

    // When inf goes out of scope, the ifstream
    // destructor will close the file
}
