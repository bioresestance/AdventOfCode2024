/**
 * Day-12 - Part 01
 */
#include "include.hpp"
#include "Utils.hpp"
#include <unordered_map>
#include <ranges>
#include <vector>
#include <algorithm>

using namespace std::ranges::views;

struct Group
{
    char letter;
    std::vector<Coordinate> coordinates;
};

static const std::array<Coordinate, 4> directions = {
    Coordinate::NORTH,
    Coordinate::EAST,
    Coordinate::SOUTH,
    Coordinate::WEST,
};

static void floodFill(std::vector<std::vector<char>> &map, std::vector<Coordinate> &group, char letter, Coordinate node)
{
    if (not inBoundary(map, node))
    {
        return;
    }
    if (map[node.y][node.x] != letter)
    {
        return;
    }

    group.emplace_back(node);
    map[node.y][node.x] = '.';

    std::ranges::for_each(directions, [&](auto &&dir)
                          { floodFill(map, group, letter, node + dir); });
}

static void calcPerimeter(Group &group, uint64_t &count, Coordinate)
{
}

int64_t handlePart1(const std::vector<std::string> &inputLines)
{
    std::vector<Group> groups;
    std::vector<std::vector<char>> map;

    // Parse the letters into groups.
    for (const auto &line : inputLines)
    {
        std::vector<char> letters;
        for (const auto letter : line)
        {
            letters.emplace_back(letter);
        }
        map.emplace_back(std::move(letters));
    }

    // Split the map into groups.
    for (const auto [yIdx, row] : map | enumerate)
    {
        for (const auto [xIdx, letter] : row | enumerate)
        {
            if (letter == '.')
            {
                continue;
            }
            std::vector<Coordinate> group;
            char saved_letter = letter;
            floodFill(map, group, letter, Coordinate{xIdx, yIdx});
            if (group.size() > 0)
            {
                groups.emplace_back(saved_letter, std::move(group));
            }
        }
    }

    uint64_t cost = 0;
    for (const auto group : groups)
    {
        uint64_t area = group.coordinates.size();
        uint64_t perimeter = 0;
        for (const auto coord : group.coordinates)
        {
            uint8_t fences = 4;
            std::ranges::for_each(directions, [&](auto &&dir)
                                  { 
            if (std::ranges::find(group.coordinates, coord + dir) != group.coordinates.end())
            {
                fences--;
            } });

            perimeter += fences;
        }
        cost += area * perimeter;
    }

    return cost;
}