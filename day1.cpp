#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
    std::ifstream file("input/day1.txt");
    if (!file)
    {
        std::cout << "Error opening file!";
    }
    std::vector<int> elfCounts;
    std::string line;
    int count = 0;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            elfCounts.push_back(count);
            count = 0;
        }
        else
        {
            count += std::stoi(line);
        }
    }
    std::sort(elfCounts.begin(), elfCounts.end());
    std::cout << "Part 1 : " << elfCounts[elfCounts.size() - 1] << "\n";
    std::cout << "Part 2 : " << std::reduce(elfCounts.end() - 3, elfCounts.end()) << "\n";
    return 0;
}