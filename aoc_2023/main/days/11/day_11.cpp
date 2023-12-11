#include "day_11.h"

#include <ranges>
#include <numeric>

std::vector<std::vector<Space>> parseUniverse(const std::vector<std::string>& input)
{
    auto universe = input
         | std::views::transform([=] (const std::string& line) -> std::vector<Space> {
             auto scan = line
                | std::views::transform([=](const char& c) -> Space {
                    switch(c)
                    {
                        case '#': return Space::GALAXY;
                        case '.': return Space::EMPTY;
                        default: exit(1);
                    };
                });

             return { scan.begin(), scan.end() };
         });

    return { universe.begin(), universe.end() };
}

std::vector<std::vector<Space>> applyDarkEnergy(const std::vector<std::vector<Space>>& universe)
{
    std::vector<int> columns;
    std::vector<int> rows;

    // Define voids
    for(auto y = 0; y < universe.size(); y++)
    {
        // move in x
        if (
            std::ranges::all_of(universe[y], [=](const Space& s) { return s == Space::EMPTY; })
        )
        {
            rows.insert(rows.begin(), y);
        }
    }

    for(auto x = 0; x < universe[x].size(); x++)
    {
        auto isEmpty = true;

        for(auto y = 0; y < universe[x].size(); y++)
        {
            if (universe[y][x] == Space::GALAXY) {
                isEmpty = false;
                break;
            }
        }

        if (isEmpty) {
            columns.insert(columns.begin(), x);
        }
    }

    // Apply dark energy
    auto expandedUniverse = universe;

    // Expand columns
    for(auto columnIndex : columns)
    {
        for(auto y = 0; y < expandedUniverse[y].size(); y++)
        {
            expandedUniverse[y].insert(
                expandedUniverse[y].begin() + columnIndex,
                Space::EMPTY
            );
        }
    }

    // expand rows
    for(auto rowIndex : rows)
    {
        auto row = expandedUniverse.at(rowIndex);

        expandedUniverse.insert(
            expandedUniverse.begin() + rowIndex,
            row
        );
    }

    return expandedUniverse;
}

std::vector<SpacialCoordinates> observeUniverse(const std::vector<std::vector<Space>>& universe) {
    std::vector<SpacialCoordinates> observations;

    for (auto y = 0; y < universe.size(); y++)
    {
        for (auto x = 0; x < universe[y].size(); x++)
        {
            if (universe[y][x] == Space::GALAXY)
            {
                observations.emplace_back(x, y);
            }
        }
    }

    return observations;
}

std::vector<int> analyzeDistances(const std::vector<SpacialCoordinates>& observations)
{
    // Generate pairs
    std::vector<std::vector<SpacialCoordinates>> pairs;
    std::vector<bool> bitset(observations.size() - 2, false);
    bitset.resize(observations.size(), true);

    do {
        std::vector<SpacialCoordinates> pair;
        for (std::size_t i = 0; i != observations.size(); ++i) {
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

constexpr std::string Day11::filename () const 
{
    return "main/days/11/input.txt";
}

int Day11::part1(const std::vector<std::string>& input) const
{
    std::cout << "Mapping Universe 🧭" << std::endl;
    auto universe = parseUniverse(input);

    std::cout << "Expanding Universe 🌟" << std::endl;
    auto expandedUniverse = applyDarkEnergy(universe);

    std::cout << "Observing Universe 👀" << std::endl;
    auto observations = observeUniverse(expandedUniverse);

    std::cout << "Analyzing Universe 📐" << std::endl;
    auto distances = analyzeDistances(observations);

    std::cout << "Coalescing Universe ✨" << std::endl;
    return std::accumulate(
        distances.begin(),
        distances.end(),
        0,
        std::plus<>()
    );
}

int Day11::part2(const std::vector<std::string>& input) const 
{
    return 0;
}