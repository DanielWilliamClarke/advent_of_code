#include "gtest/gtest.h"

#include "main/days/10/day_10.h"

TEST(Day10, ValidateDay10_Part1) 
{
    Day10 day10;

    auto input = day10.readInput();
    EXPECT_EQ(day10.part1(input), 6786);
}

TEST(Day10, ValidateDay10_Part2) 
{
    Day10 day10;

    auto input = day10.readInput();
    EXPECT_EQ(day10.part2(input), 495);
}