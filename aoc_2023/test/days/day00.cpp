#include "gtest/gtest.h"

#include "src/solution/printer.h"
#include "src/days/00/day_00.h"

TEST(Day00, ValidateDay00) 
{
    Day00 day00;

    auto input = day00.readInput();
    EXPECT_EQ(day00.part1(input), 0);
    EXPECT_EQ(day00.part1(input), 0);
}