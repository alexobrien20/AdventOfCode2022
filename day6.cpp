#include <iostream>
#include <fstream>
#include <set>

int part1Answer = 0;
int part2Answer = 0;

int solvePart1(std::string line, int n)
{
    for (int i = 0; i < line.size() - n; i++)
    {
        std::string firstFour = line.substr(i, n);
        std::set<char> v(firstFour.begin(), firstFour.end());
        if (v.size() == n)
        {
            return i + n;
        }
    }
    return 0;
}

int main()
{
    std::ifstream file("input/day6.txt");
    if (!file)
        std::cout << "Error opening file!";
    std::string line;
    while (std::getline(file, line))
    {
        part1Answer = solvePart1(line, 4);
        part2Answer = solvePart1(line, 14);
    }
    std::cout << "Answer 1 : " << part1Answer << "\n";
    std::cout << "Answer 2 : " << part2Answer << "\n";
    return 0;
}