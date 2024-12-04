/**
 * Day-4 - Part 02
 */
#include "include.hpp"
#include <stdexcept>

int64_t handlePart2(const std::vector<std::string> &inputLines)
{
    std::vector<std::vector<char>> letters;

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

    uint32_t word_count = 0;

    // Search through each row in the table
    for (uint32_t row = 0; row < letters.size(); row++)
    {
        // Search through each letter on the row
        for (uint32_t col = 0; col < letters[row].size(); col++)
        {
            // Check for the center of the "X", which is 'A'
            if (letters[row][col] == 'A')
            {
                bool x_found = false;
                // Check for all 4 possible combinations that can form an "X", if one is found, ignore the other directions.
                for (uint32_t direction = 0; direction < 4; direction++)
                {
                    try
                    {
                        if ((letters.at(row - 1).at(col + 1) == 'M') and (letters.at(row - 1).at(col - 1) == 'M') and (letters.at(row + 1).at(col - 1) == 'S') and (letters.at(row + 1).at(col + 1) == 'S'))
                        {
                            x_found = true;
                            break;
                        }
                        if ((letters.at(row - 1).at(col + 1) == 'M') and (letters.at(row - 1).at(col - 1) == 'S') and (letters.at(row + 1).at(col - 1) == 'S') and (letters.at(row + 1).at(col + 1) == 'M'))
                        {
                            x_found = true;
                            break;
                        }
                        if ((letters.at(row - 1).at(col + 1) == 'S') and (letters.at(row - 1).at(col - 1) == 'S') and (letters.at(row + 1).at(col - 1) == 'M') and (letters.at(row + 1).at(col + 1) == 'M'))
                        {
                            x_found = true;
                            break;
                        }
                        if ((letters.at(row - 1).at(col + 1) == 'S') and (letters.at(row - 1).at(col - 1) == 'M') and (letters.at(row + 1).at(col - 1) == 'M') and (letters.at(row + 1).at(col + 1) == 'S'))
                        {
                            x_found = true;
                            break;
                        }
                    }
                    catch (const std::out_of_range &e)
                    {
                        // "X" can't be formed since we are on the edge of the table.
                        break;
                    }
                }

                if (x_found)
                {
                    word_count++;
                    x_found = false;
                }
            }
        }
    }
    return word_count;
}