#include "day_00.h"

Day00::Day00(std::unique_ptr<SolutionPrinter<int>> printer)
    : printer(std::move(printer))
    {}

void Day00::print() const {
    auto input = this->readInput();
    this->printer->print(
        this->part1(input),
        this->part2(input)
    );
}

std::vector<int> Day00::readInput () const {
    return { 1, 2, 3 };
}

int Day00::part1(std::vector<int>) const {
    return 0;
}

int Day00::part2(std::vector<int>) const {
    return 0;
}