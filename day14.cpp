#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <array>

std::vector<std::vector<char>> cave(1000, std::vector<char>(1000, '.'));
int lowestRock = 0;


int part1Answer = 0;
int part2Answer = 0;

void fillCave(std::string line)
{
    while(line.find("->") != std::string::npos)
    {
        std::string lhs = line.substr(0, line.find("-> "));
        std::string rhs = line.substr(line.find(" -> ") + 4);
        line = rhs;
        if(rhs.find(" -> ") != std::string::npos)
            rhs = rhs.substr(0, rhs.find(" -> "));
        int xFrom = std::stoi(lhs.substr(0, line.find(",")));
        int yFrom = std::stoi(lhs.substr(line.find(",") + 1));
    
        int xTo= std::stoi(rhs.substr(0, line.find(",")));
        int yTo = std::stoi(rhs.substr(line.find(",") + 1));

        if(std::abs(xFrom - xTo) != 0)
        {
            // We are drawing horizontally
            for(int i = std::min(xFrom, xTo); i <= std::max(xFrom, xTo); i++)
            {
                cave[yFrom][i] = '#';
            }
        }
        else
        {
            // We are drawing vertically
            for(int i = std::min(yFrom, yTo); i <= std::max(yFrom, yTo); i++)
            {
                cave[i][xFrom] = '#';
            }
        }
        if(std::max(yFrom, yTo) > lowestRock)
            lowestRock = std::max(yFrom, yTo);
    }
}

void solvePart1( std::vector<std::string> input)
{
    for(const auto & s : input)
        fillCave(s);
    int x = 500;
    int y = 0;
    while(true)
    {
        if(y > lowestRock)
            break;
        if(cave[y + 1][x] == '.')
            y++;
        else if(cave[y+1][x - 1] == '.')
        {
            y++;
            x--;
        }
        else if(cave[y+1][x+1] == '.')
        {
            y++;
            x++;
        }
        else
        {
            // You must be blocked
            cave[y][x] = 'o';
            part1Answer++;
            // Then start again
            x = 500;
            y = 0;
        }
        
    }
}

void solvePart2()
{
    int floor = lowestRock + 2;
    std::cout << lowestRock << "\n";
    for(int i = 0; i < cave[0].size(); i++)
    {
        cave[floor][i] = '#';
    }
    int x = 500;
    int y = 0;
    while(true)
    {
        if(cave[y + 1][x] == '.')
            y++;
        else if(cave[y+1][x - 1] == '.')
        {
            y++;
            x--;
        }
        else if(cave[y+1][x+1] == '.')
        {
            y++;
            x++;
        }
        else
        {
            // You must be blocked
            // If you're block and we are on x = 500, y = 0; then we are done??
            if(x == 500 && y == 0)
                break;
            cave[y][x] = 'o';
            part2Answer++;
            // Then start again
            x = 500;
            y = 0;
        }
        
    }
}

int main()
{
    std::ifstream file("input/day14.txt");
    if (!file)
        std::cout << "Error opening file!";
    std::string line;
    std::vector<std::string> input;
    while (std::getline(file, line))
    {
        input.push_back(line);
    }
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    fillCave(input[0]);
    solvePart1(input);
    solvePart2();

     auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";

    for(int i = 0; i < 13; i++)
    {
        for(int j = 480; j < 520; j++)
        {
            std::cout << cave[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "Part 1 Answer : " << part1Answer << "\n";
    std::cout << "Part 2 Answer : " << part2Answer + part1Answer + 1 << "\n";
    std::cout << lowestRock << "\n";
    return 0;
}