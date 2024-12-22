/**
 * Day-19 - Part 01
 */
#include "include.hpp"

using namespace std::ranges::views;


static bool canFormLine(const std::string &line, const std::vector<std::string> &rules, std::unordered_map<std::string, bool> &cache) 
{
    if (line.empty()) {
        return true;
    }

    if (cache.find(line) != cache.end()) {
        return cache[line];
    }

    for (const auto &rule : rules) {
        size_t pos = line.find(rule);
        while (pos != std::string::npos) {
            std::string newLine = line;
            newLine.erase(pos, rule.size());
            if (canFormLine(newLine, rules, cache)) {
                cache[line] = true;
                return true;
            }
            pos = line.find(rule, pos + 1);
        }
    }

    cache[line] = false;
    return false;
}



int64_t handlePart1(const std::vector<std::string> &inputLines) 
{

    // Parse the rules on line 1.
    std::vector<std::string> rules;
    std::regex delimiter("[, ]+");
    for (std::sregex_token_iterator it(inputLines[0].begin(), inputLines[0].end(), delimiter, -1); it != std::sregex_token_iterator(); ++it) 
    {
        rules.push_back(*it);
    }


    std::unordered_map<std::string, bool> cache;
    uint64_t num = 0;
    for(const auto &line: inputLines | drop(2))
    {
        if (canFormLine(line, rules, cache)) {
            num++;
        }
    }

    return num;
}