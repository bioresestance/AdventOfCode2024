/**
 * Day-14 - Part 01
 */
#include "include.hpp"
#include "Utils.hpp"
#include <regex>
#include <ranges>
#include <algorithm>
#include <iostream>

static constexpr int32_t MAP_WIDTH = 101;
static constexpr int32_t MAP_HEIGHT = 103;
static constexpr int32_t RUN_TIME = 100;

struct Robot
{
    Coordinate position;
    struct Velocity
    {
        int64_t x_vel;
        int64_t y_vel;
    } velocity;
};

static std::vector<Robot> parseInput(const std::vector<std::string> &inputStrings)
{
    std::vector<Robot> robots;
    std::regex pattern(R"(p=(\d+),(\d+) v=(-?\d+),(-?\d+))");

    for (const auto &line : inputStrings)
    {
        std::smatch match;
        if (std::regex_search(line, match, pattern))
        {
            Robot robot;
            robot.position.x = std::stoi(match[1].str());
            robot.position.y = std::stoi(match[2].str());
            robot.velocity.x_vel = std::stoi(match[3].str());
            robot.velocity.y_vel = std::stoi(match[4].str());
            robots.push_back(robot);
        }
    }

    return robots;
}

static void PrintMap(std::vector<Robot> &robots)
{
    std::array<std::array<char, MAP_WIDTH>, MAP_HEIGHT> map;
    for (auto &row : map)
    {
        std::ranges::fill(row, '.');
    }

    for (const auto &robot : robots)
    {
        char &point = map[robot.position.y][robot.position.x];

        if (point == '.')
        {
            point = '1';
        }
        else
        {
            point++;
        }
    }

    for (auto &row : map)
    {
        for (const char point : row)
        {
            std::cout << point;
        }
        std::cout << std::endl;
    }
}

int64_t handlePart1(const std::vector<std::string> &inputLines)
{
    auto robots = parseInput(inputLines);

    for (auto &robot : robots)
    {
        robot.position.x += robot.velocity.x_vel * RUN_TIME;
        robot.position.y += robot.velocity.y_vel * RUN_TIME;

        // Wrap around for x position
        if (robot.position.x < 0)
        {
            robot.position.x = (robot.position.x % MAP_WIDTH + MAP_WIDTH) % MAP_WIDTH;
        }
        else
        {
            robot.position.x = robot.position.x % MAP_WIDTH;
        }

        // Wrap around for y position
        if (robot.position.y < 0)
        {
            robot.position.y = (robot.position.y % MAP_HEIGHT + MAP_HEIGHT) % MAP_HEIGHT;
        }
        else
        {
            robot.position.y = robot.position.y % MAP_HEIGHT;
        }
    }
    // PrintMap(robots);

    constexpr auto half_x = (MAP_WIDTH - 1) / 2;
    constexpr auto half_y = (MAP_HEIGHT - 1) / 2;

    auto robot_view = robots |
                      std::views::filter([](auto &&robot)
                                         { return not((robot.position.x == half_x) or (robot.position.y == half_y)); });

    uint64_t q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (const auto &robot : robot_view)
    {
        if (robot.position <= Coordinate{half_x, half_y})
        {
            q1++;
        }
        else if (robot.position >= Coordinate{half_x, half_y})
        {
            q4++;
        }
        else if (robot.position >= Coordinate{half_x, 0})
        {
            q2++;
        }
        else if (robot.position >= Coordinate{0, half_y})
        {
            q3++;
        }
    }

    return q1 * q2 * q3 * q4;
}