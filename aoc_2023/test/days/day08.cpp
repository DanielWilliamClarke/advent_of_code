#include "gtest/gtest.h"

#include "main/days/08/day_08.h"

TEST(Day08, ValidateDay08_Part1) 
{
    Day08 day08;

    auto input = day08.readInput();
    EXPECT_EQ(day08.part1(input), 20777);
}

TEST(Day08, ValidateDay08_Part2) 
{
    Day08 day08;

    auto input = day08.readInput();
    EXPECT_EQ(day08.part2(input), 13289612809129);
}