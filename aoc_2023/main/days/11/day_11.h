#ifndef DAY_11_H
#define DAY_11_H

#include "main/solution/day.h"

enum Space {
    GALAXY = '#',
    EMPTY = '.'
};

struct SpacialCoordinates {
    int x;
    int y;

    SpacialCoordinates(int x, int y)
        : x(x), y(y)
    {}
};

std::vector<std::vector<Space>> parseUniverse(const std::vector<std::string>& input);
std::vector<std::vector<Space>> applyDarkEnergy(const std::vector<std::vector<Space>>& universe);
std::vector<SpacialCoordinates> observeUniverse(const std::vector<std::vector<Space>>& universe);
std::vector<int> analyzeDistances(const std::vector<SpacialCoordinates>& observations);

class Day11 : public Day<int>
{
public:
    virtual ~Day11() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_11_H