#include "gtest/gtest.h"

#include "main/days/16/day_16.h"

TEST(Day16, ValidateDay16_Part1)
{
    Day16 day16;

    auto input = day16.readInput();
    EXPECT_EQ(day16.part1(input), 0);
}

TEST(Day16, ValidateDay16_Part2)
{
    Day16 day16;

    auto input = day16.readInput();
    EXPECT_EQ(day16.part2(input), 0);
}