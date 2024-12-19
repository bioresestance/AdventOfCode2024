/**
 * Day-18 - Part 01
 */
#include "include.hpp"

using namespace std::ranges::views;

int64_t handlePart1(const std::vector<std::string> &inputLines, uint32_t grid_size, uint32_t bytes)
{
    const Coordinate start{0, 0};
    const Coordinate end{grid_size - 1, grid_size - 1};
    const auto map_width = grid_size;
    const auto map_height = grid_size;
    std::unordered_set<Coordinate> blocks;

    for (const auto &line : inputLines | take(bytes))
    {
        auto line_view = line | std::views::split(',');
        Coordinate c;
        auto it = line_view.begin();
        c.x = std::stol(std::string(std::string_view(*it)));
        ++it;
        c.y = std::stol(std::string(std::string_view(*it)));
        blocks.emplace(std::move(c));
    }

    std::queue<std::pair<Coordinate, int>> q;
    std::unordered_set<Coordinate> visited;
    q.push({start, 0});
    visited.insert(start);

    const std::array<Coordinate, 4> directions{Coordinate::EAST, Coordinate::NORTH, Coordinate::WEST, Coordinate::SOUTH};

    while (!q.empty())
    {
        auto [current, steps] = q.front();
        q.pop();

        if (current == end)
        {
            return steps;
        }

        for (const auto &dir : directions)
        {
            Coordinate next = current + dir;

            if (!inBoundary(next, map_width, map_width))
            {
                continue;
            }

            if (blocks.contains(next))
            {
                continue;
            }

            if (visited.contains(next))
            {
                continue;
            }
            q.push({next, steps + 1});
            visited.emplace(next);
        }
    }

    return -1; // Return -1 if no path is found
}