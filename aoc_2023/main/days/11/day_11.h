#ifndef DAY_11_H
#define DAY_11_H

#include "main/solution/day.h"

class Day11 : public Day<int>
{
public:
    virtual ~Day11() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_11_H