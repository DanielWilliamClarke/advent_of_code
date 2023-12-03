#include "day_03.h"

#include <numeric>
#include <ranges>
#include <iterator>

void captureEnginePart(
    const std::vector<std::string>& input,
    const std::shared_ptr<Candidate>& candidate,
    const Coordinate& coordinate,
    const int maxX
)
{
    auto current = input[coordinate.y][coordinate.x];

    if (std::isdigit(current))
    {
        if (candidate->number.empty())
        {
            candidate->start = coordinate;
        }

        candidate->end = coordinate;
        candidate->number.push_back(current);
    }

    if (
        !candidate->number.empty() &&
        (
            !std::isdigit(current) ||
            coordinate.x >= maxX
        )
    )
    {
        candidate->closed = true;
    }
}

bool validateEnginePart(const std::vector<std::string>& input, const std::shared_ptr<Candidate>& candidate)
{
    // Bounds checking
    auto startX = candidate->start.x - 1;
    if (startX < 0)
    {
        startX = candidate->start.x;
    }
    auto endX = candidate->end.x + 1;
    if (endX >= input[0].size())
    {
        endX = candidate->end.x;
    }

    auto startY = candidate->start.y - 1;
    if (startY < 0)
    {
        startY = candidate->start.y;
    }
    auto endY = candidate->end.y + 1;
    if (endY >= input.size())
    {
        endY = candidate->end.y;
    }

    // Ensure that candidate is adjacent to an engine part symbol
    for (auto y = startY; y <= endY; y++)
    {
        for (auto x = startX; x <= endX; x++)
        {
            auto current = input[y][x];

            if (current == '.' || std::isdigit(current))
            {
                continue;
            }

            return true;
        }
    }

    return false;
}

bool isAdjacentTo(const std::shared_ptr<Candidate>& candidate, int gearX, int gearY)
{
    auto startX = candidate->start.x - 1;
    auto endX = candidate->end.x + 1;
    auto startY = candidate->start.y - 1;
    auto endY = candidate->end.y + 1;

    return (
        gearX >= startX && gearX <= endX &&
        gearY >= startY && gearY <= endY
    );
}

int calculateGearRatio(const std::vector<std::string>& input, int x, int y)
{
    // Construct search space
    auto startX = x - 3;
    if (startX < 0)
    {
        startX = x;
    }
    auto endX = x + 3;
    if (endX >= input[0].size())
    {
        endX = x;
    }

    auto startY = y - 1;
    if (startY < 0)
    {
        startY = y;
    }
    auto endY = y + 1;
    if (endY >= input.size())
    {
        endY = y;
    }

    std::vector<std::shared_ptr<Candidate>> candidates = { std::make_shared<Candidate>() } ;

    // Search and capture all candidates in space
    for (auto yi = startY; yi <= endY; yi++)
    {
        for (auto xi = startX; xi <= endX; xi++)
        {
            if(candidates.back()->closed)
            {
                candidates.emplace_back(std::make_shared<Candidate>());
            }

            captureEnginePart(
                input,
                candidates.back(),
                Coordinate(xi, yi),
                endX
            );
        }
    }

    // filter all that are not adjacent or empty
    auto filtered = candidates
        | std::views::filter( [&x, &y](const std::shared_ptr<Candidate>& c) {
            return !c->number.empty() && isAdjacentTo(c, x, y);
        })
        | std::views::transform([=](const std::shared_ptr<Candidate>& c) {
            return std::stoi(c->number);
        });

    // if only a single element is present then return 0
    if (std::ranges::distance(filtered) < 2)
    {
        return 0;
    }

    // multiple all elements
    std::vector<int> gears = { filtered.begin(), filtered.end() };
    return std::accumulate(
        gears.begin(),
        gears.end(),
        1,
        std::multiplies<>()
    );
}

constexpr std::string Day03::filename () const
{
    return "main/days/03/input.txt";
}

int Day03::part1(const std::vector<std::string>& input) const
{
    auto sum = 0;
    std::vector<std::shared_ptr<Candidate>> candidates = { std::make_shared<Candidate>() } ;

    for(auto y = 0; y < input.size(); y++)
    {
        for(auto x = 0; x < input[y].size(); x++)
        {
            if(candidates.back()->closed)
            {
                candidates.emplace_back(std::make_shared<Candidate>());
            }

            auto candidate = candidates.back();

            captureEnginePart(
                input,
                candidate,
                Coordinate(x, y),
                input[y].size() - 1
            );

            if(candidate->closed && validateEnginePart(input, candidate))
            {
                sum += std::stoi(candidate->number);
            }
        }
    }

    return sum;
}

int Day03::part2(const std::vector<std::string>& input) const
{
    auto sum = 0;

    for(auto y = 0; y < input.size(); y++)
    {
        for (auto x = 0; x < input[y].size(); x++)
        {
            if (input[y][x] == '*')
            {
                sum += calculateGearRatio(input, x, y);
            }
        }
    }

    return sum;
}