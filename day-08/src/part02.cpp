/**
 * Day-8 - Part 02
 */
#include "include.hpp"
#include <map>
#include <vector>
#include <cstdint>
#include <unordered_set>
#include <ranges>

namespace Part2
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

        Coordinate operator+(const Coordinate &other) const
        {
            Coordinate new_val;
            new_val.x = this->x + other.x;
            new_val.y = this->y + other.y;
            return new_val;
        }
        Coordinate operator*(const uint32_t &scalar) const
        {
            Coordinate new_val;
            new_val.x = this->x * scalar;
            new_val.y = this->y * scalar;
            return new_val;
        }

        friend Coordinate operator*(const uint32_t &scalar, const Coordinate &coord)
        {
            return coord * scalar;
        }
    };

    bool inBounds(const uint16_t width, const uint16_t height, const Coordinate &point)
    {
        return (point.x >= 0 && point.x < width && point.y >= 0 && point.y < height);
    }

} // namespace Part2

namespace std
{
    template <>
    struct hash<Part2::Coordinate>
    {
        std::size_t operator()(const Part2::Coordinate &coord) const
        {
            return std::hash<int16_t>()(coord.x) ^ (std::hash<int16_t>()(coord.y) << 1);
        }
    };
}

int64_t handlePart2(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;
    std::map<char, std::vector<Part2::Coordinate>> antennas;
    std::unordered_set<Part2::Coordinate> antinodes;

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
        for (const auto &coords : antennas_coordinates.second)
        {
            antinodes.emplace(coords);
            for (const auto &other_coords : antennas_coordinates.second)
            {
                if (coords == other_coords)
                {
                    continue;
                }

                Part2::Coordinate diff = other_coords - coords;
                Part2::Coordinate antinode = coords - diff;
                while (inBounds(map_width, map_height, antinode))
                {
                    antinodes.emplace(antinode);
                    antinode = antinode - diff;
                }
            }
        }
    }

    return antinodes.size();
}