#include "day_00.h"

#include <range/v3/all.hpp>

constexpr std::string Day00::filename() const
{
    return "main/days/00/input.txt";
}

int Day00::part1(const std::vector<int> &input) const
{
    auto results = input
        | ranges::views::transform([=](auto item) -> std::array<int, 2> {
            return std::array{item, 2020 - item};
        })
        | ranges::views::filter([&input](const auto item) -> bool {
            return ranges::contains(input, item.back());
        })
        | ranges::views::transform([=](auto item) -> int {
            return ranges::accumulate(item, 1, std::multiplies<>());
        });

   return ranges::front(results);
}

int Day00::part2(const std::vector<int> &input) const
{
    auto results = ranges::views::cartesian_product(input, input)
        | ranges::views::transform([=](auto item) { 
            auto [a, b] = item;
            return std::array{a, b, 2020 - a - b};
        })
        | ranges::views::filter([&input](const auto& item) {
            return ranges::contains(input, item.back()); 
        })
        | ranges::views::transform([=](auto item) {
            return ranges::accumulate(item, 1, std::multiplies<>());
        });

   return ranges::front(results);
}