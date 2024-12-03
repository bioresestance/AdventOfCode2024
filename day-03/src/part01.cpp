/**
 * Day-3 - Part 01
 */
#include "include.hpp"
#include <regex>
#include <iostream>

int64_t handlePart1(const std::vector<std::string> &inputLines)
{
    std::regex pattern(R"(mul\(\d{1,3},\d{1,3}\))");
    std::smatch matches;
    uint64_t result = 0;
    for (const auto &line : inputLines)
    {
        std::string::const_iterator searchStart(line.cbegin());
        while (std::regex_search(searchStart, line.cend(), matches, pattern))
        {
            searchStart = matches.suffix().first;

            // Extract the two numbers from the match
            std::string matchStr = matches[0];
            std::string num1Str = matchStr.substr(4, matchStr.find(',') - 4);
            std::string num2Str = matchStr.substr(matchStr.find(',') + 1, matchStr.size() - 1 - matchStr.find(',') - 1);

            result += std::stoull(num1Str) * std::stoull(num2Str);
        }
    }
    return result;
}