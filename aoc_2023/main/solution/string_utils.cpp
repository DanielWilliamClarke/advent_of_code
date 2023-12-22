#include "string_utils.h"

#include <ranges>

std::vector<std::string> splitString(const std::string &str, const std::string& delim)
{
    // Use ranges to split the string
    auto split_view = str | std::views::split(delim);

    // Convert the split view to a vector of strings
    std::vector<std::string> result;
    for (auto&& chunk : split_view)
    {
        std::string substr{chunk.begin(), chunk.end()};

        if (!substr.empty())
        {
            result.emplace_back(substr);
        }
    }

    return result;
}