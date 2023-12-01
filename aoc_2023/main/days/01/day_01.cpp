#include "day_01.h"

#include <range/v3/all.hpp>

constexpr std::string Day01::filename () const
{
    return "main/days/01/input.txt";
}

int Day01::part1(const std::vector<std::string>& input) const
{
    auto calibrations = ranges::views::transform(input,[=](const std::string& code) -> int {
        auto numbers = ranges::views::filter(code, [=] (unsigned char c) {
            return std::isdigit(c);
        });

        auto first = std::to_string(ranges::front(numbers) - '0');
        auto last = std::to_string(ranges::back(numbers) - '0');

        return std::stoi(first + last);
    });

    return ranges::accumulate(calibrations, 0, std::plus<>());
}

int Day01::part2(const std::vector<std::string>& input) const
{
    return 0;
}