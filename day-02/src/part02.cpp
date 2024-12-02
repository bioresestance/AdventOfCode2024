/**
 * Day-2 - Part 02
 */
#include "include.hpp"
#include "Utils.hpp"

namespace Part2
{

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

        if (change == 0)
            dir = Direction::SAME;
        if (change > 0)
            dir = Direction::INC;
        if (change < 0)
            dir = Direction::DEC;
        return {change, dir};
    }

    bool isLineSafe(std::vector<uint32_t> &line)
    {
        constexpr uint32_t max_change = 3;
        Direction dir = Direction::NONE;
        bool isSafe = true;
        for (size_t i = 1; i < line.size(); i++)
        {
            auto [change, direction] = CheckSafety(line[i], line[i - 1]);

            if (direction == Direction::SAME or direction == Direction::NONE)
            {
                isSafe = false;
                break;
            }

            if (i == 1)
            {
                dir = direction;
            }

            if (std::abs(change) > max_change)
            {
                isSafe = false;
                break;
            }

            if (dir != direction)
            {
                isSafe = false;
                break;
            }
        }
        return isSafe;
    }

}
std::string handlePart2(const std::string_view input)
{
    auto lines = splitString(input, '\n');

    uint32_t safeLines = 0;

    for (const auto &line : lines)
    {
        if (line.empty())
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

        // First check if the list is safe as is.
        if (Part2::isLineSafe(intNumbers))
        {
            safeLines++;
            continue;
            ;
        }

        bool isSafe = false;
        uint32_t current_idx = 0;
        for (uint32_t index = 0; index < intNumbers.size(); index++)
        {
            // Create a new vector without the element at the current index
            std::vector<uint32_t> newList;
            newList.reserve(intNumbers.size() - 1); // Reserve space for efficiency
            for (uint32_t i = 0; i < intNumbers.size(); i++)
            {
                if (i != index)
                {
                    newList.push_back(intNumbers[i]);
                }
            }
            if (Part2::isLineSafe(newList))
            {
                isSafe = true;
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