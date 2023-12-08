#ifndef DAY_08_H
#define DAY_08_H

#include "main/solution/day.h"

class Day08 : public Day<int>
{
public:
    virtual ~Day08() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_08_H