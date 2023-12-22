#include "gtest/gtest.h"

#include "main/days/20/day_20.h"

TEST(Day20, ValidateDay20_Part1)
{
    Day20 day20;

    auto input = day20.readInput();
    EXPECT_EQ(day20.part1(input), 0);
}

TEST(Day20, ValidateDay20_Part2)
{
    Day20 day20;

    auto input = day20.readInput();
    EXPECT_EQ(day20.part2(input), 0);
}