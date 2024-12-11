#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <ranges>

inline std::vector<std::string> splitString(const std::string_view input, const char delimiter)
{
    std::vector<std::string> result;
    for (const auto line : input | std::views::split(delimiter))
    {
        result.emplace_back(line.begin(), line.end());
    }
    return result;
}

struct Coordinate
{
    int64_t x, y;

    Coordinate operator+(const Coordinate &other)
    {
        Coordinate res;
        res.x = x + other.x;
        res.y = y + other.y;
        return res;
    }

    bool operator==(const Coordinate &other) const
    {
        return x == other.x && y == other.y;
    }
};

namespace std
{
    template <>
    struct hash<Coordinate>
    {
        std::size_t operator()(const Coordinate &coord) const
        {
            return std::hash<int64_t>()(coord.x) ^ (std::hash<int64_t>()(coord.y) << 1);
        }
    };
}