#ifndef DAY_09_H
#define DAY_09_H

#include "main/solution/day.h"

std::vector<std::vector<long long>> parseHistories(const std::vector<std::string>& input);
long long processHistory(const std::vector<long long>& history);

class Day09 : public Day<long long>
{
public:
    virtual ~Day09() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] long long part1(const std::vector<std::string>&) const override;
    [[nodiscard]] long long part2(const std::vector<std::string>&) const override;
};

#endif // DAY_09_H