const std = @import("std");
const runner = @import("../util/run.zig"); // Framework for running both parts with timing
const validate = @import("../util/validate.zig");

// Part 1: Solve the first puzzle (this is a placeholder example)
// Input: lines is a slice of strings read from input file
// The ! means this function can return an error
fn part1(lines: [][]const u8) !i64 {
    var sum: i64 = 0;
    for (lines) |line| {
        if (line.len == 0) continue;
        sum += try std.fmt.parseInt(i64, line, 10);
    }
    return sum;
}

// Part 2: Solve the second puzzle
fn part2(lines: [][]const u8) !i64 {
    var sum: i64 = 0;
    for (lines) |line| {
        if (line.len == 0) continue;
        const v = try std.fmt.parseInt(i64, line, 10);
        sum += v * 2; // pretend Part 2 rule
    }
    return sum;
}

// Public entry point: called from main.zig
// alloc is for memory allocation, input_path is the file to read
pub fn run(alloc: std.mem.Allocator, input_path: []const u8) !void {
    try runner.runParts(alloc, input_path, part1, part2);
}

// ========== Tests ==========

test "day01 example" {
    try validate.validateExample(1, part1, 6);
}

test "day01 part1" {
    try validate.validate(1, part1, 150);
}

test "day01 part2" {
    try validate.validate(1, part2, 300);
}
