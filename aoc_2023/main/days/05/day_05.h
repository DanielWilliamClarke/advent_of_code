#ifndef DAY_05_H
#define DAY_05_H

#include "main/solution/day.h"

struct Mapping {
    long long source;
    long long destination;
    long long length;

    Mapping(long long source, long long destination, long long length)
        : source(source), destination(destination), length(length)
    {}
};

struct Range {
    long long start;
    long long stop;

    Range()
        : start(0), stop(0)
    {}

    Range(long long start, long long stop)
        : start(start), stop(stop)
    {}
};

std::vector<long long> parseSeeds(const std::string& line);
std::vector<std::vector<Mapping>> parseMaps(const std::vector<std::string>& input);
std::vector<Range> parseRanges(const std::string& line);

std::pair<std::optional<Range>, std::vector<Range>> overlapMapping(const Range& range, const Mapping& mapping);

class Day05 : public Day<long long>
{
public:
    virtual ~Day05() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] long long part1(const std::vector<std::string>&) const override;
    [[nodiscard]] long long part2(const std::vector<std::string>&) const override;
};

#endif // DAY_05_H