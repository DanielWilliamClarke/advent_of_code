#include "day_04.h"

#include <ranges>
#include <numeric>

#include "main/solution/string_utils.h"

int findWinners(const std::string& card)
{
    auto scratchCard = splitString(card, ":").back();
    auto sides = splitString(scratchCard, "|");

    auto winningNumbers =  splitString(sides.front(), " ")
       | std::views::transform([=] (const std::string& number) { return std::stoi(number); });

    auto foundNumbers =  splitString(sides.back(), " ")
        | std::views::transform([=] (const std::string& number) { return std::stoi(number); })
        | std::views::filter([&winningNumbers](const int number) {
            return std::ranges::find(winningNumbers, number) != winningNumbers.end();
        });

    return std::ranges::distance(foundNumbers);
}

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
    [=](const std::string& card) {
        return std::pow(2, findWinners(card) - 1);
    });
}

int Day04::part2(const std::vector<std::string>& input) const 
{
    std::vector<int> cardCounts(input.size(), 1);

    for(auto i = 0; i < input.size(); ++i)
    {
        auto winners = findWinners(input[i]);

        for(auto j = i + 1; j < i + 1 + winners; ++j) {
            // add the total copies for each card for each instance of the winning card
            cardCounts[j] += cardCounts[i];
        }
    }

    return std::accumulate(
    cardCounts.begin(),
    cardCounts.end(),
    0,
    std::plus<>()
    );
}