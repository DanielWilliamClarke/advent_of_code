#ifndef DAY_00_H
#define DAY_00_H
#pragma once

#include "main/solution/solution.h"

class Day00 : public Solution<int, int> 
{
public:
    virtual ~Day00() = default;

    constexpr std::string filename() const override;
    int part1(const std::vector<int>&) const override;
    int part2(const std::vector<int>&) const override;
};

#endif // DAY_00_H