#ifndef SOLUTION_H
#define SOLUTION_H
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <cxxabi.h>
#include <chrono>

#include "printer.h"
#include "reader.h"

// Constrain types to those that can be printed via std::cout
template <typename T>
concept Streamable = requires (T t) {
    std::cout << t;
};

template <typename T>
concept Readable = requires(std::istream &os, T value) {
    { os >> value } -> std::convertible_to<std::istream &>;
};

template <Readable Input, Streamable Output1, Streamable Output2 = Output1>
class Solution : public Printer, public Reader<Input>
{
public:
    virtual Output1 part1(const std::vector<Input>& input) const = 0;
    virtual Output2 part2(const std::vector<Input>& input) const = 0;
    virtual constexpr std::string filename() const = 0;

    virtual std::vector<Input> readInput() const override;
    virtual void print() const override; 
};

template <Readable Input, Streamable Output1, Streamable Output2>
std::vector<Input> Solution<Input, Output1, Output2>::readInput() const
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

template <Readable Input, Streamable Output1, Streamable Output2>
void Solution<Input, Output1, Output2>::print() const
{
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::microseconds duration;

    // Magic typename method..
    int status;
    const auto solutionName = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
    const auto line = "🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄";

    std::cout << line << '\n';

    std::cout << "🎅 Running Advent Of Code 2023: { " << solutionName << " } 🎅" << '\n';
    const auto input = this->readInput();
    
    start = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1: " << this->part1(input);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setfill(' ') << std::setw(20) << "🕰️  Timing: [" << duration.count() << "ms]" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::cout << "Part 2: " << this->part2(input);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setfill(' ') << std::setw(20) << "🕰️  Timing: [" << duration.count() << "ms]" << std::endl;

    std::cout << line << '\n';
}

#endif // SOLUTION_H