#include "gtest/gtest.h"

#include "main/solution/reader.h"

class TestFileInputReader : public FileInputReader {
public:
    [[nodiscard]] constexpr std::string filename() const override { return "test/solution/input.txt"; };
};

TEST(Solution, CanReadAFileToVector) 
{
    TestFileInputReader reader;

    auto input = reader.readInput();

    EXPECT_EQ(input.size(), 10);
}