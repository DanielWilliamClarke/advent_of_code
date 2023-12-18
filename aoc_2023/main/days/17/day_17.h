#ifndef DAY_17_H
#define DAY_17_H

#include <queue>
#include <set>

#include "main/solution/day.h"

namespace day17
{
    using SnapShot = std::tuple<int, int, int, int, int>;
    using SnapShotSet = std::set<SnapShot>;

    using Position = std::pair<int, int>;
    using Direction = std::pair<int, int>;
    using CityBlocks = std::vector<std::vector<int>>;

    struct QueueState
    {
        int heatLoss;
        Position position;
        Direction direction;
        int steps;
        std::shared_ptr<QueueState> parent;

        bool operator>(const QueueState& other) const {
            return heatLoss > other.heatLoss;
        }
    };

    using PriorityQueue = std::priority_queue<
        QueueState,
        std::vector<QueueState>,
        std::greater<>
    >;

    CityBlocks parseCityBlocks(const std::vector<std::string>& input);
    bool withinBounds(const CityBlocks& blocks, const Position& position);
    std::shared_ptr<QueueState> dijkstraBlocks(const CityBlocks& blocks, const Position& start, const Position& end, int minStraight, int maxStraight);
    void drawPath(const CityBlocks& blocks, const std::shared_ptr<QueueState>& state);
    int calculateHeatLoss(const std::vector<std::string>& input, int minStraight, int maxStraight);
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