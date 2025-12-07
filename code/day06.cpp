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

class ProblemSet
{
private:
    // Find the locations of the non-space characters
    // in the last element of `rawProblemSet`.
    void setOperationLocs()
    {
        for (int i{0}; i < operationStr.length(); i++)
        {
            if (!(operationStr[i] == ' '))
            {
                operationLocs.push_back(i);
            }
        }
    }

    // Set the `part2Problems` parameter
    void setPart2Problems()
    {
        // Do up to the last problem
        for (int i{0}; i < operationLocs.size() - 1; i++)
        {
            part2Problems.push_back(std::make_pair(operationLocs.at(i), operationLocs.at(i + 1) - 2));
        }
        part2Problems.push_back(std::make_pair(operationLocs.back(), operationStr.length() - 1));
    }

    // Find the number represented in the column for part 2.
    uint64_t findPart2Number(int col)
    {
        uint64_t output{0};
        // Traverse the rows of `rawProblemSet`
        for (int i{0}; i < part1ProblemLength; i++)
        {
            char c{rawProblemSet.at(i).at(col)};
            if (!(c == ' '))
            {
                c = c - '0';
                output = 10 * output + c;
            }
        }
        return output;
    }

    // Do the part 2 computation for this problem with this symbol.
    uint64_t doComputation(std::pair<int, int> problem, char symbol)
    {
        // Initialize problemAnswer to the right value.
        uint64_t problemAnswer{};
        switch (symbol)
        {
        case '+':
            problemAnswer = 0;
            break;
        case '*':
            problemAnswer = 1;
            break;
        }
        for (int col{problem.first}; col <= problem.second; col++)
        {
            uint64_t nextNumber{findPart2Number(col)};

            switch (symbol)
            {
            case '+':
                problemAnswer += nextNumber;
                break;
            case '*':
                problemAnswer *= nextNumber;
                break;
            }
        }
        return problemAnswer;
    }
public:
    std::vector<std::string> rawProblemSet{};
    std::vector<std::vector<std::string>> splitProblemSet{};

    // Dimensions of the part 1 grid
    int part1ProblemLength{};
    int part1ProblemCount{};

    // The last string in `rawProblemSet`
    std::string operationStr{};

    // Location of operations within `operationStr`
    std::vector<int> operationLocs{};

    // Stores the start and end column of each part 2 problem
    std::vector<std::pair<int, int>> part2Problems{};

    ProblemSet(std::vector<std::string> rawProblemSet)
        : rawProblemSet{rawProblemSet}
    {
        // Set `splitProblemSet`
        for (std::string str : rawProblemSet)
        {
            splitProblemSet.push_back(splitBySpaces(str));
        }

        // Set relevant variables for part 1.
        part1ProblemLength = splitProblemSet.size() - 1;
        part1ProblemCount = splitProblemSet.at(0).size();

        // Set relevant variables for part 2.
        operationStr = rawProblemSet.back();
        setOperationLocs();
        setPart2Problems();
    }

    // Do computation for Part 1
    uint64_t findPart1()
    {
        uint64_t part1{};
        // For each problem
        for (int i{0}; i < part1ProblemCount; i++)
        {
            // collect problem type
            char c{splitProblemSet.at(part1ProblemLength).at(i)[0]};

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

            for (int j{0}; j < part1ProblemLength; j++)
            {
                uint64_t nextNumber{std::stoull(splitProblemSet.at(j).at(i))};

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

            part1 += problemAnswer;
        }
        return part1;
    }

    uint64_t findPart2()
    {
        uint64_t part2{0};
        for (std::pair<int, int> problem : part2Problems)
        {
            part2 += doComputation(problem, rawProblemSet.back().at(problem.first));
        }
        return part2;
    }
};

Answer findAnswer(ProblemSet problemSet)
{
    Answer answer{};
    answer.part1 = problemSet.findPart1();
    answer.part2 = problemSet.findPart2();
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
    std::vector<std::string> rawProblemSet;
    std::string strInput{};
    while (std::getline(inf, strInput))
    {
        rawProblemSet.push_back(strInput);
    }

    // Initialize our `ProblemSet`
    ProblemSet problemSet{rawProblemSet};
    Answer answer{findAnswer(problemSet)};

    auto stop{std::chrono::high_resolution_clock::now()};
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Part 1: " << answer.part1 << "\n";
    std::cout << "Part 2: " << answer.part2 << "\n";
    std::cout << "Time: " << duration.count() << " microseconds\n";

    return 0;
}
