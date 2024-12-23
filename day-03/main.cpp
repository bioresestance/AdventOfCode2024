#include <string>
#include <iostream>
#include <string_view>
#include <gtest/gtest.h>
#include <filesystem>
#include "InputFile.hpp"
#include "src/include.hpp"


#define ENABLE_PART1 (true)
#define ENABLE_PART2 (true)



// Add the test input and output strings here to validate the solution
const std::vector<std::string> testInputStrings = {"xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"};
const std::vector<std::string> testPart2InputStrings = {"xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"};

const uint64_t part1Expected = 161;
const uint64_t part2Expected = 48;

    
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
TEST(Day3Tests, TestPart1)
{
    auto result = handlePart1(testInputStrings);
    std::cout << "Part 1 - Test Result: " << result << std::endl;
    ASSERT_EQ(result, part1Expected);
}
#endif

#if ENABLE_PART2
TEST(Day3Tests, TestPart2)
{
    auto result = handlePart2(testPart2InputStrings);
    std::cout << "Part 2 - Test Result: " << result << std::endl;
    ASSERT_EQ(result, part2Expected);
}
#endif




int main(int argc, char **argv) {

    // Run the tests
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    // If the tests pass, run the solution
    if (result == 0) 
    {
        std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;
        #if ENABLE_PART1
        std::cout << "Day 3, running solution:" << std::endl;
        InputFile inputFile = InputFile(getInputFilePath());
        auto part1Result = handlePart1(inputFile.getLines());
        std::cout << "Part 1 - Real Result: " << part1Result << std::endl;
        #endif

        #if ENABLE_PART2
        auto part2Result = handlePart2(inputFile.getLines());
        std::cout << "Part 2 - Real Result: " << part2Result << std::endl;
        #endif
        std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;
    } 
    return result;
}