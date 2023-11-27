load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "aoc-2023",
    srcs = ["main.cpp"],
    deps = [":aoc-2023-days"],
)

cc_library(
    name = "aoc-2023-days",
    srcs = glob(["**/*.cpp"]),
    hdrs = glob(["**/*.h"]),
    data = glob(["**/*.txt"]),
    deps = ["@range_v3//:range-v3"],
    visibility = ["//visibility:public"]
)