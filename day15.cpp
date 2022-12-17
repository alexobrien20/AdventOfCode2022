#include <iostream>
#include <fstream>
#include <vector>

int part1Answer = 0;
int part2Answer = 0;

int xCenter = 5000000;

int manHat(int x1, int x2, int y1, int y2)
{
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

void solvePart1(std::vector<std::string> commands, int answerLine)
{
    std::vector<char> tunnel(10000000, '.');
    for(const auto & line : commands)
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


        int maxManHat = manHat(sX, bX, sY, bY);
        int ytop1 = sY - maxManHat;
        int ytop2 = sY + maxManHat;
        int yTop = std::max(ytop1, ytop2);
        int yBot = std::min(ytop1, ytop2);
        for(int i = yBot; i <= yTop; i++)
        if(answerLine > yTop || answerLine < yBot)
            continue;

        if(sY == answerLine)
            tunnel[sX + xCenter] = 'S';
        if(bY == answerLine)
            tunnel[bX + xCenter] = 'B';
        
        std::cout << "y top " << yTop << " y bot" << yBot << "\n";
        int xtop1 = sX - maxManHat;
        int xtop2 = sX + maxManHat;
        int xTop = std::max(xtop1, xtop2);
        int xBot = std::min(xtop1, xtop2);
        
        int amountOfHashes = (xTop - xBot) - 2 * std::abs(sY - answerLine);
        int eachWay = amountOfHashes / 2;
        std::cout << "Amount to draw " << eachWay << "\n";
        for(int i = 0; i <= eachWay; i++)
        {
            if(tunnel[sX + xCenter + i] != '.')
                continue;
            tunnel[sX+xCenter + i] = '#';
        }
        for(int i = 0; i <= eachWay; i++)
        {
            if(tunnel[sX + xCenter - i] != '.')
                continue;
            tunnel[sX+xCenter - i] = '#';
        }
    }
    for(int i = 0; i < tunnel.size(); i++)
    {
        if(tunnel[i] == '#')
            part1Answer++;
    }
}

void solvePart2(std::vector<std::string> commands, int maxValue)
{
    std::vector<std::vector<char>> tunnelPart2(4000001, std::vector<char>(4000001, '.'));
    for(const auto & line : commands)
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

        if(sY <= maxValue && sY >= 0 && sX <= maxValue && sX >= 0)
                tunnelPart2[sY][sX] = 'S';
        if(bY <= maxValue && bY >= 0 && bX <= maxValue && bX >= 0)
            tunnelPart2[bY][bX] = 'B';
        
        int maxManHat = manHat(sX, bX, sY, bY);
        int ytop1 = sY - maxManHat;
        int ytop2 = sY + maxManHat;
        int yTop = std::max(ytop1, ytop2);
        int yBot = std::min(ytop1, ytop2);
        std::cout << "y top " << yTop << " y bot" << yBot << "\n";
        for(int i = yBot; i <= yTop; i++)
        {
            if(i > maxValue || i < 0)
                continue;
                

            std::cout << "i " << i << "\n";
            int xtop1 = sX - maxManHat;
            int xtop2 = sX + maxManHat;
            int xTop = std::max(xtop1, xtop2);
            int xBot = std::min(xtop1, xtop2);
            
            int amountOfHashes = (xTop - xBot) - 2 * std::abs(sY - i);
            int eachWay = amountOfHashes / 2;
            std::cout << "Amount to draw " << eachWay << "\n";
            
            
            for(int j = 0; j <= eachWay; j++)
            {
                if(sX + j > maxValue || sX + j < 0)
                    continue;
                if(tunnelPart2[i][sX + j] != '.')
                    continue;
                tunnelPart2[i][sX + j] = '#';
            }
            for(int j = 0; j <= eachWay; j++)
            {
                if(sX - j > maxValue || sX - j < 0)
                    continue;
                if(tunnelPart2[i][sX - j] != '.')
                    continue;
                tunnelPart2[i][sX - j] = '#';
            }
        }
    }
    for(int i = 0; i < tunnelPart2.size(); i++)
    {
        for(int j = 0; j < tunnelPart2[0].size(); j++)
        {
            if(tunnelPart2[i][j] == '.')
                part2Answer = 4000000 * j + i;
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
        commands.push_back(line);
    }
    solvePart1(commands, 2000000);
    // solvePart2(commands, 4000000);
    std::cout << part1Answer << "\n";
    std::cout << part2Answer << "\n";
    return 0;
}
