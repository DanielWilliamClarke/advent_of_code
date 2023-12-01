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

int parseMatch(const std::sregex_iterator& match) {
    auto firstStr = (*match).str();
    try {
        return mapping.at(firstStr);
    } catch (const std::out_of_range& e) {
        return std::stoi(firstStr);
    }
}

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
            auto start = std::sregex_iterator(code.cbegin(), code.cend(), regex);
            auto end = std::sregex_iterator();

            auto lastIter = start;
            for (auto iter = start; iter != end; ++iter) {
                lastIter = iter;
            }

            auto first = parseMatch(start);
            auto last = parseMatch(lastIter);

            return first * 10 + last;
        });
}