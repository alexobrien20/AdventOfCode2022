#include <iostream>
#include <fstream>
#include <vector>

int part1Answer = 0;
int part2Answer = 0;

std::vector<std::vector<char>> tunnel(100, std::vector<char>(100, '.'));

int manHat(int x1, int x2, int y1, int y2)
{
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

void solvePart1(std::string line)
{
    std::string sensor = line.substr(0, line.find(":"));
    std::string beacon = line.substr(line.find(":") + 1);
    std::string sensorX = sensor.substr(0, sensor.find(","));
    std::string sensorY = sensor.substr(sensor.find(",") + 1);
    int sX = std::stoi(sensorX.substr(sensorX.find("x=") + 2));
    int sY = std::stoi(sensorY.substr(sensorY.find("y=") + 2));

    std::string beaconX = beacon.substr(0, beacon.find(","));
    std::string beaconY = beacon.substr(beacon.find(",") + 1);
    int bX = std::stoi(beaconX.substr(beaconX.find("x=") + 2));
    int bY = std::stoi(beaconY.substr(beaconY.find("y=") + 2));

    // Make 50,50 be the center.

    tunnel[sY + 50][sX + 50] = 'S';
    tunnel[bY + 50][bX + 50] = 'B';

    int maxManHat = manHat(sX, bX, sY, bY);
    // Iterater over the y, then fill in the x?!?
    while (manHat(sX, bX, sY, sY) <= maxManHat)
    {
        int y = sY;
        int x = sX;
        x++;
        // Just work it out by hand!?
        while (manHat(sX, x, sY, y) <= maxManHat)
        {
        }
    }
}
int main()
{
    std::ifstream file("input/day15.txt");
    if (!file)
        std::cout << "Error opening file!";
    std::string line;
    std::vector<std::string> commands;
    while (std::getline(file, line))
    {
        solvePart1(line);
    }
    for (int i = 40; i < 70; i++)
    {
        for (int j = 40; j < 100; j++)
        {
            std::cout << tunnel[i][j];
        }
        std::cout << "\n";
    }
    return 0;
}