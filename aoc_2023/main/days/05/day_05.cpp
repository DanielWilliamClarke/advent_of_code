#include "day_05.h"

#include <ranges>

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

long long Day05::part2(const std::vector<std::string>& input) const
{
    return 0;
}