#include "gtest/gtest.h"

#include "main/days/09/day_09.h"

TEST(Day09, ValidateDay09_Part1) 
{
    Day09 day09;

    auto input = day09.readInput();
    EXPECT_EQ(day09.part1(input), 1916822650);
}

TEST(Day09, ValidateDay09_Part2) 
{
    Day09 day09;

    auto input = day09.readInput();
    EXPECT_EQ(day09.part2(input), 0);
}