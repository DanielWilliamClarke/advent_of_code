#include "gtest/gtest.h"

#include "example/example.h"

TEST(Test, ShouldBeTrue) {
    Example example(true);
	
	EXPECT_TRUE(example.a);
}