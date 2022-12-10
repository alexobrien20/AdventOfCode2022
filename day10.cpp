#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>

int part1Answer = 0;
std::vector<std::vector<std::string>> part2Answer;

void solvePart1(std::vector<std::string> commands)
{
    std::unordered_set<int> intervals{20,60,100,140,180,220};
    int maxCycle = 240;
    int currentCycle = 0;
    int xRegister = 1;
    auto commandIter = commands.begin();
    int addCounter = 0;
    std::vector<std::string> temp;
    for(int i = 0; i < maxCycle; i++)
    {
        if(i % 40 == 0 && i != 0)
        {
            part2Answer.push_back(temp);
            temp.clear();
        }
        std::cout << " i " << i + 1 << " reg " << xRegister << "\n";
        if(i % 40 >= xRegister - 1 && i % 40 <= xRegister + 1)
        {
            temp.push_back("#");
        }
        else
        {
            temp.push_back(".");
        }
        if(intervals.find(i + 1) != intervals.end())
        {
            part1Answer += (*intervals.find(i + 1)) * xRegister;
        }
        if((*commandIter).find("noop") != std::string::npos)
        {
            commandIter++;
            continue;
        }
        else
        {
            if(addCounter == 1)
            {
                std::string num = (*commandIter).substr((*commandIter).find(" ") + 1);
                int n = stoi(num);
                xRegister += n;
                addCounter = 0;
                commandIter++;
                // std::cout << "i " << i << " n " << n << "\n";
            }
            else
                addCounter++;
        }
    }
    part2Answer.push_back(temp);
}

int main()
{
    std::ifstream file("input/day10.txt");
    if (!file)
        std::cout << "Error opening file!";
    std::string line;
    std::vector<std::string> commands;
    while (std::getline(file, line))
    {
        commands.push_back(line);
    }
    solvePart1(commands);
    std::cout << "Part 1 Answer " << part1Answer << "\n";
    for(int i = 0; i < part2Answer.size(); i++)
    {
        for(int j = 0; j < part2Answer[i].size(); j++)
        {
            std::cout << part2Answer[i][j];
        }
        std::cout << "\n";
    }
    return 0;
}