/**
 * Day-1 - Part 02
 */
#include "include.hpp"
#include <string_view>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
#include <cstdint>

std::string handlePart2(const std::string_view input)
{
    // split the input by lines
    std::vector<std::string> lines;
    for (const auto line : input | std::views::split('\n'))
    {
        lines.emplace_back(line.begin(), line.end());
    }

    std::vector<uint32_t> leftList;
    std::vector<uint32_t> rightList;

    for (const auto &line : lines)
    {
        auto numbers = line | std::views::split(' ') | std::views::filter([](auto part)
                                                                          { return !part.empty(); }) |
                       std::views::transform([](auto part)
                                             { return std::stoi(std::string(part.begin(), part.end())); });
        auto it = numbers.begin();
        if (it != numbers.end())
        {
            leftList.push_back(*it);
            ++it;
        }
        if (it != numbers.end())
        {
            rightList.push_back(*it);
        }
    }

    uint32_t sum = 0;
    for (const auto leftNum : leftList)
    {
        uint32_t count = std::ranges::count(rightList, leftNum);
        sum += count * leftNum;
    }

    return std::to_string(sum);
}