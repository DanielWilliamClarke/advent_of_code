#include "gtest/gtest.h"

#include "main/days/14/day_14.h"

TEST(Day14, ValidateDay14_Part1)
{
    Day14 day14;

    auto input = day14.readInput();
    EXPECT_EQ(day14.part1(input), 103333);
}

TEST(Day14, ValidateDay14_Part2)
{
    Day14 day14;

    auto input = day14.readInput();
    EXPECT_EQ(day14.part2(input), 97241);
}