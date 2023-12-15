#include "day_14.h"

#include <ranges>
#include <algorithm>

std::vector<std::vector<Rocks>> parseParabolicDish(const std::vector<std::string>& input)
{
    auto dish = input
        | std::views::transform([=] (const std::string& line) -> std::vector<Rocks> {
            auto rocks = line
                | std::views::transform([=] (const char& rock) -> Rocks {
                    switch (rock)
                    {
                        case 'O': return Rocks::ROUND;
                        case '#': return Rocks::CUBE;
                        case '.': return Rocks::NONE;
                        default: exit(1);
                    }
                });

            return { rocks.begin(), rocks.end() };
        });

    return { dish.begin(), dish.end() };
}

void tiltDishNorth(std::vector<std::vector<Rocks>>& dish)
{
    std::vector<int> movement(dish[0].size(), 0 );

    for (auto y = 0; y < dish.size(); ++y)
    {
        for(auto x = 0; x < dish[y].size(); ++x)
        {
            if (dish[y][x] == Rocks::NONE)
            {
                ++movement[x];
                continue;
            }
            if (dish[y][x] == Rocks::CUBE)
            {
                movement[x] = 0;
                continue;
            }

            auto destination_row = y - movement[x];
            if (destination_row != y)
            {
                dish[destination_row][x] = Rocks::ROUND;
                dish[y][x] = Rocks::NONE;
            }
        }
    }
}

void tiltDishWest(std::vector<std::vector<Rocks>>& dish)
{
    for (auto y = 0; y < dish.size(); ++y)
    {
        auto movement = 0;
        for(auto x = 0; x < dish[y].size(); ++x)
        {
            if (dish[y][x] == Rocks::NONE)
            {
                ++movement;
                continue;
            }
            if (dish[y][x] == Rocks::CUBE)
            {
                movement = 0;
                continue;
            }

            auto destination = x - movement;
            if(destination != x)
            {
                dish[y][destination] = Rocks::ROUND;
                dish[y][x] = Rocks::NONE;
            }
        }
    }
}

void tiltDishSouth(std::vector<std::vector<Rocks>>& dish)
{
    std::vector<int> movement( dish[0].size(), 0 );

    for (int y = dish.size() - 1; y >= 0; --y)
    {
        for (auto x = 0; x < dish[y].size(); ++x)
        {
            if (dish[y][x] == Rocks::NONE)
            {
                ++movement[x];
                continue;
            }
            if (dish[y][x] == Rocks::CUBE)
            {
                movement[x] = 0;
                continue;
            }

            auto destination = y + movement[x];
            if (destination != y)
            {
                dish[destination][x] = Rocks::ROUND;
                dish[y][x] = Rocks::NONE;
            }
        }
    }
}

void tiltDishEast(std::vector<std::vector<Rocks>>& dish)
{
    for (auto y = 0; y < dish.size(); ++y)
    {
        auto movement = 0;
        for (int x = dish[y].size() - 1; x >= 0; --x)
        {
            if (dish[y][x] == Rocks::NONE)
            {
                ++movement;
                continue;
            }
            if (dish[y][x] == Rocks::CUBE)
            {
                movement = 0;
                continue;
            }

            auto destination = x + movement;
            if(destination != x)
            {
                dish[y][destination] = Rocks::ROUND;
                dish[y][x] = Rocks::NONE;
            }
        }
    }
}

int calculateNorthLoad (const std::vector<std::vector<Rocks>>& dish)
{
    int total = 0;

    for (auto y = 0; y < dish.size(); y++)
    {
        auto roundStones = std::ranges::count_if(
            dish[y],
            [=](const Rocks& rock) {
                return rock == Rocks::ROUND;
            });

        total += roundStones * (dish.size() - y);
    }

    return total;
}

constexpr std::string Day14::filename () const 
{
    return "main/days/14/input.txt";
}

int Day14::part1(const std::vector<std::string>& input) const
{
    auto dish = parseParabolicDish(input);
    tiltDishNorth(dish);
    return calculateNorthLoad(dish);
}

int Day14::part2(const std::vector<std::string>& input) const
{
    auto dish = parseParabolicDish(input);

    DishMemoMap memo;
    int cycles = 1;
    int lookupIndex = 0;

    while(lookupIndex == 0)
    {
        // SPIN CYCLE
        tiltDishNorth(dish);
        tiltDishWest(dish);
        tiltDishSouth(dish);
        tiltDishEast(dish);

        // Look in memo to see if a cycle has started
        auto result = memo.find(dish);
        if (result != memo.end())
        {
            // Cycle detected
            auto [counter, load]  = result->second;
            auto loopLength = cycles - counter;
            // Calculate what the 1e9nth index would be in this cycle
            lookupIndex = counter + (1'000'000'000 - counter) % loopLength;
            continue;
        }

        // no cycle detected add dish to memo;
        memo[dish] = {cycles, calculateNorthLoad(dish) };
        cycles++;
    }

    // Extract result from the memo
    auto result = std::ranges::find_if(
        memo,
       [&lookupIndex] (auto r) -> int {
            return r.second.first == lookupIndex;
        });

    return result->second.second;
}