#ifndef DAY_00_H
#define DAY_00_H
#pragma once

#include <vector>

#include "solution/solution.h"

class Day00 : public Solution<int> {
public:
    const std::string filename() const override;
    int part1(std::vector<std::string>) const override;
    int part2(std::vector<std::string>) const override;
};

#endif // DAY_00_H