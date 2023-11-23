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

#include "printer.h"
#include "reader.h"

template <typename Output1, typename Output2 = Output1>
class Solution : public Printer, public Reader
{
public:
    virtual Output1 part1(const std::vector<std::string> input) const = 0;
    virtual Output2 part2(const std::vector<std::string> input) const = 0;
    virtual constexpr std::string filename() const = 0;

    virtual std::vector<std::string> readInput() const override;
    virtual void print() const override;
};

template <typename Output1, typename Output2>
std::vector<std::string> Solution<Output1, Output2>::readInput() const
{
    std::ifstream fs(this->filename());
    std::vector<std::string> input;

    std::copy(
        std::istream_iterator<std::string>(fs),
        std::istream_iterator<std::string>(),
        std::back_inserter(input));

    // std::for_each(input.begin(), input.end(), [](std::string line) {
    //     std::cout << line << std::endl;
    // });

    return input;
}

template <typename Output1, typename Output2>
void Solution<Output1, Output2>::print() const
{
    // Magic typename method..
    int status;
    const auto solutionName = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
    const auto line = "🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄🎄";

    std::cout << line << '\n';

    std::cout << "🎅 Running Advent Of Code 2023: { " << solutionName << " } 🎅" << '\n';
    const auto input = this->readInput();
    std::cout << "Part 1:" << std::setw(2) << this->part1(input) << '\n';
    std::cout << "Part 2:" << std::setw(2) << this->part2(input) << '\n';

    std::cout << line << '\n';
}

#endif // SOLUTION_H