#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

int part1Answer = 0;
int part2Answer = 0;

std::unordered_map<std::string, int> MOVES{{"A", 1}, {"B", 2}, {"C", 3}, {"X", 1}, {"Y", 2}, {"Z", 3}};
std::unordered_map<int, int> ENDINGS{{1, 0}, {2, 3}, {3, 6}};

void solvePart1(int opp, int you)
{
    part1Answer += you;
    if (opp == 1)
    {
        if (you == 1)
        {
            part1Answer += 3;
        }
        if (you == 2)
        {
            part1Answer += 6;
        }
    }
    else if (opp == 2)
    {
        if (you == 2)
        {
            part1Answer += 3;
        }
        if (you == 3)
        {
            part1Answer += 6;
        }
    }
    else if (opp == 3)
    {
        if (you == 3)
        {
            part1Answer += 3;
        }
        if (you == 1)
        {
            part1Answer += 6;
        }
    }
}

void solvePart2(int opp, int you)
{
    if (you == 1)
    {
        // Loose
        part2Answer += (opp == 1) ? 3 : opp - 1;
    }
    else if (you == 2)
    {
        // Draw
        part2Answer += opp;
    }
    else
    {
        // Win
        part2Answer += (opp == 3) ? 1 : opp + 1;
    }
    part2Answer += ENDINGS[you];
}

int main()
{
    std::ifstream file("input/day2.txt");
    if (!file)
    {
        std::cout << "Error opening file!";
    }
    std::string line;
    while (std::getline(file, line))
    {
        int opp = MOVES[line.substr(0, line.find(" "))];
        int you = MOVES[line.substr(line.find(" ") + 1, line.size())];
        solvePart1(opp, you);
        solvePart2(opp, you);
    }
    std::cout << "Answer 1 : " << part1Answer << "\n";
    std::cout << "Answer 2 : " << part2Answer << "\n";
    return 0;
}