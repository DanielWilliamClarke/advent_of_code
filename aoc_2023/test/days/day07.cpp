#include "gtest/gtest.h"

#include "main/days/07/day_07.h"

TEST(Day07, ValidateDay07_Part1) 
{
    Day07 day07;

    auto input = day07.readInput();
    EXPECT_EQ(day07.part1(input), 248812215);
}

TEST(Day07, ValidateDay07_Part2) 
{
    Day07 day07;

    auto input = day07.readInput();
    EXPECT_EQ(day07.part2(input), 250057090);
}