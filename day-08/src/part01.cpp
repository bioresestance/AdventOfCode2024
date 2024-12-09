/**
 * Day-8 - Part 01
 */
#include "include.hpp"
#include <map>
#include <vector>
#include <cstdint>
#include <unordered_set>
#include <ranges>

namespace Part1
{

    struct Coordinate
    {
        int16_t x;
        int16_t y;

        bool operator==(const Coordinate &other) const
        {
            return x == other.x && y == other.y;
        }

        Coordinate operator-(const Coordinate &other) const
        {
            Coordinate new_val;
            new_val.x = this->x - other.x;
            new_val.y = this->y - other.y;
            return new_val;
        }
    };

    bool inBounds(const uint16_t width, const uint16_t height, const Coordinate &point)
    {
        return (point.x >= 0 && point.x < width && point.y >= 0 && point.y < height);
    }

} // namespace Part1

namespace std
{
    template <>
    struct hash<Part1::Coordinate>
    {
        std::size_t operator()(const Part1::Coordinate &coord) const
        {
            return std::hash<int16_t>()(coord.x) ^ (std::hash<int16_t>()(coord.y) << 1);
        }
    };
}

int64_t handlePart1(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;
    std::map<char, std::vector<Part1::Coordinate>> antennas;
    std::unordered_set<Part1::Coordinate> antinodes;

    for (const auto [yIdx, line] : enumerate(inputLines))
    {
        for (const auto [xIdx, in] : enumerate(line))
        {
            if (in == '.')
            {
                continue;
            }

            antennas[in].emplace_back(xIdx, yIdx);
        }
    }

    uint16_t map_width = inputLines[0].size();
    uint16_t map_height = inputLines.size();

    for (const auto &antennas_coordinates : antennas)
    {
        for (const auto &[idx, coords] : enumerate(antennas_coordinates.second))
        {
            // Make a copy, and remove the current element, so we dont go over it.
            auto copy = antennas_coordinates.second;
            copy.erase(copy.begin() + idx);

            for (const auto &other_coords : copy)
            {
                Part1::Coordinate diff = other_coords - coords;
                Part1::Coordinate antinode = coords - diff;
                if (not inBounds(map_width, map_height, antinode))
                {
                    continue;
                }
                antinodes.emplace(antinode);
            }
        }
    }

    return antinodes.size();
}