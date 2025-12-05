#include <iostream>
#include <fstream>
#include <set>     // for std::set
#include <cstdint> // for fixed width integers
#include <chrono>  // for std::chrono::high_resolution_clock()
#include <string>  // for std::getline
#include <vector>
#include <array>

class Answer
{
public:
    uint64_t part1{0};
    uint64_t part2{0};
};

class RollGrid
{
    std::array<std::tuple<int, int>, 8> adjacentDirs{
        {std::make_tuple(-1, -1),
         std::make_tuple(0, -1),
         std::make_tuple(1, -1),
         std::make_tuple(-1, 0),
         std::make_tuple(1, 0),
         std::make_tuple(-1, 1),
         std::make_tuple(0, 1),
         std::make_tuple(1, 1)}};
public:
    std::vector<std::string> grid{};
    int rows{};
    int cols{};
    // Sets the parameters `rows` and `cols` based on the
    // size of the vector `grid` as well as the length of the first
    // string found in `grid`.
    void setSize()
    {
        rows = grid.size();
        cols = grid.at(0).length();
    }
    // Returns if the specified location is a roll.
    // If the location is not in the grid, returns `false`.
    bool isRoll(int row, int col)
    {
        if ((row < 0 || row >= rows) || (col < 0 || col >= cols))
            return false;
        return (grid.at(row)[col] == '@');
    }
    // Count the adjacent rolls at the specified location.
    int countAdjacentRolls(int row, int col)
    {
        int count{0};
        for (std::tuple<int, int> dir : adjacentDirs)
        {
            if (isRoll(row + std::get<0>(dir), col + std::get<1>(dir)))
            {
                // std::cout << std::get<0>(dir) << " " << std::get<1>(dir) << "\n";
                count++;
            }
        }
        return count;
    }
    // Removes all rolls from the grid which have less than 4 adjacent rolls.
    // Returns how many rolls were removed in this way.
    size_t removeLonelyRolls()
    {
        std::set<std::tuple<int, int>> lonelyRollLocs{};
        for (int row{0}; row < rows; row++)
        {
            for (int col{0}; col < cols; col++)
            {
                if (!isRoll(row, col))
                    continue;
                if (countAdjacentRolls(row, col) < 4)
                {
                    // std::cout << row << " " << col << "\n";
                    lonelyRollLocs.insert(std::make_tuple(row, col));
                }
            }
        }
        size_t output{lonelyRollLocs.size()};
        // Remove all lonely rolls
        for (std::tuple<int, int> lonelyRollLoc : lonelyRollLocs)
        {
            int row{std::get<0>(lonelyRollLoc)};
            int col{std::get<1>(lonelyRollLoc)};
            grid.at(row)[col] = '.';
        }
        return output;
    }
};

// Outputs answer to the day.
Answer findAnswer(RollGrid rollGrid)
{
    Answer answer{};
    uint64_t removedLonelyRolls{rollGrid.removeLonelyRolls()};
    answer.part1 = removedLonelyRolls;
    while (removedLonelyRolls > 0)
    {
        answer.part2 += removedLonelyRolls;
        removedLonelyRolls = rollGrid.removeLonelyRolls();
    }
    return answer;
}

int main()
{
    // Read input file
    std::ifstream inf{"inputs/day04.txt"};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, the file could not be opened for reading!\n";
        return 1;
    }

    auto start{std::chrono::high_resolution_clock::now()};

    // Initialize rollGrid and give it the following inputs.
    std::string strInput{};
    RollGrid rollGrid{};
    while (std::getline(inf, strInput))
    {
        // std::cout << strInput << "\n";
        rollGrid.grid.push_back(strInput);
    }
    rollGrid.setSize();
    
    Answer answer{findAnswer(rollGrid)};

    auto stop{std::chrono::high_resolution_clock::now()};
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Part 1: " << answer.part1 << "\n";
    std::cout << "Part 2: " << answer.part2 << "\n";
    std::cout << "Time: " << duration.count() << " microseconds\n";

    return 0;
}
