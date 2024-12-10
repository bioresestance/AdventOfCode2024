/**
 * Day-9 - Part 01
 */
#include "include.hpp"
#include <ranges>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <limits>

enum class Type
{
    FILE,
    SPACE
};

struct Memory
{
    Type type;
    uint64_t size;
    int64_t id = -1;
};

int64_t
handlePart2(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;
    std::vector<Memory> filesystem;
    std::vector<uint64_t> done_ids;

    int64_t curr_id = 0;
    for (const auto str_chunk : inputLines[0] | std::ranges::views::chunk(2))
    {
        uint64_t file_len = str_chunk[0] - '0';
        uint64_t free_len = str_chunk[1] - '0';

        filesystem.emplace_back(Type::FILE, file_len, curr_id++);
        if (str_chunk.size() == 2)
        {
            filesystem.emplace_back(Type::SPACE, free_len);
        }
    }

    // Now we loop through all of the ids to see if they can move down.
    for (int64_t max_id = curr_id - 1; max_id > 0; max_id--)
    {
        // Find the last item that is not free space.
        auto end_item_itr = std::ranges::find_if(filesystem | reverse, [&](auto &&item)
                                                 { return (item.type == Type::FILE) and (item.id == max_id); });
        auto &end_item = *end_item_itr;
        // Find the first free space that can fit the end item.
        auto free_item_itr = std::ranges::find_if(filesystem, [&](auto &&item)
                                                  { return (item.type == Type::SPACE) and (item.size >= end_item.size); });

        // Couldn't find a free spot, move to the next item
        if (free_item_itr == filesystem.end())
        {
            continue;
        }
        auto &free_item = *free_item_itr;

        auto free_idx = std::ranges::distance(filesystem.begin(), free_item_itr);
        auto end_idx = std::ranges::distance(filesystem.begin(), end_item_itr.base());

        if (free_idx >= end_idx)
        {
            continue;
        }

        auto size_diff = free_item.size - end_item.size;
        // If they are the same size, we can simply swap them.
        if (size_diff == 0)
        {
            std::swap(end_item, free_item);
            continue;
        }
        // Different sizes
        else
        {
            free_item.size = end_item.size;
            free_item.id = end_item.id;
            free_item.type = Type::FILE;

            end_item.type = Type::SPACE;
            end_item.id = -1;

            filesystem.insert(filesystem.begin() + free_idx + 1, {Type::SPACE, size_diff});
        }
    }
    uint64_t result = 0LL;
    for (uint64_t curr_idx = 0; const auto &memory : filesystem)
    {
        for (uint64_t i = 0; i < memory.size; i++, curr_idx++)
        {
            if (memory.type == Type::FILE)
            {
                result += memory.id * curr_idx;
            }
        }
    }

    return result;
}