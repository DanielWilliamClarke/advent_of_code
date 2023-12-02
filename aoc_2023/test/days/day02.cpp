#include "gtest/gtest.h"

#include "main/days/02/day_02.h"

TEST(Day02_Utils, CanExtractANumber) {
    auto input = "Game 1";

    auto id = extractNumber(input);

    EXPECT_EQ(id, 1);
}

TEST(Day02_Utils, CanParseHandful) {
    auto input = "5 green, 6 blue, 1 red";

    auto handfuls = parseHandfuls(input);

    for(auto handful : handfuls) {
        EXPECT_EQ(handful.red, 1);
        EXPECT_EQ(handful.blue, 6);
        EXPECT_EQ(handful.green, 5);
    }
}

TEST(Day02_Utils, CanParseMultipleHandfuls) {
    auto input = "1 green, 2 blue, 3 red; 4 blue, 12 red, 800 green";

    auto handfuls = parseHandfuls(input);

    EXPECT_EQ(handfuls[0].green, 1);
    EXPECT_EQ(handfuls[0].blue, 2);
    EXPECT_EQ(handfuls[0].red, 3);

    EXPECT_EQ(handfuls[1].green, 800);
    EXPECT_EQ(handfuls[1].blue, 4);
    EXPECT_EQ(handfuls[1].red, 12);
}

TEST(Day02_Utils, CanParseGame) {
    auto input = "Game 1: 8 green; 5 green, 6 blue, 1 red; 2 green, 1 blue, 4 red; 10 green, 1 red, 2 blue; 2 blue, 3 red";

    auto game = parseGameString(input);

    EXPECT_EQ(game.id, 1);
    EXPECT_EQ(game.handfuls.size(), 5);
}

TEST(Day02, ValidateDay02_Part1)
{
    Day02 day02;

    auto input = day02.readInput();
    EXPECT_EQ(day02.part1(input), 2149);
}

TEST(Day02, ValidateDay02_Part2)
{
    Day02 day02;

    auto input = day02.readInput();
    EXPECT_EQ(day02.part2(input), 71274);
}