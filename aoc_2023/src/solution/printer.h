#ifndef PRINTER_H
#define PRINTER_H
#pragma once

#include <iostream>
#include <iomanip>

class Printer {
public: 
    virtual void print () const = 0;
};

template <typename Output1, typename Output2 = Output1>
class SolutionPrinter { 
public:
    void print(Output1 part1, Output2 part2);
};

template <typename Output1, typename Output2>
void SolutionPrinter<Output1, Output2>::print(Output1 part1, Output2 part2) {
    std::cout << "Part 1:" << std::setw(5) << part1 << std::endl;
    std::cout << "Part 2:" << std::setw(5) << part2 << std::endl;
}

#endif // PRINTER_H