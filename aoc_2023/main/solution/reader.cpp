#include "reader.h"

#include <fstream>
#include <sstream>

std::vector<std::string> FileInputReader::readInput() const
{
    std::vector<std::string> input;

    std::ifstream fs(this->filename());

    std::string line;
    while (std::getline(fs, line)) {
        input.push_back(line);

        // std::cout << line << std::endl;
    }

    fs.close();

    return input;
}