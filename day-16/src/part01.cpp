/**
 * Day-16 - Part 01
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
    Coordinate position;
    Direction direction;
    uint64_t cost;

    bool operator>(const State &other) const
    {
        return cost > other.cost;
    }
};

int64_t handlePart1(const std::vector<std::string> &inputLines)
{
    std::unordered_set<Coordinate> walls;
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

    std::priority_queue<State, std::vector<State>, std::greater<>> pq;
    std::unordered_map<Coordinate, uint64_t> cost_so_far;
    pq.push({start_loc, Direction::EAST, 0});
    cost_so_far[start_loc] = 0;

    std::array<std::pair<Direction, Coordinate>, 4> directions = {
        std::make_pair(Direction::NORTH, Coordinate::NORTH),
        std::make_pair(Direction::SOUTH, Coordinate::SOUTH),
        std::make_pair(Direction::EAST, Coordinate::EAST),
        std::make_pair(Direction::WEST, Coordinate::WEST)};

    while (!pq.empty())
    {
        State current = pq.top();
        pq.pop();

        if (current.position == end_loc)
        {
            return current.cost;
        }

        for (const auto &[new_direction, move] : directions)
        {
            Coordinate new_position = current.position + move;
            uint64_t new_cost = current.cost + 1;
            if (new_direction != current.direction)
            {
                new_cost += 1000;
            }

            if (walls.find(new_position) == walls.end() && (cost_so_far.find(new_position) == cost_so_far.end() || new_cost < cost_so_far[new_position]))
            {
                cost_so_far[new_position] = new_cost;
                pq.push({new_position, new_direction, new_cost});
            }
        }
    }

    return -1; // If no path is found
}