#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <ranges>

inline std::vector<std::string> splitString(const std::string_view input, const char delimiter)
{
    std::vector<std::string> result;
    for(const auto line: input | std::views::split(delimiter) )
    {
        result.emplace_back(line.begin(), line.end());
    }
    return result;
}