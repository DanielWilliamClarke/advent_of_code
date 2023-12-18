#include "day_17.h"

#include <ranges>
#include <set>

#define RED_COLOR "\033[31m"
#define GRAY_COLOR "\033[38;5;8m"
#define RESET_COLOR "\033[0m"

day17::CityBlocks day17::parseCityBlocks(const std::vector<std::string>& input)
{
    auto blocks = input
        | std::views::transform([=](const std::string& line) -> std::vector<int> {
            auto row = line
                | std::views::transform([=](const char& block) -> int {
                    return block - 0x30;
                });

            return { row.begin(), row.end() };
        });

    return { blocks.begin(), blocks.end() };
}

bool day17::withinBounds(const day17::CityBlocks& blocks, const day17::Position& position)
{
    return (
        position.second >= 0 &&
        position.second < blocks.size() &&
        position.first >= 0 &&
        position.first < blocks[0].size()
    );
}

day17::QueueState day17::dijkstraBlocks(
    const day17::CityBlocks& blocks,
    const day17::Position& start,
    const day17::Position& end
)
{
    std::vector<Direction> directions = {
        { 0, 1 }, // down
        { 1, 0 }, // right
        { 0, -1 }, // up
        { -1, 0 },  // left
    };

    std::set<std::tuple<int, int, int, int, int>> seen;
    day17::PriorityQueue pq;

    pq.push({0, start, { 0, 0 }, 0, {}});

    while(!pq.empty())
    {
        // extract top queue data
        auto state =  pq.top();
        pq.pop();

        auto currentHeatLoss = state.heatLoss;
        auto currentPosition = state.position;
        auto currentDirection =state.direction;
        auto currentSteps = state.steps;
        auto currentPath = state.path;

        // if destination reached jump out of this loop
        if (currentPosition == end)
        {
            return state;
        }

        // if this distance is greater than the previous then go to the next queued element
        if (
            seen.count({
                currentPosition.first,
                currentPosition.second,
                currentDirection.first,
                currentDirection.second,
                currentSteps
            })
        )
        {
            continue;
        }

        seen.insert({
            currentPosition.first,
            currentPosition.second,
            currentDirection.first,
            currentDirection.second,
            currentSteps
        });

        if(
            currentSteps < 3 &&
            (currentDirection.first != 0 || currentDirection.second != 0)
        )
        {
            Position newPosition = {
                currentPosition.first + currentDirection.first,
                currentPosition.second + currentDirection.second
            };

            if (day17::withinBounds(blocks, newPosition))
            {
                auto newPath = currentPath;
                newPath.push_back(newPosition);

                pq.push({
                    currentHeatLoss + blocks[newPosition.second][newPosition.first],
                    newPosition,
                    currentDirection,
                    currentSteps + 1,
                    newPath
                });
            }
        }

        // explore neighbours
        for (const auto& dir : directions)
        {
            if (
                (dir.first != currentDirection.first || dir.second != currentDirection.second) &&
                (dir.first != -currentDirection.first || dir.second != -currentDirection.second)
            )
            {
                Position newPosition = {
                    currentPosition.first + dir.first,
                    currentPosition.second + dir.second
                };

                if (day17::withinBounds(blocks, newPosition))
                {
                    auto newPath = currentPath;
                    newPath.push_back(newPosition);

                    pq.push({
                        currentHeatLoss + blocks[newPosition.second][newPosition.first],
                        newPosition,
                        dir,
                        1,
                        newPath
                    });
                }
            }
        }
    }

    return {};
};

void day17::drawPath(
    const day17::CityBlocks& blocks,
    const std::vector<Position>& path
)
{
    for(auto y = 0; y < blocks.size(); y++)
    {
        for (auto x = 0; x < blocks[0].size(); x++)
        {
            auto pathIter = std::ranges::find_if(
                path,
                [&x, &y] (const Position& p) {
                    return p.first == x && p.second == y;
                });

            if (pathIter != path.end())
            {
                std::cout << RED_COLOR;
            }
            else
            {
                std::cout << GRAY_COLOR;
            }

            std::cout << blocks[y][x] << RESET_COLOR;
        }

        std::cout << std::endl;
    }
}

constexpr std::string Day17::filename () const 
{
    return "main/days/17/input.txt";
}

int Day17::part1(const std::vector<std::string>& input) const
{
    auto blocks = day17::parseCityBlocks(input);

    day17::Position start {0, 0};
    day17::Position end {blocks.back().size() - 1, blocks.size() - 1};

    auto state = day17::dijkstraBlocks(blocks, start, end);
    day17::drawPath(blocks, state.path);

    return state.heatLoss;
}

int Day17::part2(const std::vector<std::string>& input) const 
{
    return 0;
}