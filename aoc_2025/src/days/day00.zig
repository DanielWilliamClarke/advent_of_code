const std = @import("std");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day00.txt";
pub const example_path = "inputs/day00_example.txt";

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![]const i64 {
    var nums: std.ArrayList(i64) = .empty;
    defer nums.deinit(alloc);

    try nums.ensureTotalCapacityPrecise(alloc, lines.len);

    for (lines) |line| {
        const num = try std.fmt.parseInt(i64, line, 10);
        try nums.append(alloc, num);
    }

    return nums.toOwnedSlice(alloc);
}

// Part 1: Solve the first puzzle (this is a placeholder example)
// Input: lines is a slice of strings read from input file
// The ! means this function can return an error
pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const nums = try parse(alloc, lines);
    defer alloc.free(nums);

    for (nums, 0..) |num1, i| {
        for (nums[i + 1 ..]) |num2| {
            if (num1 + num2 == 2020) return num1 * num2;
        }
    }

    return 0;
}

// Part 2: Solve the second puzzle
pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    var nums = try parse(alloc, lines);
    defer alloc.free(nums);

    for (nums, 0..) |num1, i| {
        for (nums[i + 1 ..], 0..) |num2, j| {
            for (nums[j + 1 ..]) |num3| {
                if (num1 + num2 + num3 == 2020) return num1 * num2 * num3;
            }
        }
    }

    return 0;
}

test "day00 example" {
    try validate(part1).with(example_path).equals(514579);
}

test "day00 part1" {
    try validate(part1).with(input_path).equals(618144);
}

test "day00 part2" {
    try validate(part2).with(input_path).equals(173538720);
}
