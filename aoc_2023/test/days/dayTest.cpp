#include "gtest/gtest.h"

#include "main/days/template/day_00.h"

TEST(Day00, ValidateDay00_Part1)
{
    Day00 day00;

    auto input = day00.readInput();
    EXPECT_EQ(day00.part1(input), 0);
}

TEST(Day00, ValidateDay00_Part2)
{
    Day00 day00;

    auto input = day00.readInput();
    EXPECT_EQ(day00.part2(input), 0);
}