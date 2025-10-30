const std = @import("std");
const validate = @import("../util/validate.zig");
const Day = @import("../util/day.zig").Day;

const Day01Impl = struct {
    pub const input_path = "inputs/day00.txt";
    pub const example_path = "inputs/day00_example.txt";

    pub fn part1(_: []const []const u8) !i64 {
        return 0;
    }

    pub fn part2(_: []const []const u8) !i64 {
        return 0;
    }
};

pub const day01 = Day{
    .input_path = Day01Impl.input_path,
    .part1 = Day01Impl.part1,
    .part2 = Day01Impl.part2,
};

test "day01 example" {
    try validate.validate(Day.example_path, Day.part1, 0);
}

test "day01 part1" {
    try validate.validate(Day.input_path, Day.part1, 0);
}

test "day01 part2" {
    try validate.validate(Day.input_path, Day.part2, 0);
}
