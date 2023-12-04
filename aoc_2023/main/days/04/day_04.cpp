#include "day_04.h"

#include <ranges>
#include <numeric>

#include "main/solution/string_utils.h"

constexpr std::string Day04::filename () const 
{
    return "main/days/04/input.txt";
}

int Day04::part1(const std::vector<std::string>& input) const
{
    return std::transform_reduce(
    input.begin(),
    input.end(),
    0,
    std::plus<>(),
    [=](const std::string& game) {
        auto scratchCard = splitString(game, ':').back();
        auto sides = splitString(scratchCard, '|');

        auto winningNumbers =  splitString(sides.front(), ' ')
            | std::views::transform([=] (const std::string& number) { return std::stoi(number); });

        auto foundNumbers =  splitString(sides.back(), ' ')
            | std::views::transform([=] (const std::string& number) { return std::stoi(number); })
            | std::views::filter([&winningNumbers](const int number) {
                return std::ranges::find(winningNumbers, number) != winningNumbers.end();
            });

        return std::pow(2, std::ranges::distance(foundNumbers) - 1);
    });
}

int Day04::part2(const std::vector<std::string>& input) const 
{
    return 0;
}