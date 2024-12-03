/**
 * Day-2 - Part 01
 */
#include "include.hpp"
#include "Utils.hpp"
#include <vector>
#include <utility>
#include <tabulate/table.hpp>

enum class Direction
{
    NONE,
    SAME,
    INC,
    DEC
};

std::pair<int32_t, Direction> CheckSafety(uint32_t num1, uint32_t num2)
{
    int change = num1 - num2;
    Direction dir = Direction::NONE;

    if(change == 0) dir = Direction::SAME;
    if(change > 0)  dir = Direction::INC;
    if(change < 0)  dir = Direction::DEC;
    return {change, dir};
}


std::string handlePart1(const std::string_view input)
{
    auto lines = splitString(input, '\n');

    uint32_t safeLines = 0;
    constexpr uint32_t max_change = 3;
    for (const auto &line : lines)
    {
        if(line.empty())
        {
            continue;
        }


        // Split each line into a list of numbers.
        auto numbers = splitString(line, ' ');
        std::vector<uint32_t> intNumbers;
        for (const auto &number : numbers)
        {
            intNumbers.push_back(std::stoi(number));
        }

        // Check to see if the number is changing by more than the max_change allowed.
        bool isSafe = true;
        Direction dir = Direction::NONE;
        for (size_t i = 1; i < intNumbers.size(); i++)
        {
            auto [change, direction] = CheckSafety(intNumbers[i], intNumbers[i - 1]);

            if( direction == Direction::SAME or direction == Direction::NONE)
            {
                isSafe = false;
                break;
            }

            if( i == 1) 
            {
                dir = direction;
            }

            if( std::abs(change) > max_change )
            {
                isSafe = false;
                break;
            }


            if( dir != direction)
            {
                isSafe = false;
                break;
            }

        }

        if (isSafe)
        {
            safeLines++;
        }
    }
    return std::to_string(safeLines);
}