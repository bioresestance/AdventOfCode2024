/**
 * Day-19 - Part 01
 */
#include "include.hpp"

using namespace std::ranges::views;

int64_t handlePart1(const std::vector<std::string> &inputLines) 
{

    std::vector<std::string> rules;
    std::regex delimiter("[, ]+");

    for (std::sregex_token_iterator it(inputLines[0].begin(), inputLines[0].end(), delimiter, -1); it != std::sregex_token_iterator(); ++it) 
    {
        rules.push_back(*it);
    }

     // sort by biggest first, then alphabetical if equal length.
    auto comparator = [](const std::string &a, const std::string &b) {
        if (a.length() == b.length()) {
            return a > b;
        }
        return a.length() > b.length();
    };

    // Sort the rules vector
    std::ranges::sort(rules, comparator);



    uint64_t num = 0;
    for(const auto &line: inputLines | drop(2))
    {

    }


    return 0;
}