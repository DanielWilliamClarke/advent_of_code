#include "string_utils.h"

#include <ranges>

std::vector<std::string> splitString(const std::string &str, char delim) {
    auto words = str
                 | std::views::split(delim)
                 | std::views::transform([=](auto part) {
        return std::string_view(&*part.begin(), std::ranges::distance(part));
    })
                 | std::views::filter([=](auto str) {
        return !str.empty();
    });

    return {words.begin(), words.end()};
}