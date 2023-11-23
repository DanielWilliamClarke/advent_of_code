#include <memory>

#include "gtest/gtest.h"

#include "solution/printer.h"
#include "days/00/day_00.h"

TEST(Day00, ValidateDay00) {
    Day00 day00(std::make_unique<SolutionPrinter<int>>());
    
    auto input = day00.readInput();
    EXPECT_EQ(day00.part1(input), 0);
    EXPECT_EQ(day00.part1(input), 0);
}