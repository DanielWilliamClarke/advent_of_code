#ifndef DAY_18_H
#define DAY_18_H

#include "main/solution/day.h"

class Day18 : public Day<int>
{
public:
    virtual ~Day18() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_18_H