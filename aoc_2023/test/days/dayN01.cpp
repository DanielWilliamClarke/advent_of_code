#include "gtest/gtest.h"

#include "main/days/N01/day_N01.h"

TEST(DayN01, ValidateDayN01_Part1)
{
    DayN01 dayN01;

    auto input = dayN01.readInput();
    EXPECT_EQ(dayN01.part1(input), 618144);
}

TEST(DayN01, ValidateDayN01_Part2)
{
    DayN01 dayN01;

    auto input = dayN01.readInput();
    EXPECT_EQ(dayN01.part2(input), 173538720);
}