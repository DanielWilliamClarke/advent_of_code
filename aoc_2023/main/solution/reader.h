#ifndef READER_H
#define READER_H

#include <fstream>
#include <iterator>

#include "constraints.h"

template<Readable Data>
class Reader
{
public:
    virtual std::vector<Data> readInput () const = 0;
};

template <Readable Input>
class FileInputReader : public Reader<Input>
{
public:
    [[nodiscard]] virtual constexpr std::string filename() const = 0;
    std::vector<Input> readInput() const override;
};

template <Readable Input>
std::vector<Input> FileInputReader<Input>::readInput() const
{
    std::ifstream fs(this->filename());
    std::vector<Input> input;

    std::copy(
            std::istream_iterator<Input>(fs),
            std::istream_iterator<Input>(),
            std::back_inserter(input));

    // std::for_each(input.begin(), input.end(), [](std::string line) {
    //     std::cout << line << std::endl;
    // });

    return input;
}

#endif // READER_H