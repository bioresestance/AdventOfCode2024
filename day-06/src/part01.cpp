/**
 * Day-6 - Part 01
 */
#include "include.hpp"
#include <utility>
#include <cstdint>
#include <vector>
#include <ranges>
#include <algorithm>
#include <unordered_set>

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


    GaurdPosition operator +(const std::pair<int8_t, int8_t>& rhs)
    {
        GaurdPosition newPos;
        newPos.x = x + rhs.first;
        newPos.y = y + rhs.second;
        return newPos;
    }

        GaurdPosition operator +(std::pair<int8_t, int8_t>& rhs)
    {
        GaurdPosition newPos;
        newPos.x = x + rhs.first;
        newPos.y = y + rhs.second;
        return newPos;
    }
};

namespace std {
    template <>
    struct hash<GaurdPosition> {
        std::size_t operator()(const GaurdPosition& pos) const noexcept {
            return std::hash<uint32_t>()(pos.x) ^ (std::hash<uint32_t>()(pos.y) << 1);
        }
    };

    template <>
    struct equal_to<GaurdPosition> {
        bool operator()(const GaurdPosition& lhs, const GaurdPosition& rhs) const noexcept {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
    };
}

bool checkMapBoundary(uint32_t map_width, uint32_t map_height, GaurdPosition& pos)
{
    return (( pos.x >= 0 and pos.x < map_width) and (pos.y >=0 and pos.y < map_height));
}




static constexpr const std::pair<int8_t, int8_t> direction_to_move[] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int64_t handlePart1(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;
    std::vector<std::vector<char>> map;
    Direction gaurd_dir = Direction::UP;
    GaurdPosition guard_pos;
    std::unordered_set<GaurdPosition> positions;


    // Convert the strings into char arrays.
    std::ranges::for_each(inputLines, [&](auto&& line){map.emplace_back(std::vector(line.begin(), line.end()));});



    // Find the coordinate of the gaurds starting position.
    for(auto [ rowIdx, row]: enumerate(map))
    {
        for(auto [colIdx, col]: enumerate(row))
        {
            if(col == '^')
            {
                guard_pos.x = colIdx;
                guard_pos.y = rowIdx;
            }
        }
    }

    // Add the guards starting position to the set.
    positions.emplace(guard_pos);
    // Replace the ^ char with a .
    map[guard_pos.y][guard_pos.x] = '.';


    while(true)
    {
        auto next_pos = guard_pos + direction_to_move[static_cast<uint8_t>(gaurd_dir)];

        // Check if the next position is on the map boundary
        if(!checkMapBoundary(map[0].size(), map.size(), next_pos))
        {
            break;
        }

        if(map[next_pos.y][next_pos.x] == '.')
        {
            guard_pos = next_pos;
            positions.emplace(guard_pos);
        }
        else
        {
            // Switch the gaurds direction
            switch(gaurd_dir)
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


    return positions.size();
}