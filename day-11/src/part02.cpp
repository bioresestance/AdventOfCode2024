/**
 * Day-11 - Part 02
 */
#include "include.hpp"
#include <vector>
#include <ranges>
#include <unordered_map>

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

    void blink(std::unordered_map<uint64_t, uint64_t> &stones)
    {
        static std::unordered_map<uint64_t, std::pair<int64_t, int64_t>> cache;
        std::unordered_map<uint64_t, uint64_t> new_stones;

        for (const auto &[number, count] : stones)
        {
            if (cache.find(number) != cache.end())
            {
                auto [first_half, second_half] = cache[number];
                new_stones[first_half] += count;
                new_stones[second_half] += count;
            }
            else
            {
                if (number == 0)
                {
                    new_stones[1] += count;
                }
                else if (getNumDigits(number) % 2 == 0)
                {
                    auto [first_half, second_half] = splitNumber(number);
                    new_stones[first_half] += count;
                    new_stones[second_half] += count;
                    cache[number] = {first_half, second_half};
                }
                else
                {
                    new_stones[number * 2024] += count;
                }
            }
        }

        stones = std::move(new_stones);
    }

} // namespace Part2

int64_t handlePart2(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;

    // std::vector<uint64_t> stones;
    std::unordered_map<uint64_t, uint64_t> stones;

    const uint64_t NUM_ITERS = 75;

    // Parse the initial string.
    for (const auto number : inputLines[0] | split(' ') | transform([](auto &&num) -> uint64_t
                                                                    { return std::atoll(num.data()); }))
    {
        stones[number]++;
    }

    for (uint64_t i = 0; i < NUM_ITERS; i++)
    {
        Part2::blink(stones);
    }

    uint64_t total = 0;
    for (const auto &[num, count] : stones)
    {
        total += count;
    }

    return total;
}