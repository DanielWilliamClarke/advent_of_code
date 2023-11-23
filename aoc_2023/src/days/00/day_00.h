#ifndef DAY_00_H
#define DAY_00_H
#pragma once

#include "solution/solution.h"
#include <vector>

class Day00 : public Solution<int, int> {
public:
    std::vector<int> readInput() const override;
    int part1(std::vector<int>) const override;
    int part2(std::vector<int>) const override;
};

#endif // DAY_00_H