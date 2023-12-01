#include "gtest/gtest.h"

#include "main/days/01/day_01.h"

TEST(Day01, ValidateDay01_Part1) 
{
    Day01 day01;

    auto input = day01.readInput();
    EXPECT_EQ(day01.part1(input), 54561);
}

TEST(Day01, ValidateDay01_Part2) 
{
    Day01 day01;

    auto input = day01.readInput();
    EXPECT_EQ(day01.part2(input), 54076);
}