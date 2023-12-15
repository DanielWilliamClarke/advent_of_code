#ifndef DAY_14_H
#define DAY_14_H

#include "main/solution/day.h"

enum Rocks {
    ROUND = 'O',
    CUBE = '#',
    NONE = '.'
};

struct DishMemoHash {
    std::size_t operator () (const std::vector<std::vector<Rocks>> &dish) const {
        std::string rasterizedDish;

        for(const auto& row : dish)
        {
            for (const auto& col : row)
            {
                rasterizedDish += std::string(1, col);
            }
        }

        return std::hash<std::string>{}(rasterizedDish);
    }
};

using DishMemo = std::vector<std::vector<Rocks>>;
using DishMemoPayload = std::pair<int, int>;
using DishMemoMap = std::unordered_map<DishMemo, DishMemoPayload, DishMemoHash>;

std::vector<std::vector<Rocks>> parseParabolicDish(const std::vector<std::string>& input);

std::vector<std::vector<Rocks>> tiltDish(const std::vector<std::vector<Rocks>>& dish);

std::vector<std::vector<Rocks>> rotateDish(const std::vector<std::vector<Rocks>>& dish);

int scoreAlignment (std::vector<std::vector<Rocks>> dish);

class Day14 : public Day<int>
{
public:
    virtual ~Day14() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_14_H