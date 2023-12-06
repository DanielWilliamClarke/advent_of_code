#include "day_06.h"

#include <ranges>
#include <numeric>

#include "main/solution/string_utils.h"

std::vector<long long> parseNumbers(const std::string& line, bool ignoreWhitespace)
{
    auto numbers = splitString(line, ':').back();

    if(ignoreWhitespace)
    {
        numbers.erase(std::remove(numbers.begin(),numbers.end(),' '),numbers.end());
    }

    auto seedNumbers = splitString(numbers, ' ')
       | std::views::transform([=] (const std::string& number) { return std::stoll(number); });

    return {seedNumbers.begin(), seedNumbers.end() };
}

std::vector<Race> parseRaces(const std::string& times, const std::string& distances, bool ignoreWhitespace)
{
    auto timeValues = parseNumbers(times, ignoreWhitespace);
    auto distanceValues = parseNumbers(distances, ignoreWhitespace);

    std::vector<Race> races;
    races.reserve(timeValues.size());

    for(auto i = 0; i < timeValues.size(); i++)
    {
        races.emplace_back(timeValues.at(i), distanceValues.at(i));
    }

    return races;
}

long long processRaces(const std::vector<Race>& races)
{
    return std::transform_reduce(
        races.begin(),
        races.end(),
        1,
        std::multiplies<>(),
        [](const Race& race) {
            auto total = 0;

            for(auto speed = 0; speed < race.time; speed++) {
                auto travelTime = race.time - speed;

                auto distanceTravelled = speed * travelTime;

                if (distanceTravelled > race.distance) {
                    total += 1;
                }
            }

            // not to wipe out the result
            if (total == 0) {
                return 1;
            }

            return total;
        });
}

constexpr std::string Day06::filename () const 
{
    return "main/days/06/input.txt";
}

long long Day06::part1(const std::vector<std::string>& input) const
{
    return processRaces(
        parseRaces(
            input.at(0),
            input.at(1)
        )
    );
}

long long Day06::part2(const std::vector<std::string>& input) const
{
    return processRaces(
        parseRaces(
            input.at(0),
            input.at(1),
            true
        )
    );
}