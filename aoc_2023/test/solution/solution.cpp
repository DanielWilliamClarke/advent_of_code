#include "gtest/gtest.h"

#include "main/solution/reader.h"

TEST(Solution, CanReadAFileToVector) 
{
    FileInputReader<std::string> reader;

    auto input = reader.readInput("test/solution/input.txt");

    EXPECT_EQ(input.size(), 10);
}