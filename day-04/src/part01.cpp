/**
 * Day-4 - Part 01
 */
#include "include.hpp"
#include <stdexcept>

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};

int64_t handlePart1(const std::vector<std::string> &inputLines)
{
    std::vector<std::vector<char>> letters;
    const auto WORD = "XMAS";

    // Convert the input lines into a 2d vector of chars
    for (const std::string &line : inputLines)
    {
        std::vector<char> row;
        for (const char &c : line)
        {
            row.push_back(c);
        }
        letters.push_back(row);
    }

    uint32_t found_count = 0;

    // Search each row
    for (uint32_t row = 0; row < letters.size(); row++)
    {
        // Search each column
        for (uint32_t col = 0; col < letters[0].size(); col++)
        {

            // Check if the current letter is the start of the word
            if (letters[row][col] == WORD[0])
            {

                // Check all directions to see if it forms the word
                for (uint32_t wordDirection = Direction::UP; wordDirection <= Direction::DOWN_RIGHT; wordDirection++)
                {
                    try
                    {
                        switch (wordDirection)
                        {
                        case Direction::UP:
                            if (letters.at(row - 1).at(col) == WORD[1] && letters.at(row - 2).at(col) == WORD[2] && letters.at(row - 3).at(col) == WORD[3])
                                found_count++;
                            break;
                        case Direction::DOWN:
                            if (letters.at(row + 1).at(col) == WORD[1] && letters.at(row + 2).at(col) == WORD[2] && letters.at(row + 3).at(col) == WORD[3])
                                found_count++;
                            break;
                        case Direction::LEFT:
                            if (letters.at(row).at(col - 1) == WORD[1] && letters.at(row).at(col - 2) == WORD[2] && letters.at(row).at(col - 3) == WORD[3])
                                found_count++;
                            break;
                        case Direction::RIGHT:
                            if (letters.at(row).at(col + 1) == WORD[1] && letters.at(row).at(col + 2) == WORD[2] && letters.at(row).at(col + 3) == WORD[3])
                                found_count++;
                            break;
                        case Direction::UP_LEFT:
                            if (letters.at(row - 1).at(col - 1) == WORD[1] && letters.at(row - 2).at(col - 2) == WORD[2] && letters.at(row - 3).at(col - 3) == WORD[3])
                                found_count++;
                            break;
                        case Direction::UP_RIGHT:
                            if (letters.at(row - 1).at(col + 1) == WORD[1] && letters.at(row - 2).at(col + 2) == WORD[2] && letters.at(row - 3).at(col + 3) == WORD[3])
                                found_count++;
                            break;
                        case Direction::DOWN_LEFT:
                            if (letters.at(row + 1).at(col - 1) == WORD[1] && letters.at(row + 2).at(col - 2) == WORD[2] && letters.at(row + 3).at(col - 3) == WORD[3])
                                found_count++;
                            break;
                        case Direction::DOWN_RIGHT:
                            if (letters.at(row + 1).at(col + 1) == WORD[1] && letters.at(row + 2).at(col + 2) == WORD[2] && letters.at(row + 3).at(col + 3) == WORD[3])
                                found_count++;
                            break;

                        default:
                            break;
                        }
                    }
                    catch (const std::out_of_range &d)
                    {
                        // Not an error, means we hit the wall of the puzzle. Move to next direction.
                        continue;
                    }
                }
            }
        }
    }
    return found_count;
}