#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class InputFile
{
public:
    /**
     * @brief Takes in a filename and reads the file into a vector of lines
     *
     * @param filename Filename to read
     */
    InputFile(std::string filename = "./input.txt");
    ~InputFile() = default;

    /**
     * @brief Returns a vector of lines from the file
     *
     * @return std::vector<std::string> Vector of lines from the file.
     */
    std::vector<std::string> &getLines();

    /**
     * @brief Returns the text from the file as a single string
     *
     * @return std::string Text from the file as a single string
     */
    std::string getText();

private:
    /// @brief Filename to read
    std::string _filename;
    /// @brief Vector of lines from the file
    std::vector<std::string> _lines;
    /// @brief File stream
    std::ifstream _file;
};