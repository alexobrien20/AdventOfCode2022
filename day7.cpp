#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>

long long part1Answer = 0;
long long part2Answer = 0;

struct directory
{
    directory() {}
    directory(std::string n) : name(n) {}
    std::unordered_map<std::string, std::shared_ptr<directory>> nestedDirs;
    std::shared_ptr<directory> prevDir;
    long long size;
    std::string name;
};

std::vector<long long> counts;

long long getNestedSize(std::shared_ptr<directory> currentDir)
{
    // If 0 then just return the size of that node
    if (currentDir->nestedDirs.size() == 0)
    {
        if (currentDir->size <= 100000)
            part1Answer += currentDir->size;
        counts.push_back(currentDir->size);
        return currentDir->size;
    }
    for (const auto &[key, value] : currentDir->nestedDirs)
    {
        currentDir->size += getNestedSize(value);
    }
    currentDir->nestedDirs.clear();
    counts.push_back(currentDir->size);
    if (currentDir->size <= 100000)
        part1Answer += currentDir->size;
    return currentDir->size;
}

void solvePart1(std::shared_ptr<directory> dirs)
{
    auto currentDir = dirs;
    for (const auto &[key, value] : currentDir->nestedDirs)
    {
        currentDir->size += getNestedSize(value);
    }
    if (currentDir->size <= 100000)
        part1Answer += currentDir->size;
    counts.push_back(currentDir->size);
}

void solvePart2()
{
    long long totalSpace = 70000000;
    long long spaceLeft = totalSpace - counts.back();
    long long spaceNeeded = 30000000 - spaceLeft;
    std::vector<long long> bigEnough;
    std::copy_if(counts.begin(), counts.end(),
                 std::back_inserter(bigEnough), [&](long long size)
                 { return size >= spaceNeeded; });
    part2Answer = *std::min_element(bigEnough.begin(), bigEnough.end());
}

int main()
{
    std::ifstream file("input/day7.txt");
    if (!file)
        std::cout << "Error opening file!";
    std::string line;
    std::unordered_map<std::string, std::vector<std::string>> charCounts;
    std::unordered_map<std::string, int> intCounts;
    int tempSum = 0;
    int level = 0;
    std::string key;
    std::shared_ptr<directory> dirs = std::make_shared<directory>("root");
    // std::unordered_map<std::string, std::shared_ptr<directory>> dirs;
    std::shared_ptr<directory> currentDir = dirs;
    dirs->nestedDirs["/"] = std::make_shared<directory>("/");
    while (std::getline(file, line))
    {
        if (line.substr(2, 2) == "cd" && line.find("..") == std::string::npos)
        {
            key = line.substr(line.find("cd") + 3);
            auto temp = currentDir;
            currentDir = currentDir->nestedDirs[key];
            currentDir->prevDir = temp;
        }
        else if (line.substr(2, 2) == "cd")
        {
            // Must be a cd ..
            currentDir = currentDir->prevDir;
        }
        else if (line.find("dir") != std::string::npos)
        {
            std::string newDirKey = line.substr(line.find("dir") + 4);
            auto newDir = std::make_shared<directory>(newDirKey);
            currentDir->nestedDirs[newDirKey] = newDir;
        }
        else if (std::find_if(line.begin(), line.end(), ::isdigit) != line.end())
        {
            long long n = std::stoll(line.substr(0, line.find(" ")));
            currentDir->size += n;
        }
    }
    solvePart1(dirs->nestedDirs["/"]);
    solvePart2();
    std::cout << "Part 1 Answer " << part1Answer << "\n";
    std::cout << "Part 2 Answer " << part2Answer << "\n";
    return 0;
}