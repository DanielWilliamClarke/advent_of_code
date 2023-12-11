#include "day_N01.h"

#include <range/v3/all.hpp>

constexpr std::string DayN01::filename() const
{
    return "main/days/N01/input.txt";
}

int DayN01::part1(const std::vector<std::string> &input) const
{
    auto processedInput = input
        | ranges::views::transform([=](const std::string& item) -> int {
            return std::stoi(item);
        });

    auto results = processedInput
        | ranges::views::transform([=](auto item) -> std::array<int, 2> {
            return std::array{item, 2020 - item};
        })
        | ranges::views::filter([&processedInput](const auto item) -> bool {
            return ranges::contains(processedInput, item.back());
        })
        | ranges::views::transform([=](auto item) -> int {
            return ranges::accumulate(item, 1, std::multiplies<>());
        })
        | ranges::views::take(1);

   return ranges::front(results);
}

int DayN01::part2(const std::vector<std::string> &input) const
{
    auto processedInput = input
        | ranges::views::transform([=](const std::string& item) -> int {
            return std::stoi(item);
        });

    auto results = ranges::views::cartesian_product(processedInput, processedInput)
        | ranges::views::transform([=](auto item) { 
            auto [a, b] = item;
            return std::array{a, b, 2020 - a - b};
        })
        | ranges::views::filter([&processedInput](const auto& item) {
            return ranges::contains(processedInput, item.back());
        })
        | ranges::views::transform([=](auto item) {
            return ranges::accumulate(item, 1, std::multiplies<>());
        })
        | ranges::views::take(1);

   return ranges::front(results);
}