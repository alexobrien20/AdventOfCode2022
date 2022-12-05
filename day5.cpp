#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <vector>
#include <stack>

std::string part1Answer = "";
std::string part2Answer = "";

void solvePart1(std::vector<std::stack<char>> input, std::vector<std::string> moves)
{
    for(auto & move : moves)
    {
        int amount = std::stoi(move.substr(move.find("move ") + 5, move.find(" from") - 5));
        int from = std::stoi(move.substr(move.find("from ") + 5, move.find(" to") - 3));
        int to = std::stoi(move.substr(move.find("to ") + 3, move.size()));
        for(int i = 0; i < amount; i++)
        {
            char removeElement = input[from - 1].top();
            input[to - 1].push(removeElement);
            input[from- 1].pop();
        }
    }
    for(auto & i : input)
        part1Answer += i.top();
}

void solvePart2(std::vector<std::stack<char>> input, std::vector<std::string> moves)
{
    for(auto & move : moves)
    {
        int amount = std::stoi(move.substr(move.find("move ") + 5, move.find(" from") - 5));
        int from = std::stoi(move.substr(move.find("from ") + 5, move.find(" to") - 3));
        int to = std::stoi(move.substr(move.find("to ") + 3, move.size()));
        std::stack<char> temp;
        for(int i = 0; i < amount; i++)
        {
            temp.push(input[from - 1].top());
            input[from- 1].pop();
        }
        for(int i = 0; i < amount; i++)
        {
            input[to - 1].push(temp.top());
            temp.pop();
        }
    }
    for(auto & i : input)
        part2Answer += i.top();
}

int main()
{
    std::ifstream file("input/day5.txt");
    if (!file) std::cout << "Error opening file!";
    std::string line;
    std::vector<std::string> moves;
    std::vector<std::string> firstpart;
    while (std::getline(file, line))
    {
        if(line.find("move") != std::string::npos)
        {
            moves.push_back(line);
        }
        else if(!line.empty())
        {
            firstpart.push_back(line);
        }
    }
    int max = 0;
    for(const auto & c : firstpart[firstpart.size() - 1])
    {
        if(!isblank(c))
        {
            max = (c - '0' > max) ? c - '0' : max;    
        }    
    }
    std::vector<std::vector<char>> temp(max, std::vector<char>(100, ' '));
    int counter = 0;
    for(int i = firstpart.size() - 2; i >= 0; i--)
    {
        std::string row = firstpart[i];
        for(int j = 0; j < max; j++)
        {
            if(isblank(row[1+j*4]))
                continue;
            temp[j][counter] = row[1 + j * 4];
        }   
        counter++;
    }
    std::vector<std::stack<char>> input;
    for(int i = 0; i < max; i++)
    {
        std::stack<char> tempStack;
        for(int j =0; j < temp[i].size(); j++)
        {
            if(!isblank(temp[i][j]))
            {
                tempStack.push(temp[i][j]);
            }
        }
        input.push_back(tempStack);
    }
    solvePart1(input, moves);
    solvePart2(input, moves);
    std::cout << "Answer 1 : " << part1Answer << "\n";
    std::cout << "Answer 2 : " << part2Answer << "\n";
    return 0;
}