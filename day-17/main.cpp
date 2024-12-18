#include <string>
#include <iostream>
#include <string_view>
#include <gtest/gtest.h>
#include <filesystem>
#include <chrono>
#include "InputFile.hpp"
#include "src/include.hpp"

#define ENABLE_PART1 (true)
#define ENABLE_PART2 (false)

// Add the test input and output strings here to validate the solution
const std::vector<std::string> testInputStrings = {"Register A: 729",
                                                   "Register B: 0",
                                                   "Register C: 0",
                                                   "",
                                                   "Program: 0,1,5,4,3,0"};

const std::string part1Expected = "4,6,3,5,6,3,5,2,1,0";

const std::vector<std::string> testInputStrings2 = {"Register A: 41644071",
                                                    "Register B: 0",
                                                    "Register C: 0",
                                                    "",
                                                    "Program: 2,4,1,2,7,5,1,7,4,4,0,3,5,5,3,0"};

const std::string part1Expected2 = "3,1,5,3,7,4,2,7,5";

const std::vector<std::string> testInputStrings_part2 = {"Register A: 2024",
                                                         "Register B: 0",
                                                         "Register C: 0",
                                                         "",
                                                         "Program: 0,3,5,4,3,0"};
const int64_t part2Expected = 117440;

static std::string getInputFilePath()
{
    using std::filesystem::path;

    // Get the directory of the current file
    path currentFilePath = __FILE__;
    path currentDir = currentFilePath.parent_path();

    // Append the input file name to the directory path
    path inputFilePath = currentDir / "input.txt";

    return inputFilePath.string();
}

#if ENABLE_PART1
TEST(Day17Tests, TestPart1)
{
    auto result = handlePart1(testInputStrings);
    std::cout << "Part 1 - Test Result: " << result << std::endl;
    ASSERT_EQ(result, part1Expected);
}

TEST(Day17Tests, TestPart1_2)
{
    auto result = handlePart1(testInputStrings2);
    std::cout << "Part 1 - Test Result: " << result << std::endl;
    ASSERT_EQ(result, part1Expected2);
}
#endif

#if ENABLE_PART2
TEST(Day17Tests, TestPart2)
{
    auto result = handlePart2(testInputStrings_part2);
    std::cout << "Part 2 - Test Result: " << result << std::endl;
    ASSERT_EQ(result, part2Expected);
}
#endif

int main(int argc, char **argv)
{

    // Run the tests
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    // If the tests pass, run the solution
    if (result == 0)
    {
        InputFile inputFile = InputFile(getInputFilePath());
        std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;
#if ENABLE_PART1
        std::cout << "Day 17, running solution:" << std::endl;
        auto startPart1 = std::chrono::high_resolution_clock::now();
        auto part1Result = handlePart1(inputFile.getLines());
        auto endPart1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationPart1 = endPart1 - startPart1;
        std::cout << "Part 1 - Real Result: " << part1Result << std::endl;
        std::cout << "Part 1 - Time taken: " << durationPart1.count() << " seconds" << std::endl;
#endif

#if ENABLE_PART2
        auto startPart2 = std::chrono::high_resolution_clock::now();
        auto part2Result = handlePart2(inputFile.getLines());
        auto endPart2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationPart2 = endPart2 - startPart2;
        std::cout << "Part 2 - Real Result: " << part2Result << std::endl;
        std::cout << "Part 2 - Time taken: " << durationPart2.count() << " seconds" << std::endl;
#endif
        std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;
    }
    return result;
}