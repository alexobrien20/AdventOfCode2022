#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>

long long part1Answer = 0;
int part2Answer = 0;

void r(std::unordered_map<std::string, int> ints, std::unordered_map<std::string, std::vector<std::string>> chars)
{

}

struct directory
{
    directory() {}
    directory(std::string n) : name(n) {}
    std::vector<std::string> nestedDirs;
    long long size;
    std::string name;
};

// Check LONG long!>>!

long long getNestedSize(std::shared_ptr<directory> &currentDir, std::unordered_map<std::string, std::shared_ptr<directory>> &directories)
{
    // If 0 then just return the size of that node
    if(currentDir->nestedDirs.size() == 0)
        return currentDir->size;
    for(auto nest : currentDir->nestedDirs)
    {
        auto nestedDir = directories[nest];
        currentDir->size += getNestedSize(nestedDir, directories);
    }   
    currentDir->nestedDirs.erase(currentDir->nestedDirs.begin(), currentDir->nestedDirs.end());
    return currentDir->size;
}

void solvePart1(std::unordered_map<std::string, std::shared_ptr<directory>> &directories)
{
    for(const auto& [key, value] : directories)
    {
        // Need to recurse on the number of nested.
        for(auto nest : value->nestedDirs)
        {
            auto nestedDir = directories[nest];
            std::cout << "Key " << key << " nested key " << nest << "\n";
            value->size += getNestedSize(nestedDir, directories);
            std::cout << "v " << value->size << "\n";
        }
        value->nestedDirs.erase(value->nestedDirs.begin(), value->nestedDirs.end());
    }   
    for(const auto& [key, value] : directories)
    {
        std::cout << "Key " << key << " " << value->size << "\n";
        if(value->size <= 100000)
            part1Answer +=value->size;
    }
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
    std::string key = "root";
    std::unordered_map<std::string, std::shared_ptr<directory>> dirs;
    std::shared_ptr<directory> currentDir;
    while (std::getline(file, line))
    {
        std::cout << line << "\n";
        std::cout << line.substr(2, 2) << "\n";
        if(line.substr(2, 2) == "cd" && line.find("..") == std::string::npos)
        {
            key = line.substr(line.find("cd") + 3);
            std::cout << key << "\n";
            auto d = std::make_shared<directory>(key);
            currentDir = d;
            dirs[key] = d;
        }
        else if(line.find("dir") != std::string::npos)
        {
            std::string otherDir = line.substr(line.find("dir") + 4);
            currentDir->nestedDirs.push_back(otherDir);
        }
        else if(std::find_if(line.begin(), line.end(), ::isdigit) != line.end())
        {
            // std::cout << line << "\n";
            long long n = std::stoll(line.substr(0, line.find(" ")));
            currentDir->size += n;
        }
    }
    std::cout << dirs.size() << "\n";
    for(const auto& [key, value]: dirs)
    {
        std::cout << value->name << " " << value->size << " num of nested " << value->nestedDirs.size() << "\n";
    }
    solvePart1(dirs);
    std::cout << "Part 1 Answer " << part1Answer << "\n";
    return 0;
}