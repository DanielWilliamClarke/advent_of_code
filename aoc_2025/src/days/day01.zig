const std = @import("std");
const runner = @import("../util/run.zig");
const validate = @import("../util/validate.zig");

pub const Day = struct {
    pub const number: u8 = 1;
    pub const input_path = "inputs/day01.txt";
    pub const example_path = "inputs/day01_example.txt";

    pub fn part1(_: [][]const u8) !i64 {
        return 0;
    }

    pub fn part2(_: [][]const u8) !i64 {
        return 0;
    }

    pub fn run(alloc: std.mem.Allocator) !void {
        const Self = @This();
        try runner.runParts(alloc, Self.input_path, Self.part1, Self.part2);
    }
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
