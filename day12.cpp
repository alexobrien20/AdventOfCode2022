#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits.h>

typedef std::pair<int,int> coords;


int part1Answer = 0;
int part2Answer = INT_MAX;


int solvePart1(std::vector<std::vector<char>> matrix, int startX, int startY, char startElevation, char endElevation, char endChar)
{
    matrix[startX][startY] = startElevation;
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::vector<std::vector<int>> dists(rows, std::vector<int>(cols, INT8_MAX));
    dists[startX][startY] = 0;

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    visited[startX][startY] = true;

    std::queue<std::tuple<int,int>> q;
    q.push({startX,startY});
    std::vector<std::tuple<int,int>> moves {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    while(!q.empty())
    {
        std::tuple<int,int> currentPos = q.front();
        q.pop();
        int x = std::get<0>(currentPos);
        int y = std::get<1>(currentPos);
        for(const auto & move : moves)
        {
            int newX = x + std::get<0>(move);
            int newY = y + std::get<1>(move);
            try{
                if(visited.at(newX).at(newY))
                    continue;
                if(matrix.at(newX).at(newY) - matrix.at(x).at(y) > 1 && matrix.at(newX).at(newY) != 'E')
                    continue;
                if(matrix.at(newX).at(newY) == endChar && endElevation - matrix.at(x).at(y) > 1)
                    continue;
                if(matrix[newX][newY] == endChar)
                {
                    return dists[x][y] + 1;
                }
                visited[newX][newY] = true;
                q.push({newX,newY});
                dists[newX][newY] = dists[x][y] + 1;
            }
            catch(std::out_of_range const &exec) {}
        }
    }
    return INT_MAX;
}

int main()
{
    std::ifstream file("input/day12.txt");
    if (!file)
        std::cout << "Error opening file!";
    std::string line;
    std::vector<std::vector<char>> matrix;
    int startY = 0;
    int startX = 0;
    int xCounter = 0;
    std::vector<std::tuple<int,int>> allAs;
    while (std::getline(file, line))
    {
       std::vector<char> temp;
       int yCounter = 0;
       for(const auto & c : line)
       {
            if(c == 'S')
            {
                startY = yCounter;
                startX = xCounter;
            }
            if(c == 'a')
            {
                allAs.push_back({xCounter, yCounter});
            }
            temp.push_back(c);
            yCounter++;
       }
       matrix.push_back(temp);
       xCounter++;
    }   
    part1Answer = solvePart1(matrix, startX, startY, 'a', 'z', 'E');

    for(const auto & a : allAs)
    {
        int x = std::get<0>(a);
        int y = std::get<1>(a);
        int temp = solvePart1(matrix, x, y, 'a', 'z', 'E');
        if(temp < part2Answer)
            part2Answer = temp;
    }

    std::cout << "Part 1 Answer : " << part1Answer << "\n";
    std::cout << "Part 2 Answer : " << part2Answer << "\n";
    return 0;
}