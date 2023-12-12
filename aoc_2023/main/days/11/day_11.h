#ifndef DAY_11_H
#define DAY_11_H

#include "main/solution/day.h"

enum Space {
    GALAXY = '#',
    EMPTY = '.'
};

struct SpacialCoordinates {
    Space type;
    long long x;
    long long y;

    SpacialCoordinates(Space type, long long x, long long y)
        : type(type), x(x), y(y)
    {}
};

std::vector<std::vector<SpacialCoordinates>> parseUniverse(const std::vector<std::string>& input);
std::vector<std::vector<SpacialCoordinates>> applyDarkEnergy(const std::vector<std::vector<SpacialCoordinates>>& universe, long long factor);
std::vector<SpacialCoordinates> observeUniverse(const std::vector<std::vector<SpacialCoordinates>>& universe);
std::vector<long long> analyzeDistances(const std::vector<SpacialCoordinates>& observations);
long long traverseUniverse(const std::vector<std::string>& input, long long factor);

class Day11 : public Day<long long>
{
public:
    virtual ~Day11() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] long long part1(const std::vector<std::string>&) const override;
    [[nodiscard]] long long part2(const std::vector<std::string>&) const override;
};

#endif // DAY_11_H