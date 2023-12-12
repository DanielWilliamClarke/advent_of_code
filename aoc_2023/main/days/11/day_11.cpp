#include "day_11.h"

#include <ranges>
#include <numeric>

std::vector<std::vector<SpacialCoordinates>> parseUniverse(const std::vector<std::string>& input)
{
    std::vector<std::vector<SpacialCoordinates>> universe;

    for(auto y = 0; y < input.size(); y++)
    {
        std::vector<SpacialCoordinates> scan;
        scan.reserve(input[y].size());

        for(auto x = 0; x < input[y].size(); x++)
        {
            scan.emplace_back(
                input[y][x] == '#' ? Space::GALAXY : Space::EMPTY,
                 x, y
            );
        }

        universe.push_back(scan);
    }

    return universe;
}

std::vector<std::vector<SpacialCoordinates>> applyDarkEnergy(const std::vector<std::vector<SpacialCoordinates>>& universe, long long factor)
{
    std::vector<int> columns;
    std::vector<int> rows;

    // Define voids
    for(auto y = 0; y < universe.size(); y++)
    {
        // move in x
        if (
            std::ranges::all_of(universe[y], [=](const SpacialCoordinates& s) { return s.type == Space::EMPTY; })
        )
        {
            rows.push_back(y);
        }
    }

    for(auto x = 0; x < universe.size(); x++)
    {
        auto isEmpty = true;

        for(auto y = 0; y < universe[x].size(); y++)
        {
            if (universe[y][x].type == Space::GALAXY) {
                isEmpty = false;
                break;
            }
        }

        if (isEmpty) {
            columns.push_back(x);
        }
    }

    // Apply dark energy
    auto expandedUniverse = universe;

    // expand rows
    for(auto rowIndex : rows)
    {
        for(auto y = rowIndex; y < expandedUniverse.size(); y++)
        {
            for(auto x = 0; x < expandedUniverse[y].size(); x++)
            {
                expandedUniverse[y][x].y += factor;
            }
        }
    }

    // Expand columns
    for(auto columnIndex : columns)
    {
        for(auto y = 0; y < expandedUniverse.size(); y++)
        {
            for(auto x = columnIndex; x < expandedUniverse[y].size(); x++)
            {
                expandedUniverse[y][x].x += factor;
            }
        }
    }

    return expandedUniverse;
}

std::vector<SpacialCoordinates> observeUniverse(const std::vector<std::vector<SpacialCoordinates>>& universe) {
    std::vector<SpacialCoordinates> observations;

    for (const auto & scan : universe)
    {
        for (auto point : scan)
        {
            if (point.type == Space::GALAXY)
            {
                observations.push_back(point);
            }
        }
    }

    return observations;
}

std::vector<long long> analyzeDistances(const std::vector<SpacialCoordinates>& observations)
{
    // Generate pairs
    std::vector<std::vector<SpacialCoordinates>> pairs;
    std::vector<bool> bitset(observations.size() - 2, false);
    bitset.resize(observations.size(), true);

    do {
        std::vector<SpacialCoordinates> pair;
        for (auto i = 0; i != observations.size(); ++i) {
            if (bitset[i]) {
                pair.push_back(observations[i]);
            }
        }
        pairs.push_back(pair);
    } while (std::next_permutation(bitset.begin(), bitset.end()));

    // Calculate distances between pairs
    auto distances = pairs
        | std::views::transform([=](auto& pair) {
            // Manhattan distance
            return std::abs(pair.front().x - pair.back().x) + abs(pair.front().y - pair.back().y);
        });

    return { distances.begin(), distances.end() };
}

long long traverseUniverse(const std::vector<std::string>& input, long long factor)
{
    std::cout << "Mapping Universe 🧭" << std::endl;
    auto universe = parseUniverse(input);

    std::cout << "Expanding Universe 🌟" << std::endl;
    auto expandedUniverse = applyDarkEnergy(universe, factor);

    std::cout << "Observing Universe 👀" << std::endl;
    auto observations = observeUniverse(expandedUniverse);

    std::cout << "Analyzing Universe 📐" << std::endl;
    auto distances = analyzeDistances(observations);

    std::cout << "Coalescing Universe ✨" << std::endl;
    return std::accumulate(
        distances.begin(),
        distances.end(),
        0ll,
        std::plus<>()
    );
}

constexpr std::string Day11::filename () const 
{
    return "main/days/11/input.txt";
}

long long Day11::part1(const std::vector<std::string>& input) const
{
    long long factor = 1;
    return traverseUniverse(input, factor);
}

long long Day11::part2(const std::vector<std::string>& input) const
{
    long long factor = 1e6 - 1;
    return traverseUniverse(input, factor);
}
