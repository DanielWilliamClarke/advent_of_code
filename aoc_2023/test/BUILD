load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "aoc-2023",
    size = "small",
    srcs = glob(["**/*.cpp"]),
    data = glob(["**/*.txt"]),
    deps = [
        "//main:aoc-2023-days",
        "@gtest//:gtest_main",
    ],
)
