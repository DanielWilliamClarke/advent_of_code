const std = @import("std");
const validate = @import("../util/validate.zig");
const day = @import("../util/day.zig");

pub const day01 = day.fromImpl(struct {
    pub const input_path = "inputs/day00.txt";
    pub const example_path = "inputs/day00_example.txt";

    pub fn part1(_: []const []const u8) !i64 {
        return 0;
    }

    pub fn part2(_: []const []const u8) !i64 {
        return 0;
    }
});

test "day01 example" {
    try validate.validate(day01.example_path, day01.part1, 0);
}

test "day01 part1" {
    try validate.validate(day01.input_path, day01.part1, 0);
}

test "day01 part2" {
    try validate.validate(day01.input_path, day01.part2, 0);
}
