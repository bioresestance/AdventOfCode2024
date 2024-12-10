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

int64_t handlePart1(const std::vector<std::string> &inputLines)
{

    std::vector<uint64_t> filesystem;
    const auto EMPTY = std::numeric_limits<uint64_t>::max();

    for (uint64_t curr_id = 0; const auto str_chunk : inputLines[0] | std::ranges::views::chunk(2))
    {
        uint64_t file_len = str_chunk[0] - '0';
        uint64_t free_len = 0;
        if (str_chunk[1] >= '0' and str_chunk[1] <= '9')
        {
            free_len = str_chunk[1] - '0';
        }

        filesystem.insert(filesystem.end(), file_len, curr_id++);
        if (free_len > 0)
        {
            filesystem.insert(filesystem.end(), free_len, EMPTY);
        }
    }

    for (auto [backIdx, back_item] : filesystem | std::ranges::views::enumerate | std::ranges::views::reverse)
    {

        if (back_item == EMPTY)
        {
            continue;
        }

        auto free_item = std::ranges::find_if(filesystem, [](uint64_t item)
                                              { return (item == EMPTY); });
        if (free_item == filesystem.end())
        {
            break;
        }

        auto freeIdx = std::distance(filesystem.begin(), free_item);

        if (freeIdx >= backIdx)
        {
            break;
        }

        std::swap(filesystem[freeIdx], filesystem[backIdx]);
    }

    auto it = filesystem | std::ranges::views::enumerate;

    uint64_t result = std::transform_reduce(it.begin(), it.end(),
                                            0LL,
                                            std::plus<>(),
                                            [](auto &&pair) -> uint64_t
                                            {
                                                auto [index, value] = pair;
                                                if (value == EMPTY)
                                                {
                                                    return 0LL;
                                                }
                                                return value * index;
                                            });

    return result;
}