#ifndef DAY_00_H
#define DAY_00_H
#pragma once

#include "solution/solution.h"
#include "solution/printer.h"
#include <vector>

class Day00 : public Printer, public Solution<int, int>{
public:
    Day00(std::unique_ptr<SolutionPrinter<int>> printer);

    void print () const override;

    std::vector<int> readInput() const override;
    int part1(std::vector<int>) const override;
    int part2(std::vector<int>) const override;
private: 
    std::unique_ptr<SolutionPrinter<int>> printer;
};

#endif // DAY_00_H