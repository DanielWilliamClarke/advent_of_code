#ifndef DAY_N01_H
#define DAY_N01_H

#include "main/solution/day.h"

class DayN01 : public Day<int>
{
public:
    virtual ~DayN01() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_N01_H