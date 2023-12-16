#ifndef DAY_16_H
#define DAY_16_H

#include "main/solution/day.h"

class Day16 : public Day<int>
{
public:
    virtual ~Day16() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_16_H