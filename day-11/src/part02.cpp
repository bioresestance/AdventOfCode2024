/**
 * Day-11 - Part 02
 */
#include "include.hpp"
#include <vector>
#include <ranges>

namespace Part2
{

    inline std::pair<uint64_t, uint64_t> splitNumber(uint64_t number)
    {
        auto str = std::to_string(number);
        auto mid = str.size() / 2;
        return {std::stoull(str.substr(0, mid)), std::stoull(str.substr(mid))};
    }

    inline uint64_t getNumDigits(uint64_t number)
    {
        auto str = std::to_string(number);
        return str.size();
    }

    void blink(std::vector<uint64_t> &stones)
    {
        uint64_t idx = 0;

        while (idx < stones.size())
        {
            if (stones[idx] == 0)
            {
                stones[idx] = 1;
            }

            else if (getNumDigits(stones[idx]) % 2 == 0)
            {
                auto [first_half, second_half] = splitNumber(stones[idx]);
                stones[idx] = first_half;
                stones.insert(stones.begin() + idx + 1, second_half);
                idx++; // Skip the newly inserted element
            }
            else
            {
                stones[idx] *= 2024;
            }
            idx++;
        }
    }
} // namespace Part2

int64_t handlePart2(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;

    std::vector<uint64_t> stones;
    const uint64_t NUM_ITERS = 50;

    // Parse the initial string.
    for (const auto number : inputLines[0] | split(' ') | transform([](auto &&num) -> uint64_t
                                                                    { return std::atoll(num.data()); }))
    {
        stones.emplace_back(number);
    }

    for (uint64_t i = 0; i < NUM_ITERS; i++)
    {
        Part2::blink(stones);
    }

    return stones.size();
}