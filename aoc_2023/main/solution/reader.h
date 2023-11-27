#ifndef READER_H
#define READER_H
#pragma once

#include <fstream>
#include <iterator>

#include "constraints.h"
#include "solution.h"

template<Readable Data>
class Reader 
{
public: 
   virtual std::vector<Data> readInput () const = 0;
};

template <Readable Input, Streamable Output1, Streamable Output2 = Output1>
class ReadableSolution : public Solution<Input, Output1, Output2>, public Reader<Input>
{
public:
    std::vector<Input> readInput() const override;
};

template <Readable Input, Streamable Output1, Streamable Output2>
std::vector<Input> ReadableSolution<Input, Output1, Output2>::readInput() const
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