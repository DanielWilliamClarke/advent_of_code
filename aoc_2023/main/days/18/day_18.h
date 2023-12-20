#ifndef DAY_18_H
#define DAY_18_H

#include "main/solution/day.h"

namespace day18
{
    using Position = std::pair<long long, long long>;
    using Direction = std::pair<int, int>;

    struct Point
    {
        Position position;
        Direction direction;
        long long length;
        std::string color;
    };

    std::vector<Point> parsePoints(const std::vector<std::string>& input);
    std::vector<Point> parsePointsFromHex(const std::vector<std::string>& input);
    long long shoelace(const std::vector<Point>& points);
    long long perimeter(const std::vector<Point>& points);
    long long calculateArea(const std::vector<Point>& points);
}

class Day18 : public Day<long long>
{
public:
    virtual ~Day18() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] long long part1(const std::vector<std::string>&) const override;
    [[nodiscard]] long long part2(const std::vector<std::string>&) const override;
};

#endif // DAY_18_H