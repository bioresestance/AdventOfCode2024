/**
 * Day-16 - Part 02
 */
#include "include.hpp"

using namespace std::ranges::views;

enum class Direction
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
};

struct State
{
    Coordinate coord;
    Direction dir;
    int64_t cost;
    bool operator>(const State &other) const
    {
        return cost > other.cost;
    }
};

int64_t handlePart2(const std::vector<std::string> &inputLines)
{
    std::unordered_set<Coordinate> walls;
    std::unordered_set<Coordinate> shortest_paths_nodes;
    Coordinate start_loc;
    Coordinate end_loc;
    uint64_t score = 0;

    for (const auto [rowIdx, row] : inputLines | enumerate)
    {
        for (const auto [colIdx, col] : row | enumerate)
        {
            Coordinate c{colIdx, rowIdx};
            switch (col)
            {
            case '#':
                walls.emplace(c);
                break;
            case 'S':
                start_loc = c;
                break;
            case 'E':
                end_loc = c;
                break;
            default:
                break;
            }
        }
    }
}