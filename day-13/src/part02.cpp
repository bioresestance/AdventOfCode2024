/**
 * Day-13 - Part 02
 */
#include "include.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <tuple>
#include <ranges>
#include <cmath>

static std::vector<std::tuple<double, double, double, double, double, double>> parseInput(const std::vector<std::string> &inputStrings)
{
    std::vector<std::tuple<double, double, double, double, double, double>> parsedValues;
    std::regex regexPattern(R"(X[+=](\d+), Y[+=](\d+))");
    std::smatch match;

    for (size_t i = 0; i < inputStrings.size(); i += 4)
    {
        double x1, y1, x2, y2, x3, y3;

        if (std::regex_search(inputStrings[i], match, regexPattern))
        {
            x1 = std::stof(match[1]);
            y1 = std::stof(match[2]);
        }

        if (std::regex_search(inputStrings[i + 1], match, regexPattern))
        {
            x2 = std::stof(match[1]);
            y2 = std::stof(match[2]);
        }

        if (std::regex_search(inputStrings[i + 2], match, regexPattern))
        {
            x3 = std::stof(match[1]);
            y3 = std::stof(match[2]);
        }

        parsedValues.emplace_back(x1, y1, x2, y2, x3, y3);
    }

    return parsedValues;
}

int64_t handlePart2(const std::vector<std::string> &inputLines)
{
    const auto OFFSET = 10000000000000.0; 
    auto parsedValues = parseInput(inputLines);

    uint64_t total = 0;
    for (auto &[x1, x3, x2, x4, y1, y2] : parsedValues)
    {

        y1 += OFFSET;
        y2 += OFFSET;


        // Sove a system of equation with only two unknown values and 2 equations.
        auto A = std::round((y2 - ((x4 * y1) / x2)) / (x3 - ((x1 * x4) / x2)));
        auto B = std::round((y1 / x2) - ((x1 / x2) * A));
        

        // Test that A nad B satisfy the equation of systems.
        bool is_correct = (((x1 * A) + (x2*B)) == y1) and (((x3 * A) + (x4*B)) == y2);

        if(is_correct)
        {
            total += 3*A + B;
        }
    }

    return total;
}