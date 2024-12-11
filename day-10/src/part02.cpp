/**
 * Day-10 - Part 01
 */
#include "include.hpp"
#include <vector>
#include <ranges>
#include <unordered_set>
#include "Utils.hpp"

void checkRoutes(std::vector<std::vector<uint8_t>> &map, uint8_t next_index, Coordinate coord_to_check, uint64_t &found)
{
    // Check that the coordinate is within the map boundary.
    if ((coord_to_check.x < 0) or (coord_to_check.x >= map[0].size()) or (coord_to_check.y < 0) or (coord_to_check.y >= map.size()))
    {
        return;
    }

    // If this coordinate is not equal to the index we are looking for, return.
    if (map[coord_to_check.y][coord_to_check.x] != next_index)
    {
        return;
    }

    // If this coordinate is equal to 9, increment the count.
    if (next_index == 9)
    {
        found++;
        return;
    }

    // Check all four directions.
    checkRoutes(map, next_index + 1, coord_to_check + Coordinate{0, -1}, found); // UP
    checkRoutes(map, next_index + 1, coord_to_check + Coordinate{-1, 0}, found); // LEFT
    checkRoutes(map, next_index + 1, coord_to_check + Coordinate{0, 1}, found);  // DOWN
    checkRoutes(map, next_index + 1, coord_to_check + Coordinate{1, 0}, found);  // RIGHT
}

int64_t handlePart2(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;

    std::vector<std::vector<uint8_t>> map;
    map.reserve(inputLines.size());

    for (const auto &line : inputLines)
    {
        std::vector<uint8_t> row;
        std::unordered_set<Coordinate> found;
        for (auto num : line)
        {
            row.emplace_back(num - '0');
        }
        map.emplace_back(std::move(row));
    }

    uint64_t total = 0;
    for (const auto [rowIdx, row] : map | enumerate)
    {
        for (const auto [colIdx, col] : row | enumerate)
        {
            if (col == 0)
            {
                checkRoutes(map, 0, Coordinate{static_cast<int>(colIdx), static_cast<int>(rowIdx)}, total);
            }
        }
    }

    return total;
}