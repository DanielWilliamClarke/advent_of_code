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

std::vector<std::vector<Rocks>> tiltDish(const std::vector<std::vector<Rocks>>& dish)
{
    // for each round rock move it in the tilt direction until it cannot move any further
    auto tiltedDish = dish;

    for (auto y = 1; y < tiltedDish.size(); y++)
    {
        for(auto x = 0; x < tiltedDish[y].size(); x++)
        {
            if (tiltedDish[y][x] != Rocks::ROUND) {
                continue;
            }

            auto limit = -1;
            for (auto newY = y - 1; newY >= limit; newY--)
            {
                if(newY == limit || tiltedDish[newY][x] != Rocks::NONE)
                {
                    // Set old position as empty;
                    tiltedDish[y][x] = Rocks::NONE;
                    // Set new position of round rock
                    // - this is done after setting the space as empty just in case the rock has not moved
                    tiltedDish[newY + 1][x] = Rocks::ROUND;
                    break;
                }
            }
        }
    }

    return tiltedDish;
}

std::vector<std::vector<Rocks>> rotateDish(const std::vector<std::vector<Rocks>>& dish)
{
    std::vector<std::vector<Rocks>> transposedDish;

    //  Transpose
    for(auto x = 0; x < dish[0].size(); x++)
    {
        std::vector<Rocks> row;
        row.reserve(dish.size());

        for(const auto & line : dish)
        {
            row.push_back(line[x]);
        }

        transposedDish.emplace_back(row);
    }

    // reverse columns
    std::ranges::reverse(transposedDish);

    return transposedDish;
}

int scoreAlignment (std::vector<std::vector<Rocks>> dish)
{
    int total = 0;

    for (auto y = 0; y < dish.size(); y++)
    {
        size_t roundStones = std::ranges::count_if(
            dish[y],
            [=](const Rocks& rock) {
                return rock == Rocks::ROUND;
            });

        total += (int)roundStones * (dish.size() - y);
    }

    return total;
}

constexpr std::string Day14::filename () const 
{
    return "main/days/14/input.txt";
}

int Day14::part1(const std::vector<std::string>& input) const
{
    return scoreAlignment(
        tiltDish(
            parseParabolicDish(input)
        )
    );
}

int Day14::part2(const std::vector<std::string>& input) const
{
    auto dish = parseParabolicDish(input);

    DishMemoMap memo;
    int iteration = 0;
    for(;;)
    {
        // rotate the dish N -> W -> S -> E
        // tilt dish
        dish = tiltDish(rotateDish(dish));

        // check memo
        if(memo.count(dish))
        {
            break;
        }

        // no cycle detected add dish to memo;
        memo[dish] = { iteration, scoreAlignment(dish) };
        iteration++;
    }

    auto index = memo[dish].first;
    auto memoIndex = (((4'000'000'000 - index) % (iteration - index)) + index) - 1;

    // now mod 1 billion iterations to find the billionth cycle
    //auto memoIndex = (1'000'000'000 - memo[dish].first) % iteration;

    auto result = std::ranges::find_if(memo, [&](auto& c){
        return c.second.first == memoIndex;
    });

    return result->second.second;
    //101041 x // 105871 x // 98863 // 96386 x
}