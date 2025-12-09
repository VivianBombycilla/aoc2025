#include <iostream>
#include <fstream>
#include <set>     // for std::set
#include <cstdint> // for fixed width integers
#include <chrono>  // for std::chrono::high_resolution_clock()
#include <string>  // for std::getline
#include <vector>  // for std::vector
#include <array>   // for std::array
#include <sstream> // for std::istringstream
#include <cctype>  // for std::isdigit
#include <map>     // for std::map

// Returns indices of non-`'.'` characters.
std::set<int> findSplitters(std::string line)
{
    std::set<int> output{};
    for (int i{0}; i < line.length(); i++)
    {
        if (!(line[i] == '.'))
        {
            output.insert(i);
        }
    }
    return output;
}

// Maps everything in the set to 1.
std::map<int, uint64_t> createTimelineCount(std::set<int> &lasers)
{
    std::map<int, uint64_t> timelineCount{};
    for (int laser : lasers)
    {
        timelineCount[laser] = 1;
    }
    return timelineCount;
}

// Returns how many splits occur, and modifies the timeline count.
int doSplitting(std::set<int> &splitters, std::map<int, uint64_t> &timelineCount)
{
    std::map<int, uint64_t> newLasers;
    int count{0};
    for (std::pair<int, uint64_t> laserPair : timelineCount)
    {
        if (splitters.contains(laserPair.first))
        {
            newLasers[laserPair.first - 1] += laserPair.second;
            newLasers[laserPair.first + 1] += laserPair.second;
            count++;
        }
        else
        {
            newLasers[laserPair.first] += laserPair.second;
        }
    }
    timelineCount = newLasers;
    return count;
}

class Answer
{
public:
    uint64_t part1{0};
    uint64_t part2{0};
    Answer(std::set<int> &laserLocs, std::vector<std::set<int>> &splitterIndices)
    {
        std::map<int, uint64_t> timelineCount{createTimelineCount(laserLocs)};
        for (std::set<int> &splitterLine : splitterIndices)
        {
            part1 += doSplitting(splitterLine, timelineCount);
        }
        for (std::pair<int, uint64_t> laserPair : timelineCount)
        {
            part2 += laserPair.second;
        }
    }
};

int main()
{
    // Read input file
    std::ifstream inf{"inputs/day07.txt"};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, the file could not be opened for reading!\n";
        return 1;
    }

    auto start{std::chrono::high_resolution_clock::now()};

    std::set<int> laserLocs{};
    std::vector<std::set<int>> splitterIndices;

    // Parse the input
    std::string strInput{};
    std::getline(inf, strInput);
    laserLocs = findSplitters(strInput);
    
    std::getline(inf, strInput);
    while (std::getline(inf, strInput))
    {
        splitterIndices.push_back(findSplitters(strInput));
    }

    Answer answer{laserLocs, splitterIndices};

    auto stop{std::chrono::high_resolution_clock::now()};
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Part 1: " << answer.part1 << "\n";
    std::cout << "Part 2: " << answer.part2 << "\n";
    std::cout << "Time: " << duration.count() << " microseconds\n";

    return 0;
}
