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

class Answer
{
public:
    uint64_t part1{0};
    uint64_t part2{0};
};

class ProblemSet
{
public:
    std::vector<std::vector<std::string>> rawProblemSet{};
    int problemLength{};
    int problemCount{};
    void setStats()
    {
        problemLength = rawProblemSet.size() - 1;
        problemCount = rawProblemSet.at(0).size();
    }
};

// Prints vector
void printVector(std::vector<std::string> v)
{
    for (std::string n : v)
    {
        std::cout << n << ", ";
    }
    std::cout << "\n";
}

// splits string by abritrary number of spaces each.
std::vector<std::string> splitBySpaces(std::string str)
{
    std::istringstream iss{str};
    std::string nextItem{};
    std::vector<std::string> output{};
    while (std::getline(iss, nextItem, ' '))
    {
        if (nextItem == "")
            continue;
        output.push_back(nextItem);
    }
    return output;
}

Answer findAnswer(ProblemSet problemSet)
{
    Answer answer{};
    // For each problem
    for (int i{0}; i < problemSet.problemCount; i++)
    {
        // collect problem type
        char c{problemSet.rawProblemSet.at(problemSet.problemLength).at(i)[0]};
        std::cout << "c: " << c << "\n";
        // compute the problem
        uint64_t problemAnswer{};
        switch (c)
        {
            case '+':
                problemAnswer = 0;
                break;
            case '*':
                problemAnswer = 1;
                break;
        }

        std::cout << "problemAnswer: " << problemAnswer << "\n";
        for (int j{0}; j < problemSet.problemLength; j++)
        {
            uint64_t nextNumber{std::stoull(problemSet.rawProblemSet.at(j).at(i))};
            std::cout << "nextNumber: " << nextNumber << "\n";

            switch (c)
            {
            case '+':
                problemAnswer += nextNumber;
                break;
            case '*':
                problemAnswer *= nextNumber;
                break;
            }
        }
        std::cout << "c: " << c << "\n";
        std::cout << "problemAnswer: " << problemAnswer << "\n";
        answer.part1 += problemAnswer;
    }
    return answer;
}

int main()
{
    // Read input file
    std::ifstream inf{"inputs/day06.txt"};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, the file could not be opened for reading!\n";
        return 1;
    }

    auto start{std::chrono::high_resolution_clock::now()};

    // Parse the input
    ProblemSet problemSet{};
    std::string strInput{};
    while (std::getline(inf, strInput))
    {
        problemSet.rawProblemSet.push_back(splitBySpaces(strInput));
    }
    problemSet.setStats();

    Answer answer{findAnswer(problemSet)};

    auto stop{std::chrono::high_resolution_clock::now()};
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Part 1: " << answer.part1 << "\n";
    std::cout << "Part 2: " << answer.part2 << "\n";
    std::cout << "Time: " << duration.count() << " microseconds\n";

    return 0;
}
