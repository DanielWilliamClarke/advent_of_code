#include "gtest/gtest.h"

#include "main/days/05/day_05.h"

TEST(Day05, ValidateDay05_Part1) 
{
    Day05 day05;

    auto input = day05.readInput();
    EXPECT_EQ(day05.part1(input), 278755257);
}

TEST(Day05, ValidateDay05_Part2) 
{
    Day05 day05;

    auto input = day05.readInput();
    EXPECT_EQ(day05.part2(input), 26829166);
}