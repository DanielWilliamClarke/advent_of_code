load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
  name = "aoc-2023-test",
  srcs = glob(["**/*.cpp"]),
  deps = [
    "@com_google_googletest//:gtest_main",
     "//src:aoc-2023-days",
  ],
)