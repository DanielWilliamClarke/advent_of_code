#ifndef PRINTER_H
#define PRINTER_H

#include <iterator>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cxxabi.h>

#include "constraints.h"
#include "measurer.h"
#include "solution.h"

template <Readable Input>
class Printer 
{
public: 
    virtual void print (const std::vector<Input>&) const = 0;
};

template <Readable Input, Streamable Output1, Streamable Output2 = Output1>
class SolutionPrinter :
        public Solution<Input, Output1, Output2>,
        public Printer<Input>,
        public Measurer
{
public:
    void print(const std::vector<Input>&) const override;
};

template <Readable Input, Streamable Output1, Streamable Output2>
void SolutionPrinter<Input, Output1, Output2>::print(const std::vector<Input>& input) const
{
    // Magic typename method..
    int status;
    const auto solutionName = abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, &status);

    std::array<std::string, 40> line;
    std::fill(line.begin(), line.end(), "🎄");
    std::ostringstream oss;
    std::copy(line.begin(), line.end()-1,
              std::ostream_iterator<std::string>(oss, ""));

    std::cout << oss.str() << std::endl;
    std::cout << "🎅 Running Advent Of Code 2023: { " << solutionName << " } 🎅" << std::endl;

    auto [output1, timing1] = this->template measure<Output1>( [&]() { return this->part1(input); });
    std::cout << "Part 1: " << output1 << " | Timing: [" << timing1 << "]s" << std::endl;
    auto [output2, timing2] = this->template measure<Output2>( [&]() { return this->part2(input); });
    std::cout << "Part 2: " << output2 << " | Timing: [" << timing2 << "]s" << std::endl;

    std::cout << oss.str() << std::endl;
}

#endif // PRINTER_H