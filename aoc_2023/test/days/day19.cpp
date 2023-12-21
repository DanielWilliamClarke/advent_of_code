#include "gtest/gtest.h"

#include "main/days/19/day_19.h"

TEST(Day19, ValidateDay19_Part1)
{
    Day19 day19;

    auto input = day19.readInput();
    EXPECT_EQ(day19.part1(input), 432427);
}

TEST(Day19, ValidateDay19_Part2)
{
    Day19 day19;

    auto input = day19.readInput();
    EXPECT_EQ(day19.part2(input), 143760172569135);
}