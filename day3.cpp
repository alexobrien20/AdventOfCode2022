#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <vector>

int part1Answer = 0;
int part2Answer = 0;

void solvePart2(std::string a, std::string b, std::string c)
{   
    std::set<char> aSet(a.begin(), a.end());
    std::set<char> bSet(b.begin(), b.end());
    std::set<char> cSet(c.begin(), c.end());
    std::set<char> intersection;
    std::set_intersection(aSet.begin(), aSet.end(), bSet.begin(), bSet.end(),
                        std::inserter(intersection, intersection.begin()));
    std::set<char> badge;
    std::set_intersection(cSet.begin(), cSet.end(), intersection.begin(), intersection.end(),
                        std::inserter(badge, badge.begin()));
    for(auto const & c : badge)
    {
        if(isupper(c))
            part2Answer += (c - 38);
        else
            part2Answer += (c - 96);
    }
}

void solvePart1(std::string a)
{
    std::string lhs = a.substr(0, a.size() / 2);
    std::string rhs = a.substr((a.size() / 2), a.size());
    std::set<char> lSet(lhs.begin(), lhs.end());
    std::set<char> rSet(rhs.begin(), rhs.end());
    std::set<char> intersection;
    std::set_intersection(lSet.begin(), lSet.end(), rSet.begin(), rSet.end(),
                        std::inserter(intersection, intersection.begin()));
    for(const auto & c : intersection)
    {
        if(isupper(c))
            part1Answer += (c - 38);
        else
            part1Answer += (c - 96);
    }
}

int main()
{
    std::ifstream file("input/day3.txt");
    if (!file) std::cout << "Error opening file!";
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
        solvePart1(line);
    }
    for(int i = 0; i <= lines.size() - 3; i+=3)
    {
        solvePart2(lines[i],lines[i+1], lines[i+2]);
    }
    std::cout << "Answer 1 : " << part1Answer << "\n";
    std::cout << "Answer 2 : " << part2Answer << "\n";
    return 0;
}