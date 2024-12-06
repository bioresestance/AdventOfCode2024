/**
 * Day-5 - Part 01
 */
#include "include.hpp"
#include <ranges>
#include <cstdint>

std::vector<std::pair<uint32_t, uint32_t>> getRules(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;
    std::vector<std::pair<uint32_t, uint32_t>> rules;
    // Loop through the input line until we hit the empty line, and parse all the rules
    for (const auto &line : inputLines)
    {
        // We hit the divider between the rules and the data
        if (line.empty())
        {
            break;
        }

        auto splitView = line | split('|') | transform([](auto &&tok) -> uint32_t
                                                       { return std::atoi(std::string(tok.begin(), tok.end()).c_str()); });

        auto it = splitView.begin();
        uint32_t first = *it;
        ++it;
        uint32_t second = *it;

        rules.emplace_back(first, second);
    }
    return rules;
}

std::vector<std::vector<uint32_t>> getUpdates(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;

    std::vector<std::vector<uint32_t>> updates;
    bool rulesSkipped = false;

    for (const auto &line : inputLines)
    {

        if (rulesSkipped and line.empty())
        {
            continue;
        }

        if (line.empty())
        {
            rulesSkipped = true;
            continue;
        }
        else if (not rulesSkipped)
        {
            continue;
        }

        std::vector<uint32_t> currLine;
        for (const auto number : line | split(',') | transform([](auto &&tok) -> uint32_t
                                                               { return std::atoi(std::string(tok.begin(), tok.end()).c_str()); }))
        {
            currLine.emplace_back(number);
        }
        updates.emplace_back(std::move(currLine));
    }
    return updates;
}

std::vector<uint32_t> getNumLocations(std::vector<uint32_t> numbers, uint32_t numToFind)
{
    std::vector<uint32_t> locations;

    for (uint32_t idx = 0; idx < numbers.size(); idx++)
    {
        if (numToFind == numbers[idx])
        {
            locations.emplace_back(idx);
        }
    }
    return locations;
}

int64_t handlePart1(const std::vector<std::string> &inputLines)
{
    using namespace std::ranges::views;
    auto rules = getRules(inputLines);
    auto updates = getUpdates(inputLines);

    std::vector<std::vector<uint32_t>> validUpdates;
    // Loop through each update line.
    for (const auto &[updateIdx, update] : enumerate(updates))
    {
        // For each number in the line, we want to check if it satisfies the rules.
        bool updateValid = true;
        for (const auto [idx, num] : enumerate(update))
        {
            // Get all the rules that apply to the current number we are checking.
            for (const auto &rule : rules | filter([num](auto &&r)
                                                   { return (r.first == num); }))
            {
                // Get all the locations of the right-hand number of the rule
                auto rhLocations = getNumLocations(update, rule.second);
                for (const auto rhLoc : rhLocations)
                {
                    // Check all of the locations of the rh side of the pair to make sure they appear after the lh side.
                    if (rhLoc < idx)
                    {
                        updateValid = false;
                        break;
                    }
                }
                if (not updateValid)
                {
                    break;
                }
            }
            if (not updateValid)
            {
                break;
            }
        }

        if (updateValid)
        {
            validUpdates.emplace_back(update);
        }
    }

    uint32_t sum = 0;
    for (const auto update : validUpdates)
    {
        uint32_t middleIdx = update.size() / 2;
        sum += update[middleIdx];
    }

    return sum;
}