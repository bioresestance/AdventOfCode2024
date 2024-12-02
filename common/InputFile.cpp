#include "InputFile.hpp"

InputFile::InputFile(std::string filename) : _filename(filename)
{
    // Open the file
    _file.open(filename);
    if (!_file.is_open())
    {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }

    // Rad in all the lines and store them in the vector
    std::string line;
    while (std::getline(_file, line))
    {
        _lines.push_back(line);
    }

    // Close the file
    _file.close();
}

std::vector<std::string> &InputFile::getLines()
{
    return _lines;
}

std::string InputFile::getText()
{
    std::string text;
    for (const auto &line : _lines)
    {
        text += line + "\n";
    }

    return text;
}