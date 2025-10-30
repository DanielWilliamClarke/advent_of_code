const std = @import("std");
const runner = @import("../util/run.zig"); // Framework for running both parts with timing
const validate = @import("../util/validate.zig");

pub const Day = struct {
    pub const number: u8 = 0;
    pub const input_path = "inputs/day00.txt";
    pub const example_path = "inputs/day00_example.txt";

    // Part 1: Solve the first puzzle (this is a placeholder example)
    // Input: lines is a slice of strings read from input file
    // The ! means this function can return an error
    pub fn part1(lines: [][]const u8) !i64 {
        var sum: i64 = 0;
        for (lines) |line| {
            if (line.len == 0) continue;
            sum += try std.fmt.parseInt(i64, line, 10);
        }
        return sum;
    }

    // Part 2: Solve the second puzzle
    pub fn part2(lines: [][]const u8) !i64 {
        var sum: i64 = 0;
        for (lines) |line| {
            if (line.len == 0) continue;
            const v = try std.fmt.parseInt(i64, line, 10);
            sum += v * 2; // pretend Part 2 rule
        }
        return sum;
    }

    // Public entry point: called from main.zig
    // alloc is for memory allocation, input path is defined above
    pub fn run(alloc: std.mem.Allocator) !void {
        const Self = @This();
        try runner.runParts(alloc, Self.input_path, Self.part1, Self.part2);
    }
};

test "day00 example" {
    try validate.validate(Day.example_path, Day.part1, 6);
}

test "day00 part1" {
    try validate.validate(Day.input_path, Day.part1, 150);
}

test "day00 part2" {
    try validate.validate(Day.input_path, Day.part2, 300);
}
