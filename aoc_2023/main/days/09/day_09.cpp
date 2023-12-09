#include "day_09.h"

#include <ranges>
#include <numeric>

#include "main/solution/string_utils.h"

std::vector<std::vector<long long>> parseHistories(const std::vector<std::string>& input)
{
    auto histories = input
        | std::views::transform([=](const std::string& line) -> std::vector<long long> {
            auto numbers = splitString(line, ' ')
                | std::views::transform([=](const std::string& number) -> long long {
                    return std::stoll(number);
                });

            return { numbers.begin(), numbers.end() };
        });

    return { histories.begin(), histories.end() };
}

long long processHistory(const std::vector<long long>& history)
{
    // generate analyses
    std::vector<std::vector<long long>> analyses = { history };

    while(
        std::ranges::any_of(analyses.back(), [=](long long number) {
            return number != 0;
        })
    )
    {
        auto currentLevel = analyses.back();
        auto length = currentLevel.size() - 1;

        std::vector<long long> currentAnalysis;
        currentAnalysis.reserve(length);

        for(auto i = 0; i < length; ++i) {
            currentAnalysis.push_back(currentLevel[i + 1] - currentLevel[i]);
        }

        analyses.push_back(currentAnalysis);
    }

    return std::accumulate(
        analyses.rbegin(),
        analyses.rend(),
        0,
        [=] (long long acc, const std::vector<long long>& analysis) -> long long {
            return acc + analysis.back();
        }
    );
}

constexpr std::string Day09::filename () const 
{
    return "main/days/09/input.txt";
}

long long Day09::part1(const std::vector<std::string>& input) const
{
    auto histories = parseHistories(input);

    return std::transform_reduce(
        histories.begin(),
        histories.end(),
        0,
        std::plus<>(),
        [=](const std::vector<long long>& history) -> long long {
            return processHistory(history);
        }
    );
}

long long Day09::part2(const std::vector<std::string>& input) const
{
    return 0;
}