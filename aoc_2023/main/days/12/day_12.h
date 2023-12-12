#ifndef DAY_12_H
#define DAY_12_H

#include "main/solution/day.h"

class Day12 : public Day<int>
{
public:
    virtual ~Day12() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_12_H