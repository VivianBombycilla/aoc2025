#include <iostream>
#include <fstream>
#include <set>     // for std::set
#include <cstdint> // for fixed width integers
#include <chrono>  // for std::chrono::high_resolution_clock()

// Integer exponentiation because why doesnt C++ have that???
uint64_t pow(uint64_t base, int exp)
{
    int output = 1;
    for (int i = 0; i < exp; i++)
    {
        output *= base;
    }
    return output;
}

// Finds how many digits `n` is in base `base`
int numDigits(uint64_t n, int base)
{
    int c{0};
    while (n > 0)
    {
        n /= base;
        c++;
    }
    return c;
}

// Check if this integer is prime
bool isPrime(uint64_t n)
{
    if (n < 2) return false;
    for (int i{2}; i * i <= n; i++)
    {
        if (n % i == 0) return false;
    }
    return true;
}


// Outputs the number `num`, if written `times` times. 
uint64_t repeatNum(uint64_t num, int times)
{
    uint64_t output{num};
    int numLength = numDigits(num, 10);
    for (int i = 0; i < times - 1; i++)
    {
        for (int j = 0; j < numLength; j++)
        {
            output *= 10;
        }
        output += num;
    }
    return output;
}

// Finds the first invalid id which is either <= (if prev=True)
// or >= (if prev=False) to the given id.
//
// This is outputted in unrepeated form.
uint64_t findAdjacentInvalidID(uint64_t id, bool prev, int times)
{
    int idLength = numDigits(id, 10);
    if (idLength % times == 0) {
        // Get the first part of the 
        uint64_t firstHalf{id / pow(10, idLength - (idLength / times))};
        uint64_t firstHalfID{repeatNum(firstHalf, times)};
        // This is a good first guess at the result.
        uint64_t output{firstHalf};
        if (prev && (firstHalfID != id))
            output--;
        if (firstHalfID < id)
            output++;
        return output;
    } else
    {
        uint64_t output{pow(10, idLength / times)};
        if (prev)
            output--;
        return output;
    }
}

// Find invalid IDs between minID and maxID.
std::set<uint64_t> findInvalidIDs(uint64_t minID, uint64_t maxID, int times)
{
    uint64_t minInvalidID{findAdjacentInvalidID(minID, false, times)};
    uint64_t maxInvalidID{findAdjacentInvalidID(maxID, true, times)};
    // std::cout << minInvalidID << " " << maxInvalidID << "\n";
    std::set<uint64_t> output{};
    for (int i = minInvalidID; i <= maxInvalidID; i++)
    {
        uint64_t invalidID{repeatNum(i, times)};
        // std::cout << "invalid id: " << invalidID << "\n";
        output.insert(invalidID);
    }
    // std::cout << output << "\n";
    return output;
}

// Sum a set
uint64_t sumSet(std::set<uint64_t> set)
{
    uint64_t sum{0};
    for (uint64_t item : set)
    {
        sum += item;
    }
    return sum;
}

// Class to store the state of the problem
class ProblemState
{
public:
    uint64_t part1{0};
    uint64_t part2{0};
};

// Updates the state of the problem given another input
void updateState(ProblemState& state, uint64_t first, uint64_t last)
{
    std::set<uint64_t> invalidIDs{findInvalidIDs(first,last,2)};
    state.part1 += sumSet(invalidIDs);
    for (int i{3}; i <= numDigits(last, 10); i++)
    {
        if (isPrime(i))
        {
            invalidIDs.merge(findInvalidIDs(first, last, i));
        }
    }
    state.part2 += sumSet(invalidIDs);
}


int main()
{
    // Read input file
    std::ifstream inf{"inputs/day02.txt"};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, the file could not be opened for reading!\n";
        return 1;
    }

    auto start{std::chrono::high_resolution_clock::now()};

    ProblemState state{};
    uint64_t first{};
    uint64_t last{};
    char c{};
    while (inf)
    {
        inf >> first;
        inf.get();
        inf >> last;
        c = inf.get();

        updateState(state, first, last);
        if (c == '\n')
            break;
    }
    
    std::cout << "Part 1: " << state.part1 << "\n";
    std::cout << "Part 2: " << state.part2 << "\n";

    auto stop{std::chrono::high_resolution_clock::now()};
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time: " << duration.count() << " microseconds\n" ;
}
