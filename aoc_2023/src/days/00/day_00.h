#ifndef DAY_00_H
#define DAY_00_H
#pragma once

#include "solution/solution.h"
#include <vector>

class Day00 : public Solution<int, int> {
public:
    const std::vector<int> readInput() const override;
    int part1(const std::vector<int>) const override;
    int part2(const std::vector<int>) const override;
};

#endif // DAY_00_H