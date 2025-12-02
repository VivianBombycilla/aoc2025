#include <iostream>
#include <fstream>
#include <string> // for std::stoi
#include <cstdint> // for uint64_t

// Integer exponentiation because why doesnt C++ have that???
int pow(int base, int exp)
{
    int output = 1;
    for (int i = 0; i < exp; i++)
    {
        output *= base;
    }
    return output;
}

// Finds the first invalid id which is either <= (if prev=True)
// or >= (if prev=False) to the given id.
int findAdjacentInvalidID(std::string id, bool prev)
{
    int idLength = id.length();
    if (idLength % 2 == 0) {
        int firstHalf{std::stoi(id.substr(0, idLength / 2))};
        int secondHalf{std::stoi(id.substr(idLength / 2))};
        int output{firstHalf};
        if (prev && (firstHalf != secondHalf))
        {
            output--;
        }
        if (firstHalf < secondHalf)
        {
            output++;
        }
        return output;
    } else
    {
        int output{pow(10, idLength / 2)};
        if (prev)
            output--;
        return output;
    }
}

// Sum invalid IDs.
int sumInvalidIDs(std::string minID, std::string maxID)
{
    int minInvalidID{findAdjacentInvalidID(minID, false)};
    int maxInvalidID{findAdjacentInvalidID(maxID, true)};
    long long output{0};
    for (int i = minInvalidID; i <= maxInvalidID; i++)
    {
        std::cout << "invalid id: " << std::stoi(std::to_string(i) + std::to_string(i)) << "\n";
        output += std::stoi(std::to_string(i) + std::to_string(i));
    }
    std::cout << output;
    return output;
}

// Outputs string up to the next delimiter,
// modifying the original string.
std::string nextSubstring(std::string& str, std::string delim)
{
    size_t n{str.find(delim)};
    
    if (n != std::string::npos)
    {
        std::string output{str.substr(0, n)};
        if (n + delim.length() < str.length())
            str = str.substr(n + delim.length());
        else
            str = "";
        return output;
    }
    str = "";
    return "";
}


int main()
{
    // Read input file
    std::ifstream inf{"inputs/day02e.txt"};

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, the file could not be opened for reading!\n";
        return 1;
    }

    int first{};
    int last{};
    char c{};
    long long part1{0};
    while (inf)
    {
        inf >> first;
        inf.get();
        inf >> last;
        c = inf.get();
        std::cout << first << " " << last << "\n";
        part1 += sumInvalidIDs(std::to_string(first), std::to_string(last));

        std::cout << "running sum: " << part1 << "\n";
        if (c == '\n') break;
    }
    std::cout << "Part 1: " << part1;
}
