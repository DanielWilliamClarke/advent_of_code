#ifndef DAY_00_H
#define DAY_00_H

#include "main/solution/day.h"

class Day00 : public Day<int>
{
public:
    virtual ~Day00() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_00_H