/**
 * Day-7 - Part 01
 */
#include "include.hpp"
#include <vector>
#include <cstdint>
#include <utility>
#include <ranges>

bool checkCombinations(const std::vector<int64_t> &values, uint32_t index, int64_t current, int64_t result)
{
    if (index == values.size())
    {
        return current == result;
    }

    // Try addition
    if (checkCombinations(values, index + 1, current + values[index], result))
    {
        return true;
    }

    // Try multiplication
    if (checkCombinations(values, index + 1, current * values[index], result))
    {
        return true;
    }

    return false;
}

int64_t handlePart1(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;
    std::vector<std::pair<int64_t, std::vector<int64_t>>> num_lines;
    int64_t final_value = 0;

    // Parse the input lines and convert them into the pair.
    for (auto line : inputLines)
    {
        std::pair<int64_t, std::vector<int64_t>> line_values;
        auto split = line | std::ranges::views::split(':');

        auto it = split.begin();
        line_values.first = std::atol((*it).data());
        it++;

        for (auto num : *it | std::ranges::views::split(' '))
        {
            auto str = std::string(num.begin(), num.end());

            if (str.empty() or str == " ")
            {
                continue;
            }
            line_values.second.emplace_back(std::atol(str.data()));
        }

        num_lines.emplace_back(std::move(line_values));
    }

    for (auto [result, values] : num_lines)
    {
        if (checkCombinations(values, 1, values[0], result))
        {
            final_value += result;
        }
    }

    return final_value;
}