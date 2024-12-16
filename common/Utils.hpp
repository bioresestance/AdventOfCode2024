#pragma once

#include <bits/stdc++.h>

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

    Coordinate operator+(const Coordinate &other) const
    {
        Coordinate res;
        res.x = x + other.x;
        res.y = y + other.y;
        return res;
    }

    Coordinate operator+(Coordinate &other) const
    {
        Coordinate res;
        res.x = x + other.x;
        res.y = y + other.y;
        return res;
    }
    Coordinate operator-(const Coordinate &other) const
    {
        Coordinate res;
        res.x = x - other.x;
        res.y = y - other.y;
        return res;
    }

    Coordinate operator-(Coordinate &other) const
    {
        Coordinate res;
        res.x = x - other.x;
        res.y = y - other.y;
        return res;
    }

    bool operator==(const Coordinate &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator<(const Coordinate &other) const
    {
        return x < other.x && y < other.y;
    }

    bool operator>(const Coordinate &other) const
    {
        return x > other.x && y > other.y;
    }
    bool operator<(Coordinate &other) const
    {
        return x < other.x && y < other.y;
    }

    bool operator>(Coordinate &other) const
    {
        return x > other.x && y > other.y;
    }

    bool operator<=(const Coordinate &other) const
    {
        return x <= other.x && y <= other.y;
    }

    bool operator>=(const Coordinate &other) const
    {
        return x >= other.x && y >= other.y;
    }

    bool operator<=(Coordinate &other) const
    {
        return x <= other.x && y <= other.y;
    }

    bool operator>=(Coordinate &other) const
    {
        return x >= other.x && y >= other.y;
    }

    static const Coordinate NORTH;
    static const Coordinate SOUTH;
    static const Coordinate EAST;
    static const Coordinate WEST;
    static const Coordinate NORTH_EAST;
    static const Coordinate NORTH_WEST;
    static const Coordinate SOUTH_EAST;
    static const Coordinate SOUTH_WEST;
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

template <typename T>
static bool inBoundary(std::vector<std::vector<T>> &map, Coordinate coord)
{
    return coord.x >= 0 && coord.x < map[0].size() && coord.y >= 0 && coord.y < map.size();
}