#include "gtest/gtest.h"

#include "main/days/03/day_03.h"

TEST(Day03_Utils, canValidateEnginePart)
{
    Candidate candidate;
    candidate.number = "123";

    std::vector<std::string> center = {
        ".....",
        ".123.",
        ".#..."
    };
    candidate.start = Coordinate(1, 1);
    candidate.end = Coordinate(3, 1);
    EXPECT_TRUE(validateEnginePart(center, candidate));

    std::vector<std::string> left = {
        ".$..",
        "123.",
        "...."
    };
    candidate.start = Coordinate(0, 1);
    candidate.end = Coordinate(2, 1);
    EXPECT_TRUE(validateEnginePart(left, candidate));

    std::vector<std::string> right = {
        "....",
        ".123",
        ".%.."
    };
    candidate.start = Coordinate(1, 1);
    candidate.end = Coordinate(3, 1);
    EXPECT_TRUE(validateEnginePart(right, candidate));

    std::vector<std::string> top = {
        ".123.",
        "...#."
    };
    candidate.start = Coordinate(1, 0);
    candidate.end = Coordinate(3, 0);
    EXPECT_TRUE(validateEnginePart(top, candidate));

    std::vector<std::string> bottom = {
        ".#...",
        ".123."
    };
    candidate.start = Coordinate(1, 1);
    candidate.end = Coordinate(3, 1);
    EXPECT_TRUE(validateEnginePart(bottom, candidate));

    std::vector<std::string> topLeft = {
        "123.",
        "...#"
    };
    candidate.start = Coordinate(0, 0);
    candidate.end = Coordinate(2, 0);
    EXPECT_TRUE(validateEnginePart(topLeft, candidate));

    std::vector<std::string> topRight = {
        ".123",
        "...#"
    };
    candidate.start = Coordinate(1, 0);
    candidate.end = Coordinate(3, 0);
    EXPECT_TRUE(validateEnginePart(topRight, candidate));

    std::vector<std::string> bottomLeft = {
        "...#",
        "123."
    };
    candidate.start = Coordinate(0, 1);
    candidate.end = Coordinate(2, 1);
    EXPECT_TRUE(validateEnginePart(bottomLeft, candidate));

    std::vector<std::string> bottomRight = {
        "...#",
        ".123"
    };
    candidate.start = Coordinate(1, 1);
    candidate.end = Coordinate(3, 1);
    EXPECT_TRUE(validateEnginePart(bottomLeft, candidate));
}

TEST(Day03_Utils, canValidateNotEnginePart)
{
    Candidate candidate;
    candidate.number = "123";
    std::vector<std::string> center = {
            ".....",
            ".123.",
            "....."
    };
    candidate.start = Coordinate(1, 1);
    candidate.end = Coordinate(3, 1);
    EXPECT_FALSE(validateEnginePart(center, candidate));

    std::vector<std::string> left = {
            "....",
            "123.",
            "...."
    };
    candidate.start = Coordinate(0, 1);
    candidate.end = Coordinate(2, 1);
    EXPECT_FALSE(validateEnginePart(left, candidate));

    std::vector<std::string> right = {
            "....",
            ".123",
            "...."
    };
    candidate.start = Coordinate(1, 1);
    candidate.end = Coordinate(3, 1);
    EXPECT_FALSE(validateEnginePart(right, candidate));

    std::vector<std::string> top = {
            ".123.",
            "....."
    };
    candidate.start = Coordinate(1, 0);
    candidate.end = Coordinate(3, 0);
    EXPECT_FALSE(validateEnginePart(top, candidate));

    std::vector<std::string> bottom = {
            ".....",
            ".123."
    };
    candidate.start = Coordinate(1, 1);
    candidate.end = Coordinate(3, 1);
    EXPECT_FALSE(validateEnginePart(bottom, candidate));

    std::vector<std::string> topLeft = {
            "123.",
            "...."
    };
    candidate.start = Coordinate(0, 0);
    candidate.end = Coordinate(2, 0);
    EXPECT_FALSE(validateEnginePart(topLeft, candidate));

    std::vector<std::string> topRight = {
            ".123",
            "...."
    };
    candidate.start = Coordinate(1, 0);
    candidate.end = Coordinate(3, 0);
    EXPECT_FALSE(validateEnginePart(topRight, candidate));

    std::vector<std::string> bottomLeft = {
            "....",
            "123."
    };
    candidate.start = Coordinate(0, 1);
    candidate.end = Coordinate(2, 1);
    EXPECT_FALSE(validateEnginePart(bottomLeft, candidate));

    std::vector<std::string> bottomRight = {
            "....",
            ".123"
    };
    candidate.start = Coordinate(1, 1);
    candidate.end = Coordinate(3, 1);
    EXPECT_FALSE(validateEnginePart(bottomLeft, candidate));
}

TEST(Day03_Utils, canValidatePartOnRightEdge)
{
    Candidate candidate;
    candidate.number = "152";
    std::vector<std::string> data = {
            "...........",
            "........152",
            ".......*..."
    };
    candidate.start = Coordinate(8, 1);
    candidate.end = Coordinate(10, 1);
    EXPECT_TRUE(validateEnginePart(data, candidate));
}

TEST(Day03, ValidateDay0_Part1)
{
    Day03 day03;

    auto input = day03.readInput();
    EXPECT_EQ(day03.part1(input), 522726);
}

TEST(Day03, ValidateDay03_Part2)
{
    Day03 day03;

    auto input = day03.readInput();
    EXPECT_EQ(day03.part2(input), 0);
}