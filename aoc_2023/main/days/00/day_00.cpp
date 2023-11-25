#include "day_00.h"

#include <numeric>
#include <algorithm>
#include <ranges>

#include <range/v3/all.hpp>

constexpr std::string Day00::filename() const
{
    return "main/days/00/input.txt";
}

int Day00::part1(const std::vector<int> &input) const
{
    auto results = input
        | ranges::views::transform([=](auto i) { 
            return std::array{i, 2020 - i};
        })
        | ranges::views::filter([&input](const auto p) {
            return ranges::contains(input, p.back()); 
        })
        | ranges::views::transform([=](auto p) {
            return ranges::accumulate(p, 1, std::multiplies<>());
        });

   return ranges::front(results);
}

int Day00::part2(const std::vector<int> &input) const
{
    auto results = ranges::views::cartesian_product(input, input)
        | ranges::views::transform([=](auto i) { 
            auto [a, b] = i;
            return std::array{a, b, 2020 - a - b};
        })
        | ranges::views::filter([&input](const auto& p) {
            return ranges::contains(input, p.back()); 
        })
        | ranges::views::transform([=](auto p) {
            return ranges::accumulate(p, 1, std::multiplies<>());
        });

   return ranges::front(results);
}