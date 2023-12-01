#include "day_01.h"

#include <ranges>
#include <numeric>
#include <regex>
#include <iterator>
#include <unordered_map>
#include <stdexcept>

const std::regex regex("(one|two|three|four|five|six|seven|eight|nine|[0-9])");
const std::unordered_map<std::string, int> mapping = {
    { "one", 1 },
    { "two", 2 },
    { "three", 3 },
    { "four", 4 },
    { "five", 5 },
    { "six", 6 },
    { "seven", 7 },
    { "eight", 8 },
    { "nine", 9 },
};

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
    return std::transform_reduce(
        input.cbegin(),
        input.cend(),
        0,
        std::plus<>(),
        [=](const std::string& code) -> int {
            auto numbersStart = std::sregex_iterator(code.cbegin(), code.cend(), regex);
            auto numberEnd = std::sregex_iterator();

            auto firstStr = (*numbersStart).str();
            auto first = 0;
            try {
                first = mapping.at(firstStr);
            } catch (const std::out_of_range& e) {
                first = std::stoi(firstStr);
            }

            auto lastStr = firstStr;
            for (auto iter = numbersStart; iter != numberEnd; ++iter) {
                lastStr = (*iter).str();
            }

            auto last = 0;
            try {
                last = mapping.at(lastStr);
            } catch (const std::out_of_range& e) {
                last = std::stoi(lastStr);
            }

            return first * 10 + last;
        });
}