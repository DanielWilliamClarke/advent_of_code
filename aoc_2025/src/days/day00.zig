const std = @import("std");
const validate = @import("../util/validate.zig");
const day = @import("../util/day.zig");

pub const day00 = day.fromImpl(struct {
    pub const input_path = "inputs/day00.txt";
    pub const example_path = "inputs/day00_example.txt";

    pub fn sum(lines: []const []const u8, multiplier: i64) !i64 {
        var acc: i64 = 0;
        for (lines) |line| {
            if (line.len == 0) continue;
            const val = try std.fmt.parseInt(i64, line, 10);
            acc += val * multiplier;
        }
        return acc;
    }

    // Part 1: Solve the first puzzle (this is a placeholder example)
    // Input: lines is a slice of strings read from input file
    // The ! means this function can return an error
    pub fn part1(lines: []const []const u8) !i64 {
        return sum(lines, 1);
    }

    // Part 2: Solve the second puzzle
    pub fn part2(lines: []const []const u8) !i64 {
        return sum(lines, 2);
    }
});

test "day00 example" {
    try validate.validate(day00.example_path, day00.part1, 6);
}

test "day00 part1" {
    try validate.validate(day00.input_path, day00.part1, 150);
}

test "day00 part2" {
    try validate.validate(day00.input_path, day00.part2, 300);
}
