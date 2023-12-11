#include "gtest/gtest.h"

#include "main/days/11/day_11.h"

TEST(Day11, ValidateDay11_Part1)
{
    Day11 day11;

    auto input = day11.readInput();
    EXPECT_EQ(day11.part1(input), 9724940);
}

TEST(Day11, ValidateDay11_Part2)
{
    Day11 day11;

    auto input = day11.readInput();
    EXPECT_EQ(day11.part2(input), 0);
}