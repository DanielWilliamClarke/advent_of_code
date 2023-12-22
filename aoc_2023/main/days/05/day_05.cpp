#include "day_05.h"

#include <ranges>
#include <thread>
#include <utility>

#include "main/solution/string_utils.h"

std::vector<long long> parseSeeds(const std::string& line)
{
    auto seeds = splitString(line, ":").back();

    auto seedNumbers = splitString(seeds, " ")
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
           auto numbers = splitString(r, " ")
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

std::vector<Range> parseRanges(const std::string& line)
{
    auto seeds = parseSeeds(line);

    std::vector<Range> seedRanges = { };
    for(auto iter = seeds.begin(); iter != seeds.end(); iter+=2)
    {
        seedRanges.emplace_back(
        *iter,
        *iter + *(iter + 1)
        );
    }

    return seedRanges;
}

std::pair<std::optional<Range>, std::vector<Range>> overlapMapping(const Range& range, const Mapping& mapping)
{
    auto mappingStart = mapping.source;
    auto mappingStop = mapping.source + mapping.length - 1;

    auto overlapStart = std::max(range.start, mappingStart);
    auto overlapStop = std::min(range.stop, mappingStop);

    if (overlapStart > overlapStop)
    {
        // no overlap
        std::vector<Range> remaining = { range };
        return std::make_pair(std::nullopt, remaining);
    }

    auto resultStart = overlapStart + mapping.destination - mappingStart;
    auto resultStop = overlapStop + mapping.destination - mappingStart;

    std::vector<Range> remaining;
    if (overlapStart > range.start)
    {
        remaining.emplace_back(range.start, overlapStart - 1);
    }

    if (overlapStop < range.stop)
    {
        remaining.emplace_back(overlapStop + 1, range.stop);
    }

    return std::make_pair(
        std::optional<Range>({resultStart, resultStop}),
        remaining
    );
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

// Confession: this part really stumped me
// Ending up following this video to solve: https://www.youtube.com/watch?v=OjWhoZ3Icrs
long long Day05::part2(const std::vector<std::string>& input) const
{
    auto maps = parseMaps({input.begin() + 2, input.end() });

    auto currentRanges = parseRanges(input.at(0));

    for(const auto& mappings : maps)
    {
        std::vector<Range> newRanges;

        for(auto mapping :  mappings)
        {
            std::vector<Range> newCurrentRanges;

            for(auto range : currentRanges)
            {
                auto [translated, remaining] = overlapMapping(range, mapping);

                if (translated) {
                    newRanges.push_back(*translated);
                }

                newCurrentRanges.insert(newCurrentRanges.end(), remaining.begin(), remaining.end());
            }

            currentRanges = newCurrentRanges;
        }

        currentRanges.insert(currentRanges.end(), newRanges.begin(), newRanges.end());
    }

    auto smallest = std::ranges::min_element(
        currentRanges,
        [=] (auto a, auto b) {
            return a.start < b .start;
        });

    return smallest->start;
}