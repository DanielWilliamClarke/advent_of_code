#ifndef DAY_01_H
#define DAY_01_H

#include "main/solution/day.h"

class Day01 : public Day<std::string, int>
{
public:
    virtual ~Day01() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_01_H