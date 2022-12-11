#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

int part1Answer = 0;
int part2Answer = 0;

void solvePart1(std::vector<std::vector<int>> matrix)
{
    // Outer edge = visible already
    std::vector<std::tuple<int,int>> moves{{-1, 0},{1,0},{0,-1},{0,1}};
    for(int i = 1; i < matrix.size() - 1; i++)
    {
        for(int j = 1; j < matrix[0].size() - 1; j++)
        {
            for(const auto & move : moves)
            {
                bool visible = false;
                int diOriginal = std::get<0>(move);
                int djOriginal = std::get<1>(move);
                int di = std::get<0>(move);
                int dj = std::get<1>(move);
                while(j + dj >= 0 && j + dj < matrix[0].size() && i + di >= 0 && i + di < matrix.size())
                {
                    int nextTree = matrix[i + di][j + dj];
                    if(nextTree >= matrix[i][j])
                    {
                        visible = false;
                        break;
                    }
                    else
                        visible = true;
                    di += diOriginal;
                    dj += djOriginal;
                }
                if(visible)
                {
                    part1Answer++;
                    break;
                }
            }
        }
    }
    part1Answer += matrix[0].size() * 2;
    part1Answer += (matrix.size() - 2) * 2;
}

void solvePart2(std::vector<std::vector<int>> matrix)
{
    // Outer edge = visible already
    std::vector<std::tuple<int,int>> moves{{-1, 0},{1,0},{0,-1},{0,1}};
    for(int i = 1; i < matrix.size() - 1; i++)
    {
        for(int j = 1; j < matrix[0].size() - 1; j++)
        {
            int treeScore = 1;
            for(const auto & move : moves)
            {
                int directionScore = 0;
                int diOriginal = std::get<0>(move);
                int djOriginal = std::get<1>(move);
                int di = std::get<0>(move);
                int dj = std::get<1>(move);
                while(j + dj >= 0 && j + dj < matrix[0].size() && i + di >= 0 && i + di < matrix.size())
                {
                    int nextTree = matrix[i + di][j + dj];
                    if(nextTree >= matrix[i][j])
                    {
                        directionScore++;
                        break;
                    }
                    directionScore++;
                    di += diOriginal;
                    dj += djOriginal;
                }
                treeScore *= directionScore;
            }
            if(treeScore > part2Answer)
                part2Answer = treeScore;
        }
    }
}

int main()
{
    std::ifstream file("input/day8.txt");
    if (!file)
        std::cout << "Error opening file!";
    std::string line;
    std::vector<std::vector<int>> matrix;
    while (std::getline(file, line))
    {
        std::vector<int> tempRow;
        for(const auto & c : line)
        {
            tempRow.push_back(c - '0');
        }
        matrix.push_back(tempRow);
    }
    solvePart1(matrix);
    solvePart2(matrix);
    std::cout << "Part 1 Answer : " << part1Answer << "\n";
    std::cout << "Part 2 Answer : " << part2Answer << "\n";
    return 0;
}