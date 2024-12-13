/**
 * Day-12 - Part 02
 */
#include "include.hpp"
#include "Utils.hpp"
#include <unordered_map>
#include <ranges>
#include <vector>
#include <algorithm>
#include <unordered_set>

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

uint64_t countCorners(const std::vector<Coordinate> &group)
{
    uint64_t total_corners = 0;

    std::unordered_set<Coordinate> nodes{group.begin(), group.end()};

    for (const auto &node : nodes)
    {

        uint64_t corners = 0;
        // Get a list of all neighbors of this node.
        std::unordered_set<Coordinate> neighbors;
        for (const auto &dir : {
                 Coordinate::NORTH,
                 Coordinate::EAST,
                 Coordinate::SOUTH,
                 Coordinate::WEST,
                 Coordinate::NORTH_EAST,
                 Coordinate::NORTH_WEST,
                 Coordinate::SOUTH_EAST,
                 Coordinate::SOUTH_WEST})
        {
            if (nodes.contains(node + dir))
            {
                neighbors.emplace(dir);
            }
        }

        if (not neighbors.contains(Coordinate::WEST) and not neighbors.contains(Coordinate::NORTH))
        {
            corners += 1;
        }
        if (not neighbors.contains(Coordinate::WEST) and not neighbors.contains(Coordinate::SOUTH))
        {
            corners += 1;
        }
        if (not neighbors.contains(Coordinate::EAST) and not neighbors.contains(Coordinate::NORTH))
        {
            corners += 1;
        }
        if (not neighbors.contains(Coordinate::EAST) and not neighbors.contains(Coordinate::SOUTH))
        {
            corners += 1;
        }
        if (neighbors.contains(Coordinate::WEST) and neighbors.contains(Coordinate::NORTH) and not neighbors.contains(Coordinate::NORTH_WEST))
        {
            corners += 1;
        }
        if (neighbors.contains(Coordinate::EAST) and neighbors.contains(Coordinate::NORTH) and not neighbors.contains(Coordinate::NORTH_EAST))
        {
            corners += 1;
        }
        if (neighbors.contains(Coordinate::WEST) and neighbors.contains(Coordinate::SOUTH) and not neighbors.contains(Coordinate::SOUTH_WEST))
        {
            corners += 1;
        }
        if (neighbors.contains(Coordinate::EAST) and neighbors.contains(Coordinate::SOUTH) and not neighbors.contains(Coordinate::SOUTH_EAST))
        {
            corners += 1;
        }

        total_corners += corners;
    }

    return total_corners;
}

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

    // Only need to check the first 4 directions.
    std::ranges::for_each(directions, [&](auto &&dir)
                          { floodFill(map, group, letter, node + dir); });
}

int64_t handlePart2(const std::vector<std::string> &inputLines)
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
        // There are the same number of corners as sides.
        uint64_t corners = countCorners(group.coordinates);
        cost += area * corners;
    }

    return cost;
}