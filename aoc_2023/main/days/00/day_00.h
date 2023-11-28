#ifndef DAY_00_H
#define DAY_00_H
#pragma once

#include "main/solution/day.h"

class Day00 : public Day<int, int>
{
public:
    virtual ~Day00() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<int>&) const override;
    [[nodiscard]] int part2(const std::vector<int>&) const override;
};

#endif // DAY_00_H