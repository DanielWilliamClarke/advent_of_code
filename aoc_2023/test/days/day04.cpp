#include "gtest/gtest.h"

#include "main/days/04/day_04.h"

TEST(Day04, ValidateDay04_Part1) 
{
    Day04 day04;

    auto input = day04.readInput();
    EXPECT_EQ(day04.part1(input), 24175);
}

TEST(Day04, ValidateDay04_Part2) 
{
    Day04 day04;

    auto input = day04.readInput();
    EXPECT_EQ(day04.part2(input), 0);
}