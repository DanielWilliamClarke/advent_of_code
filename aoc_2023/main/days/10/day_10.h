#ifndef DAY_10_H
#define DAY_10_H

#include "main/solution/day.h"

//| is a vertical pipe connecting north and south.
//- is a horizontal pipe connecting east and west.
//L is a 90-degree bend connecting north and east.
//J is a 90-degree bend connecting north and west.
//7 is a 90-degree bend connecting south and west.
//F is a 90-degree bend connecting south and east.
//. is ground; there is no pipe in this tile.
//S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
enum PipeType {
    UP_DOWN = '|',
    LEFT_RIGHT = '-',
    DOWN_RIGHT = 'L',
    DOWN_LEFT = 'J',
    UP_LEFT = '7',
    UP_RIGHT = 'F',
    GROUND = '.',
    START = 'S'
};

struct PipeCoordinate {
    int x;
    int y;

    PipeCoordinate(int x, int y)
        : x(x), y(y)
    {}
};

struct Movement {
    int x;
    int y;

    Movement(int x, int y)
        : x(x), y(y)
    {}

    bool operator == (const Movement& other) const noexcept
    {
        return this->x == other.x && this->y == other.y;
    }
};

struct Pipe {
    PipeType type;
    PipeCoordinate coordinate;
    std::vector<Movement> canEnterBy;
    std::vector<Movement> cannotExitBy;
    bool visited;

    Pipe(PipeType type, PipeCoordinate coordinate, std::vector<Movement> canEnterBy, std::vector<Movement> cannotExitBy)
        : type(type), coordinate(coordinate), canEnterBy(canEnterBy), cannotExitBy(cannotExitBy)
    {}
};

std::vector<std::vector<std::shared_ptr<Pipe>>> parsePipeGrid (const std::vector<std::string>& input);
std::pair<int, int> findStartPoint(const std::vector<std::vector<std::shared_ptr<Pipe>>>& grid);
std::vector<std::shared_ptr<Pipe>> findPipeLoopFurthestPoint(std::pair<int, int> startPoint, const std::vector<std::vector<std::shared_ptr<Pipe>>>& grid);

int findEnclosedArea(const std::vector<std::vector<std::shared_ptr<Pipe>>>& grid);

class Day10 : public Day<int>
{
public:
    virtual ~Day10() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_10_H