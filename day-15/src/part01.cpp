/**
 * Day-15 - Part 01
 */
#include "include.hpp"
#include "Utils.hpp"
#include <unordered_map>
#include <ranges>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std::ranges::views;

enum class BlockType : uint8_t
{
    WALL,
    ROBOT,
    BOX,
    SPACE
};

static void moveBlock(Coordinate cur_pos, Coordinate move_dir, std::unordered_map<Coordinate, BlockType> &blocks)
{

    Coordinate next_pos = cur_pos + move_dir;
    BlockType next_type = blocks[cur_pos + move_dir];

    switch (next_type)
    {
    case BlockType::SPACE:
        std::swap(blocks[cur_pos], blocks[next_pos]);
        break;
    case BlockType::WALL:
    case BlockType::ROBOT:
        // Can't move here, ignore.
        break;
    case BlockType::BOX:
    {
        Coordinate box_next_pos = next_pos + move_dir;
        BlockType box_next_type = blocks[box_next_pos];
        if (box_next_type == BlockType::SPACE)
        {
            std::swap(blocks[next_pos], blocks[box_next_pos]);
            std::swap(blocks[cur_pos], blocks[next_pos]);
        }
        else if (box_next_type == BlockType::BOX)
        {
            moveBlock(next_pos, move_dir, blocks);
            if (blocks[next_pos] == BlockType::SPACE)
            {
                std::swap(blocks[cur_pos], blocks[next_pos]);
            }
        }
        break;
    }
    default:
        break;
    }
}
void printMap(const std::unordered_map<Coordinate, BlockType> &blocks)
{
    int min_x = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    int min_y = std::numeric_limits<int>::max();
    int max_y = std::numeric_limits<int>::min();

    for (const auto &[coord, type] : blocks)
    {
        if (coord.x < min_x)
            min_x = coord.x;
        if (coord.x > max_x)
            max_x = coord.x;
        if (coord.y < min_y)
            min_y = coord.y;
        if (coord.y > max_y)
            max_y = coord.y;
    }

    for (int y = min_y; y <= max_y; ++y)
    {
        for (int x = min_x; x <= max_x; ++x)
        {
            Coordinate coord{x, y};
            if (blocks.find(coord) != blocks.end())
            {
                switch (blocks.at(coord))
                {
                case BlockType::WALL:
                    std::cout << '#';
                    break;
                case BlockType::BOX:
                    std::cout << 'O';
                    break;
                case BlockType::SPACE:
                    std::cout << '.';
                    break;
                case BlockType::ROBOT:
                    std::cout << '@';
                    break;
                }
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
}

int64_t handlePart1(const std::vector<std::string> &inputLines)
{

    std::unordered_map<Coordinate, BlockType> blocks;
    std::vector<Coordinate> directions;

    // Parse the inputs into directions and break the map up into a hashmap of coordinates.
    auto map_view = inputLines |
                    take_while([](auto &&line)
                               { return not line.empty(); });
    auto cmd_view = inputLines |
                    drop_while([](auto &&line)
                               { return not line.empty(); }) |
                    join;

    std::ranges::for_each(cmd_view, [&](auto &&cmd)
                          {
                              switch (cmd)
                              {
                              case '<':
                                  directions.emplace_back(Coordinate::WEST);
                                  break;
                              case '>':
                                  directions.emplace_back(Coordinate::EAST);
                                  break;
                              case '^':
                                  directions.emplace_back(Coordinate::NORTH);
                                  break;
                              case 'v':
                                  directions.emplace_back(Coordinate::SOUTH);
                                  break;
                              default:
                                  std::cout << "Unexpected char: " << cmd << std::endl;
                                  break;
                              } });

    for (const auto [rowIdx, line] : map_view | enumerate)
    {
        for (const auto [colIdx, block] : line | enumerate)
        {
            Coordinate c{colIdx, rowIdx};
            BlockType type;
            switch (block)
            {
            case '#':
                type = BlockType::WALL;
                break;
            case 'O':
                type = BlockType::BOX;
                break;
            case '.':
                type = BlockType::SPACE;
                break;
            case '@':
                type = BlockType::ROBOT;
                break;
            default:
                std::cout << "Unexpected char: " << block << std::endl;
                break;
            }
            blocks[c] = type;
        }
    }

    for (const auto cmd : directions)
    {
        auto robot_pos = std::ranges::find_if(blocks, [](const auto &block)
                                              { return block.second == BlockType::ROBOT; });
        moveBlock(robot_pos->first, cmd, blocks);
    }

    // printMap(blocks);

    uint64_t sum = 0;
    std::ranges::for_each(blocks | filter([](auto &&block)
                                          { return block.second == BlockType::BOX; }),
                          [&](auto &&box)
                          {
                              sum += (box.first.y * 100) + box.first.x;
                          });

    return sum;
}