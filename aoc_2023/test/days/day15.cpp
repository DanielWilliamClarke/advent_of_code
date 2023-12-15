#include "gtest/gtest.h"

#include "main/days/15/day_15.h"

TEST(Day15, ValidateDay15_Part1)
{
    Day15 day15;

    auto input = day15.readInput();
    EXPECT_EQ(day15.part1(input), 0);
}

TEST(Day15, ValidateDay15_Part2)
{
    Day15 day15;

    auto input = day15.readInput();
    EXPECT_EQ(day15.part2(input), 0);
}