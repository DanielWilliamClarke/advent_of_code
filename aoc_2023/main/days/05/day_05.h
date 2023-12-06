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

struct SeedRange {
    long long id;
    long long length;

    SeedRange()
        : id(0), length(0)
    {}

    SeedRange(long long id, long long length)
        : id(id), length(length)
    {}
};

std::vector<long long> parseSeeds(const std::string& line);
std::vector<std::vector<Mapping>> parseMaps(const std::vector<std::string>& input);
std::vector<SeedRange> parseSeedRanges(const std::string& line);

class Day05 : public Day<long long>
{
public:
    virtual ~Day05() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] long long part1(const std::vector<std::string>&) const override;
    [[nodiscard]] long long part2(const std::vector<std::string>&) const override;
};

#endif // DAY_05_H