const std = @import("std");
const validate = @import("../util/validate.zig");
const day = @import("../util/day.zig");

pub const day00 = day.fromImpl(struct {
    pub const input_path = "inputs/day00.txt";
    pub const example_path = "inputs/day00_example.txt";

    // Part 1: Solve the first puzzle (this is a placeholder example)
    // Input: lines is a slice of strings read from input file
    // The ! means this function can return an error
    pub fn part1(lines: []const []const u8) !i64 {
        var sum: i64 = 0;
        for (lines) |line| {
            if (line.len == 0) continue;
            sum += try std.fmt.parseInt(i64, line, 10);
        }
        return sum;
    }

    // Part 2: Solve the second puzzle
    pub fn part2(lines: []const []const u8) !i64 {
        var sum: i64 = 0;
        for (lines) |line| {
            if (line.len == 0) continue;
            const v = try std.fmt.parseInt(i64, line, 10);
            sum += v * 2; // pretend Part 2 rule
        }
        return sum;
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
