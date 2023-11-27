#ifndef PRINTER_H
#define PRINTER_H
#pragma once

#include <iterator>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cxxabi.h>
#include <chrono>
#include <functional>

#include "constraints.h"
#include "reader.h"
#include "solution.h"

class Printer 
{
public: 
    virtual void print () const = 0;
};

template <Readable Input, Streamable Output1, Streamable Output2 = Output1>
class PrintableSolution : public ReadableSolution<Input, Output1, Output2>, public Printer
{
public:
    void print() const override;
private:
    template<Streamable Output>
    void measure(int part, std::function<Output()> method) const;
};

template <Readable Input, Streamable Output1, Streamable Output2>
void PrintableSolution<Input, Output1, Output2>::print() const
{
    // Magic typename method..
    int status;
    const auto solutionName = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);

    std::array<std::string, 40> line;
    std::fill(line.begin(), line.end(), "🎄");
    std::ostringstream oss;
    std::copy(line.begin(), line.end()-1,
              std::ostream_iterator<std::string>(oss, ""));

    std::cout << oss.str() << std::endl;
    std::cout << "🎅 Running Advent Of Code 2023: { " << solutionName << " } 🎅" << std::endl;

    const auto input = this->readInput();
    this->measure<Output1>(1, [&]() {
        return this->part1(input);
    });
    this->measure<Output2>(2, [&]() {
        return this->part2(input);
    });

    std::cout << oss.str() << std::endl;
}

template <Readable Input, Streamable Output1, Streamable Output2>
template<Streamable Output>
void PrintableSolution<Input, Output1, Output2>::measure(int part, std::function<Output()> method) const
{
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::duration<float> duration;

    start = std::chrono::high_resolution_clock::now();
    auto output = method();
    end = std::chrono::high_resolution_clock::now();

    std::cout << "Part " << part << ": " << output;
    duration = end - start;
    std::cout << std::setfill(' ') << std::setw(20) << "🕰️  Timing: [" << duration.count() << "s]" << std::endl;
}

#endif // PRINTER_H