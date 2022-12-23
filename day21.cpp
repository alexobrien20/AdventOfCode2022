#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

double part1Answer = 0;
double doublepart2Answer = 0;

std::unordered_map<std::string, std::tuple<std::string,std::string,std::string>> stringMap;
std::unordered_map<std::string, double> numberMap;


double doOperation(double left, double right, std::string operation)
{
    if(operation == "+")
        return left + right;
    if(operation == "/")
        return left / right;
    if(operation == "*")
        return left * right;
    return left - right;
}

double solvePart1(std::string lhs, std::string rhs, std::string operation, bool stop = false)
{
    if(stop == true && (rhs == "humn" || lhs == "humn"))
        return 1;
    double left = 0;
    double right = 0;
    if(stringMap.find(rhs) != stringMap.end())
    {
        // The rhs isn't a number so we need to find that number
        std::string newRhs = std::get<0>(stringMap[rhs]);
        std::string newLhs = std::get<1>(stringMap[rhs]);
        std::string newOperation = std::get<2>(stringMap[rhs]);
        right = solvePart1(newRhs, newLhs, newOperation);
    }
    else
        right = numberMap[rhs];
    if(stringMap.find(lhs) != stringMap.end())
    {
        std::string newRhs = std::get<0>(stringMap[lhs]);
        std::string newLhs = std::get<1>(stringMap[lhs]);
        std::string newOperation = std::get<2>(stringMap[lhs]);
        left = solvePart1(newRhs, newLhs, newOperation);
    }
    else
        left = numberMap[lhs];
    return doOperation(left, right, operation);
}

int main()
{
    std::ifstream file("input/day21.txt");
    if (!file)
        std::cout << "Error opening file!";
    std::string line;
    std::vector<std::string> operations{"+", "/", "*", "-"};
    while (std::getline(file, line))
    {
        std::string monkeyName = line.substr(0,line.find(":"));
        std::string rhs = line.substr(line.find(":") + 2);
        for(const auto & operation : operations)
        {
            if(rhs.find(operation) != std::string::npos)
            {
                std::string leftName = rhs.substr(0, rhs.find(operation) - 1);
                std::string rightName = rhs.substr(rhs.find(operation) + 2);
                stringMap[monkeyName] = {leftName, rightName, operation};
                break;
            }
        }
        if(stringMap.find(monkeyName) == stringMap.end())
            numberMap[monkeyName] = std::stoll(rhs);
    }
    std::string start;
    double finalValue;

    std::string rootLeft = std::get<0>(stringMap["root"]);
    std::string rootRight = std::get<1>(stringMap["root"]);
    part1Answer = solvePart1(rootLeft,rootRight, std::get<2>(stringMap["root"]));

    double finalLeft = solvePart1(std::get<0>(stringMap[rootLeft]), std::get<1>(stringMap[rootLeft]), std::get<2>(stringMap[rootLeft]));
    double finalRight =  solvePart1(std::get<0>(stringMap[rootRight]), std::get<1>(stringMap[rootRight]), std::get<2>(stringMap[rootRight]));

    if(solvePart1(std::get<0>(stringMap[rootLeft]), std::get<1>(stringMap[rootLeft]), std::get<2>(stringMap[rootLeft]), true))
    {
        // humn is on the left side
        start = std::get<0>(stringMap["root"]);
        finalValue = finalRight;
    }
    else
    {
        // humn is on the right side.
        start = std::get<1>(stringMap["root"]);
        finalValue = finalLeft;
    }
    double temp = solvePart1(std::get<0>(stringMap[start]), std::get<1>(stringMap[start]), std::get<2>(stringMap[start]), true);
    std::cout << "temp value " << temp << "\n";
    std::cout << "temp value " << finalValue << "\n";
    double midpoint;
    double minRange = (temp < finalValue) ? numberMap["humn"] : 100000000000000;
    double maxRange = (temp > finalValue) ? numberMap["humn"] : 100000000000000;
    while(temp != finalValue)
    {
        midpoint = (minRange + maxRange ) / 2.0;
        numberMap["humn"] = midpoint;
        temp = solvePart1(std::get<0>(stringMap[start]), std::get<1>(stringMap[start]), std::get<2>(stringMap[start]), true);
        std::cout << "mid point " << midpoint << " range " << minRange << " to " << maxRange << " temp " << temp << "\n";
        if(temp - finalValue > 0)
            maxRange = midpoint;
        else if(temp - finalValue < 0)
            minRange = midpoint;
    }
    std::cout << std::fixed;
    std::cout << "Final left number : " << finalLeft << " Final right number : " << finalRight << "\n";
    std::cout << "Final value we want to reach " << finalValue << "\n";
    std::cout << "Our final value " << temp << "\n";
    std::cout << "Part 1 Answer : " << part1Answer << "\n";
    std::cout << "Part 2 Answer : " << numberMap["humn"] << "\n";
    return 0;
}
