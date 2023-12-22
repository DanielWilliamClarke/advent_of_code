#include "day_02.h"

#include <ranges>
#include <algorithm>
#include <string>
#include <string_view>
#include <numeric>

#include "main/solution/string_utils.h"

int extractNumber(const std::string &str) {
    auto words = splitString(str, " ");

    if (!words.empty()) {
        return std::stoi(words.back());
    }

    return 0;
}

std::vector<Handful> parseHandfuls(const std::string &str) {
    auto sets = splitString(str, ";")
        | std::views::transform([=](const std::string &set) -> Handful {
            auto colors = splitString(set, ",");

            return std::accumulate(
                colors.begin(),
                colors.end(),
                Handful(),
                [&](Handful acc, const std::string &color) {
                    auto colors = splitString(color, " ");

                    auto amount = std::stoi(colors.front());
                    auto colorName = colors.back();
                    
                    if (colorName == "red") {
                        acc.red = amount;
                    }
                    if (colorName == "blue") {
                        acc.blue = amount;
                    }
                    if (colorName == "green") {
                        acc.green = amount;
                    }

                    return acc;
                });
        });

    return {sets.begin(), sets.end()};
}

//// Game 1: 8 green; 5 green, 6 blue, 1 red; 2 green, 1 blue, 4 red; 10 green, 1 red, 2 blue; 2 blue, 3 red
Game parseGameString(const std::string &str) {
    auto parts = splitString(str, ":");

    Game game(
        extractNumber(parts.front()),
        parseHandfuls(parts.back())
    );

    return game;
}

constexpr std::string Day02::filename() const {
    return "main/days/02/input.txt";
}

int Day02::part1(const std::vector<std::string> &input) const {
    return std::transform_reduce(
        input.begin(),
        input.end(),
        0,
        std::plus<>(),
        [=](const std::string &gameStr) {
            auto game = parseGameString(gameStr);

            auto isValid = std::ranges::all_of(game.handfuls, [=](Handful handful) -> bool {
                return handful.red <= 12 && handful.green <= 13 && handful.blue <= 14;
            });

            if (isValid) {
                return game.id;
            }

            return 0;
        }
    );
}

int Day02::part2(const std::vector<std::string> &input) const {
    return std::transform_reduce(
        input.begin(),
        input.end(),
        0,
        std::plus<>(),
        [=](const std::string &gameStr) {
            auto game = parseGameString(gameStr);

            auto power = std::accumulate(
                game.handfuls.begin(),
                game.handfuls.end(),
                Handful(),
                [&](Handful acc, const Handful &handful) {
                    if (handful.red > acc.red) {
                        acc.red = handful.red;
                    }
                    if (handful.green > acc.green) {
                        acc.green = handful.green;
                    }
                    if (handful.blue > acc.blue) {
                        acc.blue = handful.blue;
                    }

                    return acc;
                });

            return power.red * power.green * power.blue;
        }
    );
}
