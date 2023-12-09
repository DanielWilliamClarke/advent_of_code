#ifndef DAY_10_H
#define DAY_10_H

#include "main/solution/day.h"

class Day10 : public Day<int>
{
public:
    virtual ~Day10() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_10_H