#include "day_13.h"

#include <algorithm>
#include <numeric>

std::vector<std::vector<std::string>> parseLandscapes(const std::vector<std::string>& input)
{
    std::vector<std::vector<std::string>> landscapes;

    for(const auto& row : input)
    {
        if (row.empty() || landscapes.empty()) {
            landscapes.emplace_back();
            continue;
        }

        landscapes.back().push_back(row);
    }

    return landscapes;
}

int countInconsistencies(const std::string& rowUp, const std::string& rowDown)
{
    auto total = 0;

    for(auto i = 0; i < rowUp.size(); i++)
    {
        if (rowUp[i] != rowDown[i])
        {
            total += 1;
        }
    }

    return total;
}

std::vector<std::string> flipLandscape(const std::vector<std::string>& landscape)
{
    std::vector<std::string> flippedLandscapes;
    flippedLandscapes.reserve(landscape[0].size());

    for(auto x = 0; x < landscape[0].size(); x++)
    {
        std::string flippedLine;
        for(const auto & line : landscape)
        {
            flippedLine.push_back(line[x]);
        }

        flippedLandscapes.emplace_back(flippedLine);
    }

    return flippedLandscapes;
}

int findReflection(const std::vector<std::string>& landscape, int threshold)
{
    for(auto split = 1; split < landscape.size(); split++)
    {
        int size = std::min(split, int(landscape.size() - split));

        auto inconsistencyCount = 0;
        for(auto i = 0; i < size; i++)
        {
            inconsistencyCount += countInconsistencies(
                landscape[split - i - 1],
                landscape[split + i]
            );
        }

        if (inconsistencyCount == threshold)
        {
            return split;
        }
    }

    return 0;
}

constexpr std::string Day13::filename () const 
{
    return "main/days/13/input.txt";
}

int Day13::part1(const std::vector<std::string>& input) const
{
    auto landscapes = parseLandscapes(input);

    return std::transform_reduce(
        landscapes.begin(),
        landscapes.end(),
        0,
        std::plus<>(),
        [=] (const std::vector<std::string>& l) {
            return (findReflection(l) * 100) + findReflection(flipLandscape(l));
        }
    );
}

int Day13::part2(const std::vector<std::string>& input) const 
{
    auto smudgeThreshold = 1;
    auto landscapes = parseLandscapes(input);

    return std::transform_reduce(
        landscapes.begin(),
        landscapes.end(),
        0,
        std::plus<>(),
        [&smudgeThreshold] (const std::vector<std::string>& l) {
            return (findReflection(l, smudgeThreshold) * 100) +
                findReflection(flipLandscape(l), smudgeThreshold);
        }
    );
}