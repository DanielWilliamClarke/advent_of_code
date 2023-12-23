#ifndef DAY_21_H
#define DAY_21_H

#include "main/solution/day.h"

namespace day21
{

}

class Day21 : public Day<int>
{
public:
    virtual ~Day21() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_21_H