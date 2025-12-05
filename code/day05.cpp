#include <iostream>
#include <fstream>
#include <set>     // for std::set
#include <cstdint> // for fixed width integers
#include <chrono>  // for std::chrono::high_resolution_clock()
#include <string>  // for std::getline
#include <vector>
#include <array>
#include <sstream>

class Answer
{
public:
    uint64_t part1{0};
    uint64_t part2{0};
};

// Check if ingredient is in this range.
bool isInRange(uint64_t ingredient, std::pair<uint64_t, uint64_t> freshRange)
{
    return (
        (ingredient >= std::get<0>(freshRange))
        && (ingredient <= std::get<1>(freshRange))
    );
}

// Check if ingredient is in any of the ranges.
bool isFresh(uint64_t ingredient, std::vector<std::pair<uint64_t, uint64_t>> freshRanges)
{
    for (std::pair<uint64_t, uint64_t> freshRange : freshRanges)
    {
        if (isInRange(ingredient, freshRange))
            return true;
    }
    return false;
}

// Calculate if ranges intersect
bool rangesIntersect(std::pair<uint64_t, uint64_t> range1, std::pair<uint64_t, uint64_t> range2)
{
    return (
        isInRange(std::get<0>(range1), range2)
        || isInRange(std::get<1>(range1), range2)
        || isInRange(std::get<0>(range2), range1)
    );
}

// Merge ranges, assuming they intersect.
std::pair<uint64_t, uint64_t> mergeRanges(std::pair<uint64_t, uint64_t> range1, std::pair<uint64_t, uint64_t> range2)
{
    return std::make_pair(
        std::min(range1.first, range2.first),
        std::max(range1.second, range2.second)
    );
}

// Print the ranges
void printRange(std::pair<uint64_t, uint64_t> range)
{
    std::cout << range.first << " " << range.second << "\n";
}

// Print the ranges
void printRanges(std::set<std::pair<uint64_t, uint64_t>> &ranges)
{
    for (std::pair<uint64_t, uint64_t> range : ranges)
    {
        printRange(range);
    }
}

// Build a set of ranges which is equivalent to the set of ranges before,
// but with no overlaps.
std::set<std::pair<uint64_t, uint64_t>> optimizeRanges(std::vector<std::pair<uint64_t, uint64_t>> &freshRanges, std::set<std::pair<uint64_t, uint64_t>> &optimizedRanges)
{
    // If `freshRanges` is empty then we're done.
    if (freshRanges.empty())
        return optimizedRanges;
    // Select a range
    std::pair<uint64_t, uint64_t> range1{freshRanges.back()};
    freshRanges.pop_back();
    bool found{false};
    // Find a range that intersects with this one.
    for (std::pair<uint64_t, uint64_t> range2 : optimizedRanges)
    {
        if (rangesIntersect(range1, range2))
        {
            freshRanges.push_back(mergeRanges(range1, range2));
            optimizedRanges.erase(range2);
            found = true;
            break;
        }
    }
    if (!found)
        {
            // std::cout << "New range added to set: ";
            // printRange(range1);
            optimizedRanges.insert(range1);
        }
    return optimizeRanges(freshRanges, optimizedRanges);
}

Answer findAnswer(std::vector<uint64_t> ingredients, std::vector<std::pair<uint64_t, uint64_t>> freshRanges)
{
    Answer answer{};
    for (uint64_t ingredient : ingredients)
    {
        if (isFresh(ingredient, freshRanges))
            answer.part1++;
    }

    std::set<std::pair<uint64_t, uint64_t>> optimizedRanges{};
    optimizedRanges = optimizeRanges(freshRanges, optimizedRanges);
    for (std::pair<uint64_t, uint64_t> range : optimizedRanges)
    {
        answer.part2 += range.second - range.first + 1;
    }
    return answer;
}

int main()
{
    // Read input file
    std::ifstream inf{"inputs/day05.txt"};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, the file could not be opened for reading!\n";
        return 1;
    }

    auto start{std::chrono::high_resolution_clock::now()};

    // Parse the input
    std::vector<std::pair<uint64_t, uint64_t>> freshRanges{};
    std::vector<uint64_t> ingredients{};
    std::string strInput{};
    uint64_t first{};
    uint64_t last{};
    char c{};
    while (std::getline(inf,strInput))
    {
        if (strInput == "")
            break;
        std::istringstream iss{strInput};
        iss >> first;
        iss.get();
        iss >> last;
        freshRanges.push_back(std::make_pair(first, last));
        // std::cout << first << " " << last << "\n";
    }
    while (std::getline(inf, strInput))
    {
        std::istringstream iss{strInput};
        iss >> first;
        ingredients.push_back(first);
        // std::cout << first << "\n";
    }

    Answer answer{findAnswer(ingredients, freshRanges)};

    auto stop{std::chrono::high_resolution_clock::now()};
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Part 1: " << answer.part1 << "\n";
    std::cout << "Part 2: " << answer.part2 << "\n";
    std::cout << "Time: " << duration.count() << " microseconds\n";

    return 0;
}
