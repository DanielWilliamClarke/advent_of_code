#ifndef DAY_17_H
#define DAY_17_H

#include <queue>

#include "main/solution/day.h"

namespace day17
{
    using Position = std::pair<int, int>;
    using Direction = std::pair<int, int>;
    using CityBlocks = std::vector<std::vector<int>>;

    struct QueueState
    {
        int heatLoss;
        Position position;
        Direction direction;
        int steps;
        std::vector<Position> path;

        bool operator>(const QueueState& other) const {
            return heatLoss > other.heatLoss;
        }
    };

    using PriorityQueue = std::priority_queue<
        QueueState,
        std::vector<QueueState>,
        std::greater<QueueState>
    >;

    struct Candidate
    {
        int heatLoss;
        Position position;
        std::shared_ptr<Candidate> parent;

        Candidate(int heatLoss, Position position, std::shared_ptr<Candidate> parent)
            : heatLoss(heatLoss), position(position), parent(parent)
        {}
    };

    CityBlocks parseCityBlocks(const std::vector<std::string>& input);
    bool withinBounds(const CityBlocks& blocks, const Position& position);
    QueueState dijkstraBlocks(const CityBlocks& blocks, const Position& start, const Position& end);
    void drawPath(const CityBlocks& blocks, const std::vector<Position>& path);
}

class Day17 : public Day<int>
{
public:
    virtual ~Day17() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_17_H