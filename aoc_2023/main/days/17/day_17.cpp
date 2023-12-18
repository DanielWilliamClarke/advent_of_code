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

std::shared_ptr<day17::QueueState> day17::dijkstraBlocks(
    const day17::CityBlocks& blocks,
    const day17::Position& start,
    const day17::Position& end,
    int minStraight,
    int maxStraight
)
{
    std::vector<Direction> directions = {
        { 0, 1 }, // down
        { 1, 0 }, // right
        { 0, -1 }, // up
        { -1, 0 },  // left
    };

    Direction startDirection = { 0, 0 };

    SnapShotSet seen;
    day17::PriorityQueue pq;
    pq.push({ 0, start, startDirection, 0, nullptr });

    while(!pq.empty())
    {
        // extract top queue data
        auto currentState = pq.top();
        pq.pop();

        auto currentHeatLoss = currentState.heatLoss;
        auto currentPosition = currentState.position;
        auto currentDirection = currentState.direction;
        auto currentSteps = currentState.steps;

        // if destination reached jump out of this loop
        if (currentPosition == end)
        {
            return std::make_shared<QueueState>(currentState);
        }

        SnapShot snapShot{
            currentPosition.first,
            currentPosition.second,
            currentDirection.first,
            currentDirection.second,
            currentSteps
        };

        // if this distance is greater than the previous then go to the next queued element
        if (seen.count(snapShot)) { continue; }
        seen.insert(snapShot);

        // check in current direction if max steps have not been taken
        if(currentSteps < maxStraight && currentDirection != startDirection)
        {
            Position newPosition = {
                    currentPosition.first + currentDirection.first,
                    currentPosition.second + currentDirection.second
            };

            if (day::withinBounds(blocks, newPosition))
            {
                pq.push({
                    currentHeatLoss + blocks[newPosition.second][newPosition.first],
                    newPosition,
                    currentDirection,
                    currentSteps + 1,
                    std::make_shared<QueueState>(currentState)
                });
            }
        }

        if (currentSteps >= minStraight || currentDirection == startDirection)
        {
            // explore perpendicular neighbours
            for (const auto& dir : directions)
            {
                if (
                    std::abs(dir.first) != std::abs(currentDirection.first) ||
                    std::abs(dir.second) != std::abs(currentDirection.second)
                )
                {
                    Position newPosition = {
                        currentPosition.first + dir.first,
                        currentPosition.second + dir.second
                    };

                    if (day17::withinBounds(blocks, newPosition))
                    {
                        pq.push({
                            currentHeatLoss + blocks[newPosition.second][newPosition.first],
                            newPosition,
                            dir,
                            1,
                            std::make_shared<QueueState>(currentState)
                        });
                    }
                }
            }
        }
    }

    return nullptr;
};

void day17::drawPath(
    const day17::CityBlocks& blocks,
    const std::shared_ptr<QueueState>& state
)
{
    // null check
    if(state == nullptr)
    {
        std::cout << "Heat map not traversed!" << std::endl;
        return;
    }

    // Extract path
    std::vector<Position> path;
    auto s = state;
    while(s != nullptr)
    {
        path.push_back(s->position);
        s = s->parent;
    }

    // Render grid
    for(auto y = 0; y < blocks.size(); y++)
    {
        for (auto x = 0; x < blocks[0].size(); x++)
        {
            auto pathIter = std::ranges::find_if(
                path,
                [&x, &y] (const Position& p) {
                    return p.first == x && p.second == y;
                });

            std::cout
                << (pathIter != path.end() ? RED_COLOR : GRAY_COLOR)
                << blocks[y][x]
                << RESET_COLOR;
        }

        std::cout << std::endl;
    }
}

int calculateHeatLoss(const std::vector<std::string>& input, int minStraight, int maxStraight)
{
    auto blocks = day17::parseCityBlocks(input);

    auto state = day17::dijkstraBlocks(
        blocks,
        {0, 0 },
        { blocks.back().size() - 1, blocks.size() - 1 },
         minStraight,
        maxStraight
    );

    day17::drawPath(blocks, state);

    return state->heatLoss;
}

constexpr std::string Day17::filename () const 
{
    return "main/days/17/input.txt";
}

int Day17::part1(const std::vector<std::string>& input) const
{
    return calculateHeatLoss(input, 0, 3);
}

int Day17::part2(const std::vector<std::string>& input) const 
{
    return calculateHeatLoss(input, 4, 10);
}