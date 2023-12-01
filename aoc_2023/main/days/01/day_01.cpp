#include "day_01.h"

#include <ranges>
#include <numeric>

constexpr std::string Day01::filename () const
{
    return "main/days/01/input.txt";
}

int Day01::part1(const std::vector<std::string>& input) const
{
    return std::transform_reduce(
        input.cbegin(),
        input.cend(),
        0,
        std::plus<>(),
        [=](const std::string& code) -> int {
            auto numbers = std::views::filter(code, [=] (unsigned char c) {
                return std::isdigit(c);
            });

            const auto first = numbers.front() - 0x30;
            const auto last = numbers.back() - 0x30;

            return first * 10 + last;
        });
}

int Day01::part2(const std::vector<std::string>& input) const
{
    return 0;
}