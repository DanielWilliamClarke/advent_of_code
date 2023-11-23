#include "gtest/gtest.h"

#include "days/00/day_00.h"

TEST(Day00, ValidateDay00) {
    Day00 day00;
    auto input = std::vector<int>{ 1, 2, 3 };

    EXPECT_EQ(day00.part1(input), 0);
    EXPECT_EQ(day00.part1(input), 0);
}