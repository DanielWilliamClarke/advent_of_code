#ifndef READER_H
#define READER_H

#include <vector>
#include <string>

class FileInputReader
{
public:
    [[nodiscard]] virtual constexpr std::string filename() const = 0;
    [[nodiscard]] std::vector<std::string> readInput() const;
};

#endif // READER_H