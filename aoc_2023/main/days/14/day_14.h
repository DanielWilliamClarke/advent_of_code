#ifndef DAY_14_H
#define DAY_14_H

#include <map>

#include "main/solution/day.h"

enum Rocks {
    ROUND = 'O',
    CUBE = '#',
    NONE = '.'
};

using DishMemo = std::vector<std::vector<Rocks>>;
using DishMemoPayload = std::pair<int, int>;
using DishMemoMap = std::map<DishMemo, DishMemoPayload>;

std::vector<std::vector<Rocks>> parseParabolicDish(const std::vector<std::string>& input);

void tiltDishNorth(std::vector<std::vector<Rocks>>& dish);
void tiltDishWest(std::vector<std::vector<Rocks>>& dish);
void tiltDishSouth(std::vector<std::vector<Rocks>>& dish);
void tiltDishEast(std::vector<std::vector<Rocks>>& dish);

int calculateNorthLoad (const std::vector<std::vector<Rocks>>& dish);

class Day14 : public Day<int>
{
public:
    virtual ~Day14() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_14_H