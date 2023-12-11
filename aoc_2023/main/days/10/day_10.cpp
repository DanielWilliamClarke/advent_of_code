#include "day_10.h"

#include <ranges>
#include <cmath>
#include <cassert>

#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"
#define PURPLE_COLOR "\033[35m"

std::vector<std::vector<std::shared_ptr<Pipe>>> parsePipeGrid (const std::vector<std::string>& input)
{
    Movement up{ 0, -1 };
    Movement right{ 1, 0 };
    Movement down{ 0, 1 };
    Movement left{ -1, 0 };

    int x = 0;
    int y = 0;

    auto grid = input
        | std::views::transform([&](const std::string& line) -> std::vector<std::shared_ptr<Pipe>> {
            auto gridLine = line
                | std::views::transform([&](const char pipe) -> std::shared_ptr<Pipe> {
                    // we should have code to know if the pipe is being entered from either side
                    switch (pipe)
                    {
                        // can be traversed each way cases
                        case '|': return std::make_shared<Pipe>(
                            Pipe(
                                PipeType::UP_DOWN,
                                { x, y },
                                { up, down },
                                { left, right }
                            )
                        );
                        case '-': return std::make_shared<Pipe>(
                            Pipe(
                            PipeType::LEFT_RIGHT,
                                { x, y },
                                { left, right },
                                { up, down }
                            )
                        );
                        // directive case
                        case 'L': return std::make_shared<Pipe>(
                            Pipe(
                                PipeType::DOWN_RIGHT,
                                { x, y },
                                { down, left },
                                { down, left }
                            )
                        );
                        case 'J': return std::make_shared<Pipe>(
                            Pipe(
                                PipeType::DOWN_LEFT,
                                { x, y },
                                { down, right },
                                { down, right }
                            )
                        );
                        case '7': return std::make_shared<Pipe>(
                            Pipe(
                                PipeType::UP_LEFT,
                                { x, y },
                                { up, right },
                                { up, right }
                            )
                        );
                        case 'F': return std::make_shared<Pipe>(
                            Pipe(
                                PipeType::UP_RIGHT,
                                { x, y },
                                { up, left },
                                { up, left }
                            )
                        );
                        // special cases
                        case '.': return std::make_shared<Pipe>(
                            Pipe(
                                PipeType::GROUND,
                                { x, y },
                                { },
                                { }
                            )
                        );
                        case 'S': return std::make_shared<Pipe>(
                            Pipe(
                                PipeType::START,
                                { x, y },
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

std::pair<int, int> findStartPoint(const std::vector<std::vector<std::shared_ptr<Pipe>>>& grid)
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

std::vector<std::shared_ptr<Pipe>> findPipeLoopFurthestPoint(std::pair<int, int> startPoint, const std::vector<std::vector<std::shared_ptr<Pipe>>>& grid)
{
    // so check around start point and find movement
    std::vector<Movement> movements = {
        { 1, 0 }, // right
        { 0, -1 }, // up
        { -1, 0 }, // left
        { 0, 1 },  // down
    };

    bool loopClosed = false;
    auto currentPoint = startPoint;

    std::vector<std::shared_ptr<Pipe>> loop;

    while (!loopClosed)
    {
        for(auto movement: movements)
        {
            // block illegal move for the current pipe
            auto current = grid[currentPoint.second][currentPoint.first];
            auto cannotExit = std::ranges::any_of(
                current->cannotExitBy,
                [&movement] (const Movement& direction) {
                    return movement == direction;
                });

            if (cannotExit) {
                continue;
            }

            // Determine next coordinate
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

            auto next = grid[nextY][nextX];
            if (next->visited) {
                continue; // can't backwards
            }

            // can we enter the next pipe from this direction?
            auto canEnter = std::ranges::any_of(
                next->canEnterBy,
                [&movement] (const Movement& direction) {
                    return movement == direction;
                });

            if (canEnter)
            {
                next->visited = true;
                currentPoint = std::make_pair(nextX, nextY);
                loop.push_back(next);

                break;
            }
        }

        if (currentPoint == startPoint) {
            loopClosed = true;
        }
    }

    // close the loop properly
    auto start = grid[startPoint.second][startPoint.first];
    start->visited = true;

    return loop;
}

int findEnclosedArea(const std::vector<std::vector<std::shared_ptr<Pipe>>>& grid)
{
    // ray casting method
    int total = 0;

    // ground out grid accept for loop
    for(const auto& line : grid)
    {
        for(const auto& cell : line)
        {
            if(!cell->visited) {
                cell->type = PipeType::GROUND;
            }
        }
    }

    for(const auto& line : grid)
    {
        for(auto cIter = line.begin(); cIter != line.end(); cIter++)
        {
            if ((*cIter)->visited) {
                std::cout << YELLOW_COLOR << std::string(1, (*cIter)->type) << RESET_COLOR;
                continue;
            }

            auto intersections = std::ranges::count_if(
                cIter,
                line.end(),
                [=] (const std::shared_ptr<Pipe>& cell) -> bool {
                    return (
                        cell->visited && (
                            cell->type == PipeType::UP_DOWN ||
                            cell->type == PipeType::DOWN_LEFT ||
                            cell->type == PipeType::DOWN_RIGHT
                        )
                    );
                }
            );

            if(intersections > 0 && intersections % 2 == 1) {
                total += 1;

                std::cout << RED_COLOR;
            }

            std::cout << std::string(1, (*cIter)->type) << RESET_COLOR;
        }

        std::cout << std::endl;
    }

    return total;
}

constexpr std::string Day10::filename () const 
{
    return "main/days/10/input.txt";
}

int Day10::part1(const std::vector<std::string>& input) const
{
    auto grid = parsePipeGrid(input);
    auto startPoint = findStartPoint(grid);
    auto loop = findPipeLoopFurthestPoint(startPoint, grid);

    for(const auto& line : grid)
    {
        for (const auto &cell: line)
        {
            if (cell->type == PipeType::START)
            {
                std::cout << GREEN_COLOR;
            }
            else if(cell->visited)
            {
                std::cout << PURPLE_COLOR;
            }
            else
            {
                cell->type = PipeType::GROUND;
            }

            std::cout << std::string(1, cell->type) << RESET_COLOR;
        }

        std::cout << std::endl;
    }

    return std::ceil(loop.size() / 2);
}

int Day10::part2(const std::vector<std::string>& input) const 
{
    auto grid = parsePipeGrid(input);
    auto startPoint = findStartPoint(grid);
    auto loop = findPipeLoopFurthestPoint(startPoint, grid);

    // modify S to fill the loop
    // TODO: return to work this out properly
    grid[startPoint.second][startPoint.first]->type = PipeType::UP_DOWN;

    // flood fill time!
    return findEnclosedArea(grid);
}