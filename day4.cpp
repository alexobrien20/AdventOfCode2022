#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

int part1Answer = 0;
int part2Answer = 0;

void solvePart1(int aStart, int bStart, int aEnd, int bEnd)
{
    if(aStart >= bStart && aEnd <= bEnd || bStart >= aStart && bEnd <= aEnd)
        part1Answer++;
}

void solvePart2(int aStart, int bStart, int aEnd, int bEnd)
{
    if(bStart <= aEnd && bStart >= aStart)
        part2Answer++;
    else if(aStart <= bEnd && aStart >= bStart)
        part2Answer++;
}

int main()
{
    std::ifstream file("input/day4.txt");
    if (!file) std::cout << "Error opening file!";
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
        std::string a = line.substr(0, line.find(","));
        std::string b = line.substr(line.find(",") + 1, line.size());
        int aStart = std::stoi(a.substr(0, a.find("-")));
        int aEnd = std::stoi(a.substr(a.find("-") + 1, a.size()));
        int bStart = std::stoi(b.substr(0, b.find("-")));
        int bEnd = std::stoi(b.substr(b.find("-")+1, b.size()));
        solvePart1(aStart, bStart, aEnd, bEnd);
        solvePart2(aStart, bStart, aEnd, bEnd);
    }
    std::cout << "Answer 1 : " << part1Answer << "\n";
    std::cout << "Answer 2 : " << part2Answer << "\n";
    return 0;
}