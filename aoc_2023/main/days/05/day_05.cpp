#include "day_05.h"

#include <ranges>
#include <thread>

#include "main/solution/string_utils.h"

std::vector<long long> parseSeeds(const std::string& line)
{
    auto seeds = splitString(line, ':').back();

    auto seedNumbers = splitString(seeds, ' ')
       | std::views::transform([=] (const std::string& number) { return std::stoll(number); });

    return {seedNumbers.begin(), seedNumbers.end() };
}

std::vector<std::vector<Mapping>> parseMaps(const std::vector<std::string>& input)
{
    std::vector<std::vector<std::string>> unprocessedMaps = { { } };
    for(const auto& line : input)
    {
        if (!line.empty())
        {
            unprocessedMaps.back().push_back(line);
        }
        else
        {
            unprocessedMaps.emplace_back();
        }
    }

    std::vector<std::vector<Mapping>> maps = { };
    for(const auto& m : unprocessedMaps)
    {
        std::vector<Mapping> mappings = { };

        std::vector<std::string> ranges = { m.begin() + 1, m.end() };
        for(const auto& r : ranges)
        {
           auto numbers = splitString(r, ' ')
                | std::views::transform([=] (const std::string& number) { return std::stoll(number); });    ;

            std::vector<long long> rangeNumbers = { numbers.begin(), numbers.end() };

            mappings.push_back(Mapping(
            rangeNumbers.at(1),
            rangeNumbers.at(0),
            rangeNumbers.at(2)
            ));
        }

        maps.push_back(mappings);
    }

    return maps;
}

std::vector<SeedRange> parseSeedRanges(const std::string& line)
{
    auto seeds = parseSeeds(line);

    std::vector<SeedRange> seedRanges = { };

    for(auto iter = seeds.begin(); iter != seeds.end(); iter+=2) {
        seedRanges.push_back(SeedRange(
            *iter,
            *(iter + 1)
        ));
    }

    return seedRanges;
}

bool hasOverlap(const SeedRange& sr, const Mapping& m)
{
    // [x1:x2] and [y1:y2]
    // x1 <= y2 && y1 <= x2

    auto x1 = sr.id;
    auto x2 = sr.id + sr.length;

    auto y1 = m.source;
    auto y2 = m.source + m.length;

    return (
      x1 <= y2 &&
      y1 <= x2
    );
}

SeedRange findOverlap(const SeedRange& sr, const Mapping& m)
{
    return {
        std::max(sr.id, m.source),
        std::min(sr.id + sr.length, m.source + m.length)
    };
}

constexpr std::string Day05::filename () const 
{
    return "main/days/05/input.txt";
}

long long Day05::part1(const std::vector<std::string>& input) const
{
    auto seeds = parseSeeds(input.at(0));
    // parse seeds
    auto maps = parseMaps({input.begin() + 2, input.end() });

    auto locations = seeds
        | std::views::transform([&maps](const long long& s) {
            auto location = s;

            for(const auto& mappings : maps)
            {
                for(const auto& mapping : mappings)
                {
                    if(
                        location >= mapping.source &&
                        location <= mapping.source + mapping.length
                    )
                    {
                        auto diff = location - mapping.source;
                        
                        location = mapping.destination + diff;

                        break;
                    }
                }
            }

            return location;
        });

    return std::ranges::min(locations);
}

std::mutex coutMutex;

// https://www.youtube.com/watch?v=_RpZrD3CaDc
long long Day05::part2(const std::vector<std::string>& input) const
{
    auto seeds = parseSeedRanges(input.at(0));

    // parse seeds
    auto maps = parseMaps({input.begin() + 2, input.end() });

    return 0;
}