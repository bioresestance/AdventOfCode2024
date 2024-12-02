/**
 * Day-1 - Part 01
 */
#include "include.hpp"
#include <string_view>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>

std::string handlePart1(const std::string_view input) {
    
    // split the input by lines
    std::vector<std::string> lines;
    for(const auto line: input | std::views::split('\n') )
    {
        lines.emplace_back(line.begin(), line.end());
    }

    std::vector<uint32_t> leftList;
    std::vector<uint32_t> rightList;

    for(const auto& line: lines)
    {
         auto numbers = line | std::views::split(' ') 
                            | std::views::filter([](auto part) { return !part.empty(); })
                            | std::views::transform([](auto part) { return std::stoi(std::string(part.begin(), part.end())); });
        auto it = numbers.begin();
        if (it != numbers.end()) {
            leftList.push_back(*it);
            ++it;
        }
        if (it != numbers.end()) {
            rightList.push_back(*it);
        }
    }

    std::ranges::sort(leftList);
    std::ranges::sort(rightList);

    uint32_t sum = 0;
    for(uint32_t i = 0; i < leftList.size(); i++)
    {
        sum += std::abs(static_cast<int>(leftList[i] - rightList[i]));
    }

    return std::to_string(sum);
}