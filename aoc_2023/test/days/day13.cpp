#include "gtest/gtest.h"

#include "main/days/13/day_13.h"

TEST(Day13, ValidateDay13_Part1)
{
    Day13 day13;

    auto input = day13.readInput();
    EXPECT_EQ(day13.part1(input), 0);
}

TEST(Day13, ValidateDay13_Part2)
{
    Day13 day13;

    auto input = day13.readInput();
    EXPECT_EQ(day13.part2(input), 0);
}