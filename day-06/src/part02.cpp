/**
 * Day-6 - Part 02
 */

#include "include.hpp"
#include <utility>
#include <cstdint>
#include <vector>
#include <ranges>
#include <algorithm>
#include <unordered_set>
#include <iostream>

namespace Part02
{

    static constexpr const std::pair<int8_t, int8_t> direction_to_move[] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    struct GaurdPosition
    {
        int32_t x;
        int32_t y;

        GaurdPosition operator+(const std::pair<int8_t, int8_t> &rhs)
        {
            GaurdPosition newPos;
            newPos.x = x + rhs.first;
            newPos.y = y + rhs.second;
            return newPos;
        }

        GaurdPosition operator+(std::pair<int8_t, int8_t> &rhs)
        {
            GaurdPosition newPos;
            newPos.x = x + rhs.first;
            newPos.y = y + rhs.second;
            return newPos;
        }
    };

    bool operator==(const GaurdPosition &lhs, const GaurdPosition &rhs)
    {
        return (lhs.x == rhs.x) and (lhs.y == rhs.y);
    }

    bool checkMapBoundary(uint32_t map_width, uint32_t map_height, GaurdPosition &pos)
    {
        return ((pos.x >= 0 and pos.x < map_width) and (pos.y >= 0 and pos.y < map_height));
    }

}

namespace std
{
    template <>
    struct hash<Part02::GaurdPosition>
    {
        std::size_t operator()(const Part02::GaurdPosition &pos) const noexcept
        {
            return std::hash<uint32_t>()(pos.x) ^ (std::hash<uint32_t>()(pos.y) << 1);
        }
    };

    template <>
    struct equal_to<Part02::GaurdPosition>
    {
        bool operator()(const Part02::GaurdPosition &lhs, const Part02::GaurdPosition &rhs) const noexcept
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
    };

    template <>
    struct hash<std::pair<Part02::GaurdPosition, Part02::Direction>>
    {
        std::size_t operator()(const std::pair<Part02::GaurdPosition, Part02::Direction> &p) const noexcept
        {
            return std::hash<Part02::GaurdPosition>()(p.first) ^ (std::hash<int>()(static_cast<int>(p.second)) << 1);
        }
    };
}

namespace Part02
{

    bool runSimulation(std::vector<std::vector<char>> &map, GaurdPosition starting_pos)
    {
        Direction gaurd_dir = Direction::UP;
        GaurdPosition guard_pos = starting_pos;
        std::unordered_set<std::pair<GaurdPosition, Direction>> positions;
        bool escaped = false;

        while (true)
        {
            auto next_pos = guard_pos + direction_to_move[static_cast<uint8_t>(gaurd_dir)];

            // Check if the next position is on the map boundary
            if (!checkMapBoundary(map[0].size(), map.size(), next_pos))
            {
                escaped = true;
                break;
            }

            if (map[next_pos.y][next_pos.x] == '.')
            {
                guard_pos = next_pos;

                auto new_pos = std::make_pair(guard_pos, gaurd_dir);
                if (std::ranges::find(positions, new_pos) != positions.end())
                {
                    // We are going to the same position in the same direction, we must be in a loop.
                    break;
                }

                positions.emplace(std::move(new_pos));
            }
            else
            {
                // Switch the gaurds direction
                switch (gaurd_dir)
                {
                case Direction::UP:
                    gaurd_dir = Direction::RIGHT;
                    break;
                case Direction::RIGHT:
                    gaurd_dir = Direction::DOWN;
                    break;
                case Direction::DOWN:
                    gaurd_dir = Direction::LEFT;
                    break;
                case Direction::LEFT:
                    gaurd_dir = Direction::UP;
                    break;
                }
            }
        }
        return escaped;
    }
} // namespace Part02

int64_t handlePart2(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;
    std::vector<std::vector<char>> map;
    Part02::GaurdPosition guard_pos;
    uint64_t loop_count = 0;

    // Convert the strings into char arrays.
    std::ranges::for_each(inputLines, [&](auto &&line)
                          { map.emplace_back(std::vector(line.begin(), line.end())); });

    // Find the coordinate of the gaurds starting position.
    for (auto [rowIdx, row] : enumerate(map))
    {
        for (auto [colIdx, col] : enumerate(row))
        {
            if (col == '^')
            {
                guard_pos.x = colIdx;
                guard_pos.y = rowIdx;
                // Replace the ^ char with a .
                map[guard_pos.y][guard_pos.x] = '.';
            }
        }
    }

    for (auto [rowIdx, row] : enumerate(map))
    {
        for (auto [colIdx, col] : enumerate(row))
        {
            // No need to replace it, since its already an obstacle.
            if (col == '#')
            {
                continue;
            }

            if (guard_pos.x == colIdx and guard_pos.y == rowIdx)
            {
                // Can't place an obstacle in the gaurds starting position.
                continue;
            }

            // Change it to be an obstacle.
            col = '#';
            if (!Part02::runSimulation(map, guard_pos))
            {
                loop_count++;
                std::cout << "Discovered loop at [" << colIdx << "," << rowIdx << "]" << std::endl;
            }
            // Change it back.
            col = '.';
        }
    }

    return loop_count;
}