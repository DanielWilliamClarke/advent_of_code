#include "gtest/gtest.h"

#include "main/days/12/day_12.h"

TEST(Day12, ValidateDay12_Part1)
{
    Day12 day12;

    auto input = day12.readInput();
    EXPECT_EQ(day12.part1(input), 7221);
}

TEST(Day12, ValidateDay12_Part2)
{
    Day12 day12;

    auto input = day12.readInput();
    EXPECT_EQ(day12.part2(input), 7139671893722);
}