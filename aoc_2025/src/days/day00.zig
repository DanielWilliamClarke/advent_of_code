const std = @import("std");
const validate = @import("../util/validate.zig");

pub const input_path = "inputs/day00.txt";
pub const example_path = "inputs/day00_example.txt";

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![]const i64 {
    var nums: std.ArrayList(i64) = .empty;
    defer nums.deinit(alloc);

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

    const result = res: {
        for (nums, 0..) |num1, i| {
            for (nums[i + 1 ..]) |num2| {
                if (num1 + num2 == 2020) break :res num1 * num2;
            }
        }
        break :res 0; // fallback value if not found
    };

    return result;
}

// Part 2: Solve the second puzzle
pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    var nums = try parse(alloc, lines);
    defer alloc.free(nums);

    const result = res: {
        for (nums, 0..) |num1, i| {
            const rest1 = nums[i + 1 ..];

            for (rest1, 0..) |num2, j| {
                const rest2 = rest1[j + 1 ..];

                for (rest2) |num3| {
                    if (num1 + num2 + num3 == 2020) {
                        break :res num1 * num2 * num3;
                    }
                }
            }
        }

        break :res 0;
    };

    return result;
}

test "day00 example" {
    try validate.validate(example_path, part1, 514579);
}

test "day00 part1" {
    try validate.validate(input_path, part1, 618144);
}

test "day00 part2" {
    try validate.validate(input_path, part2, 173538720);
}
