#ifndef DAY_04_H
#define DAY_04_H

#include "main/solution/day.h"

class Day04 : public Day<int>
{
public:
    virtual ~Day04() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_04_H