#include "gtest/gtest.h"

#include "main/days/18/day_18.h"

TEST(Day18, ValidateDay18_Part1)
{
    Day18 day18;

    auto input = day18.readInput();
    EXPECT_EQ(day18.part1(input), 0);
}

TEST(Day18, ValidateDay18_Part2)
{
    Day18 day18;

    auto input = day18.readInput();
    EXPECT_EQ(day18.part2(input), 0);
}