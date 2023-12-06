#include "gtest/gtest.h"

#include "main/days/06/day_06.h"

TEST(Day06, ValidateDay06_Part1) 
{
    Day06 day06;

    auto input = day06.readInput();
    EXPECT_EQ(day06.part1(input), 5133600);
}

TEST(Day06, ValidateDay06_Part2) 
{
    Day06 day06;

    auto input = day06.readInput();
    EXPECT_EQ(day06.part2(input), 40651271);
}