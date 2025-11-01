const std = @import("std");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day00.txt";
pub const example_path = "inputs/day00_example.txt";

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![]i64 {
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
    const TARGET: i64 = 2020;

    const nums = try parse(alloc, lines);
    defer alloc.free(nums);

    // sort in place
    std.sort.block(i64, nums, {}, std.sort.asc(i64));

    // two-pointer scan
    var l: usize = 0;
    var r: usize = nums.len - 1;
    while (l < r) {
        const s = nums[l] + nums[r];
        if (s == TARGET) return nums[l] * nums[r];
        if (s < TARGET) l += 1 else r -= 1;
    }
    return 0;
}

// Part 2: Solve the second puzzle
pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const TARGET: i64 = 2020;

    const nums = try parse(alloc, lines);
    defer alloc.free(nums);

    // sort in place
    std.sort.block(i64, nums, {}, std.sort.asc(i64));

    // O(n^2) scan
    for (nums, 0..) |a, i| {
        var l: usize = i + 1;
        var r: usize = nums.len - 1;
        while (l < r) {
            const s = a + nums[l] + nums[r];
            if (s == TARGET) return a * nums[l] * nums[r];
            if (s < TARGET) l += 1 else r -= 1;
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
