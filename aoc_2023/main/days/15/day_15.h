#ifndef DAY_15_H
#define DAY_15_H

#include "main/solution/day.h"

class Day15 : public Day<int>
{
public:
    virtual ~Day15() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_15_H