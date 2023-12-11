#include "day_10.h"

#include <ranges>
#include <cmath>

std::vector<std::vector<std::unique_ptr<Pipe>>> parsePipeGrid (const std::vector<std::string>& input)
{
    Movement up{ 0, -1 };
    Movement right{ 1, 0 };
    Movement down{ 0, 1 };
    Movement left{ -1, 0 };

    auto grid = input
        | std::views::transform([=](const std::string& line) -> std::vector<std::unique_ptr<Pipe>> {
            auto gridLine = line
                | std::views::transform([=](const char pipe) -> std::unique_ptr<Pipe> {
                    // we should have code to know if the pipe is being entered from either side
                    switch (pipe)
                    {
                        // can be traversed each way cases
                        case '|': return std::make_unique<Pipe>(
                            Pipe(
                                PipeType::UP_DOWN,
                                { up, down },
                                { left, right }
                            )
                        );
                        case '-': return std::make_unique<Pipe>(
                            Pipe(
                            PipeType::LEFT_RIGHT,
                            { left, right },
                            { up, down }
                            )
                        );
                        // directive case
                        case 'L': return std::make_unique<Pipe>(
                            Pipe(
                                PipeType::DOWN_RIGHT,
                                { down, left },
                                { down, left }
                            )
                        );
                        case 'J': return std::make_unique<Pipe>(
                            Pipe(
                                PipeType::DOWN_LEFT,
                                { down, right },
                                { down, right }
                            )
                        );
                        case '7': return std::make_unique<Pipe>(
                            Pipe(
                                PipeType::UP_LEFT,
                                { up, right },
                                { up, right }
                            )
                        );
                        case 'F': return std::make_unique<Pipe>(
                            Pipe(
                                PipeType::UP_RIGHT,
                                { up, left },
                                { up, left }
                            )
                        );
                        // special cases
                        case '.': return std::make_unique<Pipe>(
                            Pipe(
                                PipeType::GROUND,
                                { }, { }
                            )
                        );
                        case 'S': return std::make_unique<Pipe>(
                            Pipe(
                                PipeType::START,
                                { up, right, down, left },
                                { }
                            )
                        );
                        // should not happen
                        default: exit(1);
                    }
                });

            return { gridLine.begin(), gridLine.end() };
        });

    return { grid.begin(), grid.end() };
}

std::pair<int, int> findStartPoint(const std::vector<std::vector<std::unique_ptr<Pipe>>>& grid)
{
    for(auto y = 0; y < grid.size(); y++)
    {
        for(auto x = 0; x < grid[y].size(); x++)
        {
            if (grid[y][x]->type == PipeType::START)
            {
                return std::make_pair(x, y);
            }
        }
    }

    return std::make_pair(0, 0);
}

int findPipeLoopFurthestPoint(std::pair<int, int> startPoint, const std::vector<std::vector<std::unique_ptr<Pipe>>>& grid)
{
    // so check around start point and find movement
    std::vector<Movement> movements = {
        { 1, 0 }, // right
        { 0, -1 }, // up
        { -1, 0 }, // left
        { 0, 1 },  // down
    };

    int steps = 0;
    bool loopClosed = false;
    auto currentPoint = startPoint;

//    auto start = grid[startPoint.second][startPoint.first];
//    std::cout
//        << steps << ": "
//        << std::string(1, start->type)
//        << " (" << startPoint.first + 1 << ", " << startPoint.second + 1 << ")"
//        << std::endl;

    while (!loopClosed)
    {
        for(auto movement: movements)
        {
            const auto& current = grid[currentPoint.second][currentPoint.first];
            // block illegal move for the current pipe
            auto cannotExit = std::ranges::any_of(
                current->cannotExitBy,
                [&movement] (const Movement& direction) {
                    return movement == direction;
                });

            if (cannotExit) {
                continue;
            }

            auto nextX = currentPoint.first + movement.x;
            auto nextY = currentPoint.second + movement.y;

            // bounds check
            if (
                nextX < 0 ||
                nextX >= grid[0].size() ||
                nextY < 0 ||
                nextY >= grid.size()
            ) {
                continue;
            }

            const auto& next = grid[nextY][nextX];

            if (next->visited) {
                continue;
            }

            auto canEnter = std::ranges::any_of(
                    next->canEnterBy,
                [&movement] (const Movement& direction) {
                        return movement == direction;
                    });

            if (canEnter)
            {
//                std::cout
//                    << steps + 1 << ": "
//                    << std::string(1, nextPipe->type)
//                    << " (" << nextX + 1 << ", " << nextY + 1 << ")"
//                    << std::endl;

                next->visited = true;
                currentPoint = std::make_pair(nextX, nextY);

                break;
            }
        }

        steps += 1;

        if (currentPoint == startPoint) {
            loopClosed = true;
        }
    }

    return std::ceil(steps / 2);
}

constexpr std::string Day10::filename () const 
{
    return "main/days/10/input.txt";
}

int Day10::part1(const std::vector<std::string>& input) const
{
    auto grid = parsePipeGrid(input);

    auto startPoint = findStartPoint(grid);

    return findPipeLoopFurthestPoint(startPoint, grid);
}

int Day10::part2(const std::vector<std::string>& input) const 
{
    return 0;
}