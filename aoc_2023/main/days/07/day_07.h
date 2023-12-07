#ifndef DAY_07_H
#define DAY_07_H

#include "main/solution/day.h"

class Day07 : public Day<int>
{
public:
    virtual ~Day07() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_07_H