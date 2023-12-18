#include "gtest/gtest.h"

#include "main/days/17/day_17.h"

TEST(Day17, ValidateDay17_Part1)
{
    Day17 day17;

    auto input = day17.readInput();
    EXPECT_EQ(day17.part1(input), 674);
}

TEST(Day17, ValidateDay17_Part2)
{
    Day17 day17;

    auto input = day17.readInput();
    EXPECT_EQ(day17.part2(input), 773);
}