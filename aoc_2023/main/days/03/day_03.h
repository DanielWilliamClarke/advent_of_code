#ifndef DAY_03_H
#define DAY_03_H

#include "main/solution/day.h"

struct Coordinate {
    int x;
    int y;

    Coordinate()
            : x(0), y(0)
    {}

    Coordinate(int x, int y)
            : x(x), y(y)
    {}
};

struct Candidate {
    std::string number;
    Coordinate start;
    Coordinate end;
};

bool validateEnginePart(const std::vector<std::string>& input, const Candidate& candidate);

class Day03 : public Day<int>
{
public:
    virtual ~Day03() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_03_H