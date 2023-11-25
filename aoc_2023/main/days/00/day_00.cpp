#include "day_00.h"

#include <numeric>
#include <algorithm>
#include <ranges>

#include "main/utils/cartesian_product.h"

constexpr std::string Day00::filename() const
{
    return "main/days/00/input.txt";
}

int Day00::part1(const std::vector<int> &input) const
{
    auto result = input
        | std::views::transform([=](auto i) { return std::array{i, 2020 - i}; })
        | std::views::filter([&input](const auto& p) {
            return std::find(input.begin(), input.end(), p.back()) != input.end();
        })
        | std::views::transform([=](auto&& p) {
            return std::accumulate(p.begin(), p.end(), 1, std::multiplies<>());
        });

    if (auto it = result.begin(); it != result.end()) {
        return *it;
    }
    
    return 0;
}

int Day00::part2(const std::vector<int> &input) const
{
    auto result = cartesian_product(input, input)
        | std::views::transform([=](auto i) { 
            auto [a, b] = i;
            return std::array{a, b, 2020 - a - b};
        })
        | std::views::filter([&input](const auto& p) {
            return std::find(input.begin(), input.end(), p.back()) != input.end();
        })
        | std::views::transform([=](auto&& p) {
            return std::accumulate(p.begin(), p.end(), 1, std::multiplies<>());
        });

    if (auto it = result.begin(); it != result.end()) {
        return *it;
    }
    
    return 0;
}