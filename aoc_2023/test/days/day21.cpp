#include "gtest/gtest.h"

#include "main/days/21/day_21.h"

TEST(Day21, ValidateDay21_Part1)
{
    Day21 day21;

    auto input = day21.readInput();
    EXPECT_EQ(day21.part1(input), 0);
}

TEST(Day21, ValidateDay21_Part2)
{
    Day21 day21;

    auto input = day21.readInput();
    EXPECT_EQ(day21.part2(input), 0);
}