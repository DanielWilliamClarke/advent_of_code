#include "gtest/gtest.h"

#include <thread>

#include "main/solution/measurer.h"

TEST(Measurer, CanMeasureAMethodTiming)
{
    Measurer measurer;
    auto data = 0;

    auto [output, timing] = measurer.measure<int>([&data]() -> int {
        using namespace std::chrono_literals;

        std::this_thread::sleep_for(2000ms);

        return data;
    });

    EXPECT_EQ(data, output);
    EXPECT_EQ(std::floor(timing), 2.0f);
}