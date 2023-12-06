#ifndef DAY_06_H
#define DAY_06_H

#include "main/solution/day.h"

struct Race {
    long long time;
    long long distance;

    Race(const long long time, const long long distance)
        : time(time), distance(distance)
    {}
};

std::vector<long long> parseNumbers(const std::string& line, bool ignoreWhitespace = false);
std::vector<Race> parseRaces(const std::string& times, const std::string& distances, bool ignoreWhitespace = false);
long long processRaces(const std::vector<Race>& races);

class Day06 : public Day<int, long long>
{
public:
    virtual ~Day06() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] long long part2(const std::vector<std::string>&) const override;
};

#endif // DAY_06_H