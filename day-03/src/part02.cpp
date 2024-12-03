/**
 * Day-3 - Part 02
 */
#include "include.hpp"
#include <regex>
#include <iostream>
#include <string>
#include <vector>

int64_t handlePart2(const std::vector<std::string> &inputLines)
{
    std::regex pattern(R"((mul\(\d{1,3},\d{1,3}\))|(do\(\))|(don't\(\)))");
    std::smatch matches;
    uint64_t result = 0;
    bool enabled = true;
    for (const auto &line : inputLines)
    {
        std::string::const_iterator searchStart(line.cbegin());
        while (std::regex_search(searchStart, line.cend(), matches, pattern))
        {
            searchStart = matches.suffix().first;

            std::string matchStr = matches[0];
            if (matchStr.find("mul(") == 0)
            {
                // Extract the two numbers from the match
                std::string num1Str = matchStr.substr(4, matchStr.find(',') - 4);
                std::string num2Str = matchStr.substr(matchStr.find(',') + 1, matchStr.size() - 1 - matchStr.find(',') - 1);

                if (enabled)
                {
                    result += std::stoull(num1Str) * std::stoull(num2Str);
                }
            }
            else if (matchStr == "do()")
            {
                enabled = true;
            }
            else if (matchStr == "don't()")
            {
                enabled = false;
            }
        }
    }
    return result;
}