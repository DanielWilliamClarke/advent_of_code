const std = @import("std");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day01.txt";
pub const example_path = "inputs/day01_example.txt";

pub fn part1(_: std.mem.Allocator, _: []const []const u8) !i64 {
    return 0;
}

pub fn part2(_: std.mem.Allocator, _: []const []const u8) !i64 {
    return 0;
}

test "day01 example" {
    try validate(part1).with(example_path).equals(0);
}

test "day01 part1" {
    try validate(part1).with(input_path).equals(0);
}

test "day01 part2" {
    try validate(part2).with(input_path).equals(0);
}
