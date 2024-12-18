#include <string>
#include <iostream>
#include <string_view>
#include <gtest/gtest.h>
#include <filesystem>
#include "InputFile.hpp"
#include "src/include.hpp"

// Add the test input and output strings here to validate the solution
const std::string_view testInputPart1String =   "3   4\n" \
                                                "4   3\n" \
                                                "2   5\n" \
                                                "1   3\n" \
                                                "3   9\n" \
                                                "3   3";
const std::string_view testOutputPart1String = "11";

const std::string_view testInputPart2String =   "3   4\n" \
                                                "4   3\n" \
                                                "2   5\n" \
                                                "1   3\n" \
                                                "3   9\n" \
                                                "3   3";
const std::string_view testOutputPart2String = "31";

class Day1Tests : public ::testing::Test
{
protected:

    InputFile inputFile;

    Day1Tests() : inputFile(getInputFilePath())
    {

    }
   
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
};



TEST_F(Day1Tests, TestPart1Verify)
{
    uint32_t resInt = std::stoi(testOutputPart1String.data());
    std::string result = handlePart1(testInputPart1String);
    uint32_t resultInt = std::stoi(result);
    std::cout << "Part 1 Result: " << resultInt << std::endl;
    ASSERT_EQ(resultInt, resInt);
}

TEST_F(Day1Tests, TestPart2Verify)
{
    uint32_t resInt = std::stoi(testOutputPart2String.data());
    std::string result = handlePart2(testInputPart2String);
    uint32_t resultInt = std::stoi(result);
    std::cout << "Part 2 Result: " << resultInt << std::endl;
    ASSERT_EQ(resultInt, resInt);
}

TEST_F(Day1Tests, TestPart1Actual)
{
    uint32_t resInt = std::stoi(testOutputPart1String.data());
    std::string result = handlePart1(inputFile.getText());
    uint32_t resultInt = std::stoi(result);
    std::cout << "Part 1 Result: " << resultInt << std::endl;
}

TEST_F(Day1Tests, TestPart2Actual)
{
    uint32_t resInt = std::stoi(testOutputPart2String.data());
    std::string result = handlePart2(inputFile.getText());
    uint32_t resultInt = std::stoi(result);
    std::cout << "Part 2 Result: " << resultInt << std::endl;
}

